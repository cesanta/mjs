/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_STRING_H_
#define MJS_STRING_H_

#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_string_public.h"

/*
 * Size of the extra space for strings mbuf that is needed to avoid frequent
 * reallocations
 */
#define _MJS_STRING_BUF_RESERVE 100

MJS_PRIVATE unsigned long cstr_to_ulong(const char *s, size_t len, int *ok);
MJS_PRIVATE mjs_err_t
str_to_ulong(struct mjs *mjs, mjs_val_t v, int *ok, unsigned long *res);
MJS_PRIVATE int s_cmp(struct mjs *mjs, mjs_val_t a, mjs_val_t b);
MJS_PRIVATE mjs_val_t s_concat(struct mjs *mjs, mjs_val_t a, mjs_val_t b);

MJS_PRIVATE void embed_string(struct mbuf *m, size_t offset, const char *p,
                              size_t len, uint8_t /*enum embstr_flags*/ flags);

MJS_PRIVATE void mjs_fstr(struct mjs *mjs);

MJS_PRIVATE void mjs_string_slice(struct mjs *mjs);
MJS_PRIVATE void mjs_string_char_code_at(struct mjs *mjs);
MJS_PRIVATE void mjs_string_indexof(struct mjs *mjs);

#define EMBSTR_ZERO_TERM 1
#define EMBSTR_UNESCAPE 2

#endif /* MJS_STRING_H_ */
