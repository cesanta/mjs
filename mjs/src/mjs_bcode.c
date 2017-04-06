/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#include "common/cs_varint.h"

#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_core.h"
#include "mjs/src/mjs_tok.h"

static void add_lineno_map_item(struct pstate *pstate) {
  if (pstate->last_emitted_line_no < pstate->line_no) {
    int offset = pstate->cur_idx - pstate->start_bcode_idx;
    size_t offset_llen = cs_varint_llen(offset);
    size_t lineno_llen = cs_varint_llen(pstate->line_no);
    mbuf_resize(&pstate->offset_lineno_map,
                pstate->offset_lineno_map.size + offset_llen + lineno_llen);

    /* put offset */
    cs_varint_encode(offset, (uint8_t *) pstate->offset_lineno_map.buf +
                                 pstate->offset_lineno_map.len);
    pstate->offset_lineno_map.len += offset_llen;

    /* put line_no */
    cs_varint_encode(pstate->line_no,
                     (uint8_t *) pstate->offset_lineno_map.buf +
                         pstate->offset_lineno_map.len);
    pstate->offset_lineno_map.len += lineno_llen;

    pstate->last_emitted_line_no = pstate->line_no;
  }
}

MJS_PRIVATE void emit_byte(struct pstate *pstate, uint8_t byte) {
  add_lineno_map_item(pstate);
  mbuf_insert(&pstate->mjs->bcode, pstate->cur_idx, &byte, sizeof(byte));
  pstate->cur_idx += sizeof(byte);
}

MJS_PRIVATE void emit_int(struct pstate *pstate, int64_t n) {
  add_lineno_map_item(pstate);
  struct mbuf *b = &pstate->mjs->bcode;
  size_t llen = cs_varint_llen(n);
  mbuf_insert(b, pstate->cur_idx, NULL, llen);
  cs_varint_encode(n, (uint8_t *) b->buf + pstate->cur_idx);
  pstate->cur_idx += llen;
}

MJS_PRIVATE void emit_str(struct pstate *pstate, const char *ptr, size_t len) {
  add_lineno_map_item(pstate);
  struct mbuf *b = &pstate->mjs->bcode;
  size_t llen = cs_varint_llen(len);
  mbuf_insert(b, pstate->cur_idx, NULL, llen + len);
  cs_varint_encode(len, (uint8_t *) b->buf + pstate->cur_idx);
  memcpy(b->buf + pstate->cur_idx + llen, ptr, len);
  pstate->cur_idx += llen + len;
}

MJS_PRIVATE int mjs_bcode_insert_offset(struct pstate *p, struct mjs *mjs,
                                        size_t offset, size_t v) {
  assert(offset < mjs->bcode.len);
  int llen = cs_varint_llen(v);
  int diff = llen - MJS_INIT_OFFSET_SIZE;
  if (diff > 0) {
    mbuf_resize(&mjs->bcode, mjs->bcode.size + diff);
  }
  /*
   * Offset is going to take more than one was reserved, so, move the data
   * forward
   */
  memmove(mjs->bcode.buf + offset + llen,
          mjs->bcode.buf + offset + MJS_INIT_OFFSET_SIZE,
          mjs->bcode.len - offset - MJS_INIT_OFFSET_SIZE);
  mjs->bcode.len += diff;
  cs_varint_encode(v, (uint8_t *) mjs->bcode.buf + offset);

  /*
   * If current parsing index is after the offset at which we've inserted new
   * varint, the index might need to be adjusted
   */
  if (p->cur_idx >= (int) offset) {
    p->cur_idx += diff;
  }
  return diff;
}
