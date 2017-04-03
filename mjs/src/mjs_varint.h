/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_VARINT_H_
#define MJS_VARINT_H_

#include "mjs/src/mjs_internal.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

MJS_PRIVATE int varint_encode(int64_t num, uint8_t *to);
MJS_PRIVATE int64_t varint_decode(const uint8_t *from, int *llen);
MJS_PRIVATE int varint_llen(int64_t num);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_VARINT_H_ */
