/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#if MG_ENABLE_NET_IF_LWIP_LOW_LEVEL

#include "common/mg_mem.h"

#include <lwip/pbuf.h>
#include <lwip/tcp.h>
#if CS_PLATFORM != CS_P_STM32
#include <lwip/tcp_impl.h>
#endif
#include <lwip/udp.h>

#include "common/cs_dbg.h"

/*
 * Depending on whether Mongoose is compiled with ipv6 support, use right
 * lwip functions
 */
#if MG_ENABLE_IPV6
#define TCP_NEW tcp_new_ip6
#define TCP_BIND tcp_bind_ip6
#define UDP_BIND udp_bind_ip6
#define IPADDR_NTOA(x) ip6addr_ntoa((const ip6_addr_t *)(x))
#define SET_ADDR(dst, src)                               \
  memcpy((dst)->sin6.sin6_addr.s6_addr, (src)->ip6.addr, \
         sizeof((dst)->sin6.sin6_addr.s6_addr))
#else
#define TCP_NEW tcp_new
#define TCP_BIND tcp_bind
#define UDP_BIND udp_bind
#define IPADDR_NTOA ipaddr_ntoa
#define SET_ADDR(dst, src) (dst)->sin.sin_addr.s_addr = GET_IPV4(src)
#endif

/*
 * If lwip is compiled with ipv6 support, then API changes even for ipv4
 */
#if !defined(LWIP_IPV6) || !LWIP_IPV6
#define GET_IPV4(ipX_addr) ((ipX_addr)->addr)
#else
#define GET_IPV4(ipX_addr) ((ipX_addr)->ip4.addr)
#endif

void mg_lwip_ssl_do_hs(struct mg_connection *nc);
void mg_lwip_ssl_send(struct mg_connection *nc);
void mg_lwip_ssl_recv(struct mg_connection *nc);

void mg_lwip_if_init(struct mg_iface *iface);
void mg_lwip_if_free(struct mg_iface *iface);
void mg_lwip_if_add_conn(struct mg_connection *nc);
void mg_lwip_if_remove_conn(struct mg_connection *nc);
time_t mg_lwip_if_poll(struct mg_iface *iface, int timeout_ms);

#ifdef RTOS_SDK
extern void mgos_lock();
extern void mgos_unlock();
#else
#define mgos_lock()
#define mgos_unlock()
#endif

static void mg_lwip_recv_common(struct mg_connection *nc, struct pbuf *p);

#if LWIP_TCP_KEEPALIVE
void mg_lwip_set_keepalive_params(struct mg_connection *nc, int idle,
                                  int interval, int count) {
  if (nc->sock == INVALID_SOCKET || nc->flags & MG_F_UDP) {
    return;
  }
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  struct tcp_pcb *tpcb = cs->pcb.tcp;
  if (idle > 0 && interval > 0 && count > 0) {
    tpcb->keep_idle = idle * 1000;
    tpcb->keep_intvl = interval * 1000;
    tpcb->keep_cnt = count;
    tpcb->so_options |= SOF_KEEPALIVE;
  } else {
    tpcb->so_options &= ~SOF_KEEPALIVE;
  }
}
#elif !defined(MG_NO_LWIP_TCP_KEEPALIVE)
#warning LWIP TCP keepalive is disabled. Please consider enabling it.
#endif /* LWIP_TCP_KEEPALIVE */

static err_t mg_lwip_tcp_conn_cb(void *arg, struct tcp_pcb *tpcb, err_t err) {
  struct mg_connection *nc = (struct mg_connection *) arg;
  DBG(("%p connect to %s:%u = %d", nc, IPADDR_NTOA(ipX_2_ip(&tpcb->remote_ip)),
       tpcb->remote_port, err));
  if (nc == NULL) {
    tcp_abort(tpcb);
    return ERR_ARG;
  }
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  cs->err = err;
#if LWIP_TCP_KEEPALIVE
  if (err == 0) mg_lwip_set_keepalive_params(nc, 60, 10, 6);
#endif
  mg_lwip_post_signal(MG_SIG_CONNECT_RESULT, nc);
  return ERR_OK;
}

static void mg_lwip_tcp_error_cb(void *arg, err_t err) {
  struct mg_connection *nc = (struct mg_connection *) arg;
  DBG(("%p conn error %d", nc, err));
  if (nc == NULL) return;
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  cs->pcb.tcp = NULL; /* Has already been deallocated */
  if (nc->flags & MG_F_CONNECTING) {
    cs->err = err;
    mg_lwip_post_signal(MG_SIG_CONNECT_RESULT, nc);
  } else {
    mg_lwip_post_signal(MG_SIG_CLOSE_CONN, nc);
  }
}

static err_t mg_lwip_tcp_recv_cb(void *arg, struct tcp_pcb *tpcb,
                                 struct pbuf *p, err_t err) {
  struct mg_connection *nc = (struct mg_connection *) arg;
  DBG(("%p %p %u %d", nc, tpcb, (p != NULL ? p->tot_len : 0), err));
  if (p == NULL) {
    if (nc != NULL) {
      mg_lwip_post_signal(MG_SIG_CLOSE_CONN, nc);
    } else {
      /* Tombstoned connection, do nothing. */
    }
    return ERR_OK;
  } else if (nc == NULL) {
    tcp_abort(tpcb);
    return ERR_ARG;
  }
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  /*
   * If we get a chain of more than one segment at once, we need to bump
   * refcount on the subsequent bufs to make them independent.
   */
  if (p->next != NULL) {
    struct pbuf *q = p->next;
    for (; q != NULL; q = q->next) pbuf_ref(q);
  }
  if (cs->rx_chain == NULL) {
    cs->rx_offset = 0;
  } else if (pbuf_clen(cs->rx_chain) >= 4) {
    /* ESP SDK has a limited pool of 5 pbufs. We must not hog them all or RX
     * will be completely blocked. We already have at least 4 in the chain,
     * this one is, so we have to make a copy and release this one. */
    struct pbuf *np = pbuf_alloc(PBUF_RAW, p->tot_len, PBUF_RAM);
    if (np != NULL) {
      pbuf_copy(np, p);
      pbuf_free(p);
      p = np;
    }
  }
  mg_lwip_recv_common(nc, p);
  return ERR_OK;
}

static void mg_lwip_handle_recv_tcp(struct mg_connection *nc) {
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;

#if MG_ENABLE_SSL
  if (nc->flags & MG_F_SSL) {
    if (nc->flags & MG_F_SSL_HANDSHAKE_DONE) {
      mg_lwip_ssl_recv(nc);
    } else {
      mg_lwip_ssl_do_hs(nc);
    }
    return;
  }
#endif

  mgos_lock();
  while (cs->rx_chain != NULL) {
    struct pbuf *seg = cs->rx_chain;
    size_t len = (seg->len - cs->rx_offset);
    char *data = (char *) MG_MALLOC(len);
    if (data == NULL) {
      mgos_unlock();
      DBG(("OOM"));
      return;
    }
    pbuf_copy_partial(seg, data, len, cs->rx_offset);
    cs->rx_offset += len;
    if (cs->rx_offset == cs->rx_chain->len) {
      cs->rx_chain = pbuf_dechain(cs->rx_chain);
      pbuf_free(seg);
      cs->rx_offset = 0;
    }
    mgos_unlock();
    mg_if_recv_tcp_cb(nc, data, len, 1 /* own */);
    mgos_lock();
  }
  mgos_unlock();

  if (nc->send_mbuf.len > 0) {
    mg_lwip_mgr_schedule_poll(nc->mgr);
  }
}

static err_t mg_lwip_tcp_sent_cb(void *arg, struct tcp_pcb *tpcb,
                                 u16_t num_sent) {
  struct mg_connection *nc = (struct mg_connection *) arg;
  DBG(("%p %p %u", nc, tpcb, num_sent));
  if (nc == NULL) return ERR_OK;
  if ((nc->flags & MG_F_SEND_AND_CLOSE) && !(nc->flags & MG_F_WANT_WRITE) &&
      nc->send_mbuf.len == 0 && tpcb->unacked == 0) {
    mg_lwip_post_signal(MG_SIG_CLOSE_CONN, nc);
  }
  return ERR_OK;
}

void mg_lwip_if_connect_tcp(struct mg_connection *nc,
                            const union socket_address *sa) {
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  struct tcp_pcb *tpcb = TCP_NEW();
  cs->pcb.tcp = tpcb;
  ip_addr_t *ip = (ip_addr_t *) &sa->sin.sin_addr.s_addr;
  u16_t port = ntohs(sa->sin.sin_port);
  tcp_arg(tpcb, nc);
  tcp_err(tpcb, mg_lwip_tcp_error_cb);
  tcp_sent(tpcb, mg_lwip_tcp_sent_cb);
  tcp_recv(tpcb, mg_lwip_tcp_recv_cb);
  cs->err = TCP_BIND(tpcb, IP_ADDR_ANY, 0 /* any port */);
  DBG(("%p tcp_bind = %d", nc, cs->err));
  if (cs->err != ERR_OK) {
    mg_lwip_post_signal(MG_SIG_CONNECT_RESULT, nc);
    return;
  }
  cs->err = tcp_connect(tpcb, ip, port, mg_lwip_tcp_conn_cb);
  DBG(("%p tcp_connect %p = %d", nc, tpcb, cs->err));
  if (cs->err != ERR_OK) {
    mg_lwip_post_signal(MG_SIG_CONNECT_RESULT, nc);
    return;
  }
}

/*
 * Lwip included in the SDKs for nRF5x chips has different type for the
 * callback of `udp_recv()`
 */
#if CS_PLATFORM == CS_P_NRF51 || CS_PLATFORM == CS_P_NRF52 || \
    CS_PLATFORM == CS_P_STM32
static void mg_lwip_udp_recv_cb(void *arg, struct udp_pcb *pcb, struct pbuf *p,
                                const ip_addr_t *addr, u16_t port)
#else
static void mg_lwip_udp_recv_cb(void *arg, struct udp_pcb *pcb, struct pbuf *p,
                                ip_addr_t *addr, u16_t port)
#endif
{
  struct mg_connection *nc = (struct mg_connection *) arg;
  DBG(("%p %s:%u %p %u %u", nc, IPADDR_NTOA(addr), port, p, p->ref, p->len));
  /* Put address in a separate pbuf and tack it onto the packet. */
  struct pbuf *sap =
      pbuf_alloc(PBUF_RAW, sizeof(union socket_address), PBUF_RAM);
  if (sap == NULL) {
    pbuf_free(p);
    return;
  }
  union socket_address *sa = (union socket_address *) sap->payload;
  sa->sin.sin_addr.s_addr = addr->addr;
  sa->sin.sin_port = htons(port);
  /* Logic in the recv handler requires that there be exactly one data pbuf. */
  p = pbuf_coalesce(p, PBUF_RAW);
  pbuf_chain(sap, p);
  mg_lwip_recv_common(nc, sap);
  (void) pcb;
}

static void mg_lwip_recv_common(struct mg_connection *nc, struct pbuf *p) {
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  mgos_lock();
  if (cs->rx_chain == NULL) {
    cs->rx_chain = p;
  } else {
    pbuf_chain(cs->rx_chain, p);
  }
  if (!cs->recv_pending) {
    cs->recv_pending = 1;
    mg_lwip_post_signal(MG_SIG_RECV, nc);
  }
  mgos_unlock();
}

static void mg_lwip_handle_recv_udp(struct mg_connection *nc) {
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  /*
   * For UDP, RX chain consists of interleaved address and packet bufs:
   * Address pbuf followed by exactly one data pbuf (recv_cb took care of that).
   */
  while (cs->rx_chain != NULL) {
    struct pbuf *sap = cs->rx_chain;
    struct pbuf *p = sap->next;
    cs->rx_chain = pbuf_dechain(p);
    size_t data_len = p->len;
    char *data = (char *) MG_MALLOC(data_len);
    if (data != NULL) {
      pbuf_copy_partial(p, data, data_len, 0);
      pbuf_free(p);
      mg_if_recv_udp_cb(nc, data, data_len,
                        (union socket_address *) sap->payload, sap->len);
      pbuf_free(sap);
    } else {
      pbuf_free(p);
      pbuf_free(sap);
    }
  }
}

void mg_lwip_if_connect_udp(struct mg_connection *nc) {
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  struct udp_pcb *upcb = udp_new();
  cs->err = UDP_BIND(upcb, IP_ADDR_ANY, 0 /* any port */);
  DBG(("%p udp_bind %p = %d", nc, upcb, cs->err));
  if (cs->err == ERR_OK) {
    udp_recv(upcb, mg_lwip_udp_recv_cb, nc);
    cs->pcb.udp = upcb;
  } else {
    udp_remove(upcb);
  }
  mg_lwip_post_signal(MG_SIG_CONNECT_RESULT, nc);
}

void mg_lwip_accept_conn(struct mg_connection *nc, struct tcp_pcb *tpcb) {
  union socket_address sa;
  SET_ADDR(&sa, &tpcb->remote_ip);
  sa.sin.sin_port = htons(tpcb->remote_port);
  mg_if_accept_tcp_cb(nc, &sa, sizeof(sa.sin));
}

void mg_lwip_handle_accept(struct mg_connection *nc) {
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
#if MG_ENABLE_SSL
  if (cs->lc->flags & MG_F_SSL) {
    if (mg_ssl_if_conn_accept(nc, cs->lc) != MG_SSL_OK) {
      LOG(LL_ERROR, ("SSL error"));
      tcp_close(cs->pcb.tcp);
    }
  } else
#endif
  {
    mg_lwip_accept_conn(nc, cs->pcb.tcp);
  }
}

static err_t mg_lwip_accept_cb(void *arg, struct tcp_pcb *newtpcb, err_t err) {
  struct mg_connection *lc = (struct mg_connection *) arg;
  DBG(("%p conn %p from %s:%u", lc, newtpcb,
       IPADDR_NTOA(ipX_2_ip(&newtpcb->remote_ip)), newtpcb->remote_port));
  struct mg_connection *nc = mg_if_accept_new_conn(lc);
  if (nc == NULL) {
    tcp_abort(newtpcb);
    return ERR_ABRT;
  }
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  cs->lc = lc;
  cs->pcb.tcp = newtpcb;
  /* We need to set up callbacks before returning because data may start
   * arriving immediately. */
  tcp_arg(newtpcb, nc);
  tcp_err(newtpcb, mg_lwip_tcp_error_cb);
  tcp_sent(newtpcb, mg_lwip_tcp_sent_cb);
  tcp_recv(newtpcb, mg_lwip_tcp_recv_cb);
#if LWIP_TCP_KEEPALIVE
  mg_lwip_set_keepalive_params(nc, 60, 10, 6);
#endif
  mg_lwip_post_signal(MG_SIG_ACCEPT, nc);
  (void) err;
  return ERR_OK;
}

int mg_lwip_if_listen_tcp(struct mg_connection *nc, union socket_address *sa) {
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  struct tcp_pcb *tpcb = TCP_NEW();
  ip_addr_t *ip = (ip_addr_t *) &sa->sin.sin_addr.s_addr;
  u16_t port = ntohs(sa->sin.sin_port);
  cs->err = TCP_BIND(tpcb, ip, port);
  DBG(("%p tcp_bind(%s:%u) = %d", nc, IPADDR_NTOA(ip), port, cs->err));
  if (cs->err != ERR_OK) {
    tcp_close(tpcb);
    return -1;
  }
  tcp_arg(tpcb, nc);
  tpcb = tcp_listen(tpcb);
  cs->pcb.tcp = tpcb;
  tcp_accept(tpcb, mg_lwip_accept_cb);
  return 0;
}

int mg_lwip_if_listen_udp(struct mg_connection *nc, union socket_address *sa) {
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  struct udp_pcb *upcb = udp_new();
  ip_addr_t *ip = (ip_addr_t *) &sa->sin.sin_addr.s_addr;
  u16_t port = ntohs(sa->sin.sin_port);
  cs->err = UDP_BIND(upcb, ip, port);
  DBG(("%p udb_bind(%s:%u) = %d", nc, IPADDR_NTOA(ip), port, cs->err));
  if (cs->err != ERR_OK) {
    udp_remove(upcb);
    return -1;
  }
  udp_recv(upcb, mg_lwip_udp_recv_cb, nc);
  cs->pcb.udp = upcb;
  return 0;
}

int mg_lwip_tcp_write(struct mg_connection *nc, const void *data,
                      uint16_t len) {
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  struct tcp_pcb *tpcb = cs->pcb.tcp;
  if (tpcb == NULL) return -1;
  len = MIN(tpcb->mss, MIN(len, tpcb->snd_buf));
  if (len == 0) {
    DBG(("%p no buf avail %u %u %u %p %p", tpcb, tpcb->acked, tpcb->snd_buf,
         tpcb->snd_queuelen, tpcb->unsent, tpcb->unacked));
    tcp_output(tpcb);
    return 0;
  }
/*
 * On ESP8266 we only allow one TCP segment in flight at any given time.
 * This may increase latency and reduce efficiency of tcp windowing,
 * but memory is scarce and precious on that platform so we do this to
 * reduce footprint.
 */
#if CS_PLATFORM == CS_P_ESP8266
  if (tpcb->unacked != NULL) {
    return 0;
  }
  if (tpcb->unsent != NULL) {
    len = MIN(len, (TCP_MSS - tpcb->unsent->len));
  }
#endif
  cs->err = tcp_write(tpcb, data, len, TCP_WRITE_FLAG_COPY);
  DBG(("%p tcp_write %u = %d", tpcb, len, cs->err));
  if (cs->err != ERR_OK) {
    /*
     * We ignore ERR_MEM because memory will be freed up when the data is sent
     * and we'll retry.
     */
    return (cs->err == ERR_MEM ? 0 : -1);
  }
  return len;
}

static int mg_lwip_udp_send(struct mg_connection *nc, const void *data,
                            uint16_t len) {
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  if (cs->pcb.udp == NULL) {
    /*
     * In case of UDP, this usually means, what
     * async DNS resolve is still in progress and connection
     * is not ready yet
     */
    DBG(("%p socket is not connected", nc));
    return -1;
  }
  struct udp_pcb *upcb = cs->pcb.udp;
  struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);
  ip_addr_t *ip = (ip_addr_t *) &nc->sa.sin.sin_addr.s_addr;
  u16_t port = ntohs(nc->sa.sin.sin_port);
  if (p == NULL) {
    DBG(("OOM"));
    return 0;
  }
  memcpy(p->payload, data, len);
  cs->err = udp_sendto(upcb, p, (ip_addr_t *) ip, port);
  DBG(("%p udp_sendto = %d", nc, cs->err));
  pbuf_free(p);
  return (cs->err == ERR_OK ? len : -1);
}

static void mg_lwip_send_more(struct mg_connection *nc) {
  int num_sent = 0;
  if (nc->sock == INVALID_SOCKET) return;
  if (nc->flags & MG_F_UDP) {
    num_sent = mg_lwip_udp_send(nc, nc->send_mbuf.buf, nc->send_mbuf.len);
    DBG(("%p mg_lwip_udp_send %u = %d", nc, nc->send_mbuf.len, num_sent));
  } else {
    num_sent = mg_lwip_tcp_write(nc, nc->send_mbuf.buf, nc->send_mbuf.len);
    DBG(("%p mg_lwip_tcp_write %u = %d", nc, nc->send_mbuf.len, num_sent));
  }
  if (num_sent == 0) return;
  if (num_sent > 0) {
    mg_if_sent_cb(nc, num_sent);
  } else {
    mg_lwip_post_signal(MG_SIG_CLOSE_CONN, nc);
  }
}

void mg_lwip_if_tcp_send(struct mg_connection *nc, const void *buf,
                         size_t len) {
  mbuf_append(&nc->send_mbuf, buf, len);
  mg_lwip_mgr_schedule_poll(nc->mgr);
}

void mg_lwip_if_udp_send(struct mg_connection *nc, const void *buf,
                         size_t len) {
  mbuf_append(&nc->send_mbuf, buf, len);
  mg_lwip_mgr_schedule_poll(nc->mgr);
}

void mg_lwip_if_recved(struct mg_connection *nc, size_t len) {
  if (nc->flags & MG_F_UDP) return;
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  if (nc->sock == INVALID_SOCKET || cs->pcb.tcp == NULL) {
    DBG(("%p invalid socket", nc));
    return;
  }
  DBG(("%p %p %u", nc, cs->pcb.tcp, len));
/* Currently SSL acknowledges data immediately.
 * TODO(rojer): Find a way to propagate mg_lwip_if_recved. */
#if MG_ENABLE_SSL
  if (!(nc->flags & MG_F_SSL)) {
    tcp_recved(cs->pcb.tcp, len);
  }
#else
  tcp_recved(cs->pcb.tcp, len);
#endif
  mbuf_trim(&nc->recv_mbuf);
}

int mg_lwip_if_create_conn(struct mg_connection *nc) {
  struct mg_lwip_conn_state *cs =
      (struct mg_lwip_conn_state *) MG_CALLOC(1, sizeof(*cs));
  if (cs == NULL) return 0;
  cs->nc = nc;
  nc->sock = (intptr_t) cs;
  return 1;
}

void mg_lwip_if_destroy_conn(struct mg_connection *nc) {
  if (nc->sock == INVALID_SOCKET) return;
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  if (!(nc->flags & MG_F_UDP)) {
    struct tcp_pcb *tpcb = cs->pcb.tcp;
    if (tpcb != NULL) {
      tcp_arg(tpcb, NULL);
      DBG(("%p tcp_close %p", nc, tpcb));
      tcp_arg(tpcb, NULL);
      tcp_close(tpcb);
    }
    while (cs->rx_chain != NULL) {
      struct pbuf *seg = cs->rx_chain;
      cs->rx_chain = pbuf_dechain(cs->rx_chain);
      pbuf_free(seg);
    }
    memset(cs, 0, sizeof(*cs));
    MG_FREE(cs);
  } else if (nc->listener == NULL) {
    /* Only close outgoing UDP pcb or listeners. */
    struct udp_pcb *upcb = cs->pcb.udp;
    if (upcb != NULL) {
      DBG(("%p udp_remove %p", nc, upcb));
      udp_remove(upcb);
    }
    memset(cs, 0, sizeof(*cs));
    MG_FREE(cs);
  }
  nc->sock = INVALID_SOCKET;
}

void mg_lwip_if_get_conn_addr(struct mg_connection *nc, int remote,
                              union socket_address *sa) {
  memset(sa, 0, sizeof(*sa));
  if (nc == NULL || nc->sock == INVALID_SOCKET) return;
  struct mg_lwip_conn_state *cs = (struct mg_lwip_conn_state *) nc->sock;
  if (nc->flags & MG_F_UDP) {
    struct udp_pcb *upcb = cs->pcb.udp;
    if (remote) {
      memcpy(sa, &nc->sa, sizeof(*sa));
    } else if (upcb != NULL) {
      sa->sin.sin_port = htons(upcb->local_port);
      SET_ADDR(sa, &upcb->local_ip);
    }
  } else {
    struct tcp_pcb *tpcb = cs->pcb.tcp;
    if (remote) {
      memcpy(sa, &nc->sa, sizeof(*sa));
    } else if (tpcb != NULL) {
      sa->sin.sin_port = htons(tpcb->local_port);
      SET_ADDR(sa, &tpcb->local_ip);
    }
  }
}

void mg_lwip_if_sock_set(struct mg_connection *nc, sock_t sock) {
  nc->sock = sock;
}

/* clang-format off */
#define MG_LWIP_IFACE_VTABLE                                          \
  {                                                                   \
    mg_lwip_if_init,                                                  \
    mg_lwip_if_free,                                                  \
    mg_lwip_if_add_conn,                                              \
    mg_lwip_if_remove_conn,                                           \
    mg_lwip_if_poll,                                                  \
    mg_lwip_if_listen_tcp,                                            \
    mg_lwip_if_listen_udp,                                            \
    mg_lwip_if_connect_tcp,                                           \
    mg_lwip_if_connect_udp,                                           \
    mg_lwip_if_tcp_send,                                              \
    mg_lwip_if_udp_send,                                              \
    mg_lwip_if_recved,                                                \
    mg_lwip_if_create_conn,                                           \
    mg_lwip_if_destroy_conn,                                          \
    mg_lwip_if_sock_set,                                              \
    mg_lwip_if_get_conn_addr,                                         \
  }
/* clang-format on */

const struct mg_iface_vtable mg_lwip_iface_vtable = MG_LWIP_IFACE_VTABLE;
#if MG_NET_IF == MG_NET_IF_LWIP_LOW_LEVEL
const struct mg_iface_vtable mg_default_iface_vtable = MG_LWIP_IFACE_VTABLE;
#endif

#endif /* MG_ENABLE_NET_IF_LWIP_LOW_LEVEL */
