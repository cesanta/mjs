/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#include "mjs/src/mjs_exec_public.h"
#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_object.h"
#include "mjs/src/mjs_primitive.h"
#include "mjs/src/mjs_util.h"

void *mjs_mem_get_ptr(void *base, int offset) {
  return (char *) base + offset;
}

void mjs_mem_set_ptr(void *ptr, void *val) {
  *(void **) ptr = val;
}

double mjs_mem_get_dbl(void *ptr) {
  double v;
  memcpy(&v, ptr, sizeof(v));
  return v;
}

void mjs_mem_set_dbl(void *ptr, double val) {
  memcpy(ptr, &val, sizeof(val));
}

unsigned mjs_mem_get_uint(void *ptr, int size, int bigendian) {
  uint8_t *p = (uint8_t *) ptr;
  int i, inc = bigendian ? 1 : -1;
  unsigned res = 0;
  p += bigendian ? 0 : size - 1;
  for (i = 0; i < size; i++, p += inc) {
    res <<= 8;
    res |= *p;
  }
  return res;
}

void mjs_mem_set_uint(void *ptr, unsigned val, int size, int bigendian) {
  uint8_t *p = (uint8_t *) ptr + (bigendian ? 0 : size - 1);
  int i, inc = bigendian ? 1 : -1;
  for (i = 0; i < size; i++, p += inc) {
    *p = val & 0xff;
    val >>= 8;
  }
}

int mjs_mem_get_int(void *ptr, int size, int bigendian) {
  int8_t *p = (int8_t *) ptr + (bigendian ? 0 : size - 1);
  int i, inc = bigendian ? 1 : -1, res = 0;
  for (i = 0; i < size; i++, p += inc) {
    res <<= 8;
    res |= *p;
  }
  return res;
}

void mjs_mem_set_int(void *ptr, int val, int size, int bigendian) {
  mjs_mem_set_uint(ptr, val, size, bigendian);
}
