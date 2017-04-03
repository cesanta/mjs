/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include "mjs/src/mjs_varint.h"
#include "mjs/src/mjs_internal.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*
 * Strings in AST are encoded as tuples (length, string).
 * Length is variable-length: if high bit is set in a byte, next byte is used.
 * Small string length (less then 128 bytes) is encoded in 1 byte.
 */
MJS_PRIVATE int64_t varint_decode(const uint8_t *p, int *llen) {
  int64_t i = 0, num = 0;

  do {
    /*
     * Each byte of varint contains 7 bits, in little endian order.
     * MSB is a continuation bit: it tells whether next byte is used.
     */
    num |= ((int64_t)(p[i] & 0x7f)) << (7 * i);
    /*
     * First we increment i, then check whether it is within boundary and
     * whether decoded byte had continuation bit set.
     */
  } while ((size_t) ++i < sizeof(int64_t) && (p[i - 1] & 0x80));
  *llen = i;

  return num;
}

/* Return number of bytes to store length */
MJS_PRIVATE int varint_llen(int64_t num) {
  int n = 0;

  do {
    n++;
  } while (num >>= 7);

  return n;
}

MJS_PRIVATE int varint_encode(int64_t num, uint8_t *p) {
  int i, llen = varint_llen(num);

  for (i = 0; i < llen; i++) {
    p[i] = (num & 0x7f) | (i < llen - 1 ? 0x80 : 0);
    num >>= 7;
  }

  return llen;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */
