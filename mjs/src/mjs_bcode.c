/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_core.h"
#include "mjs/src/mjs_tok.h"
#include "mjs/src/mjs_varint.h"

static void add_lineno_map_item(struct pstate *pstate) {
  if (pstate->last_emitted_line_no < pstate->line_no) {
    int offset = pstate->mjs->bcode.len - pstate->start_bcode_idx;
    size_t offset_llen = varint_llen(offset);
    size_t lineno_llen = varint_llen(pstate->line_no);
    mbuf_resize(&pstate->offset_lineno_map,
                pstate->offset_lineno_map.size + offset_llen + lineno_llen);

    /* put offset */
    varint_encode(offset, (uint8_t *) pstate->offset_lineno_map.buf +
                              pstate->offset_lineno_map.len);
    pstate->offset_lineno_map.len += offset_llen;

    /* put line_no */
    varint_encode(pstate->line_no, (uint8_t *) pstate->offset_lineno_map.buf +
                                       pstate->offset_lineno_map.len);
    pstate->offset_lineno_map.len += lineno_llen;

    pstate->last_emitted_line_no = pstate->line_no;
  }
}

MJS_PRIVATE void emit_byte(struct pstate *pstate, uint8_t byte) {
  add_lineno_map_item(pstate);
  mbuf_append(&pstate->mjs->bcode, &byte, sizeof(byte));
}

MJS_PRIVATE void emit_int(struct pstate *pstate, int64_t n) {
  add_lineno_map_item(pstate);
  struct mbuf *b = &pstate->mjs->bcode;
  size_t llen = varint_llen(n);
  mbuf_resize(b, b->size + llen);
  varint_encode(n, (uint8_t *) b->buf + b->len);
  b->len += llen;
}

MJS_PRIVATE void emit_str(struct pstate *pstate, const char *ptr, size_t len) {
  add_lineno_map_item(pstate);
  struct mbuf *b = &pstate->mjs->bcode;
  size_t llen = varint_llen(len);
  mbuf_resize(b, b->size + llen + len);
  varint_encode(len, (uint8_t *) b->buf + b->len);
  memcpy(b->buf + b->len + llen, ptr, len);
  b->len += llen + len;
}

MJS_PRIVATE size_t mjs_bcode_size(const struct mbuf *bcode) {
  return bcode->len;
}

MJS_PRIVATE void mjs_bcode_mutate_byte(struct mjs *mjs, size_t offset,
                                       size_t v) {
  if (v > 0xff) {
    mjs_set_errorf(mjs, MJS_INTERNAL_ERROR, "loop/cond body too long");
  } else if (offset >= mjs->bcode.len) {
    mjs_set_errorf(mjs, MJS_INTERNAL_ERROR, "oob offset");
  } else if (offset < mjs->bcode.len) {
    mjs->bcode.buf[offset] = v;
  }
}
