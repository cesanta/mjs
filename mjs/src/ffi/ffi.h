/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_FFI_FFI_H_
#define MJS_FFI_FFI_H_

#include "common/platform.h"

/*
 * Maximum number of word-sized args to ffi-ed function. If at least one
 * of the args is double, only 2 args are allowed.
 */
#define FFI_MAX_ARGS_CNT 6

typedef void (*ffi_fn_t)(void);

struct ffi_arg {
  int size;
  int is_float;
  union {
    uint64_t i;
    double d;
  } v;
};

int ffi_call(ffi_fn_t func, int nargs, struct ffi_arg *res,
             struct ffi_arg *args);

void ffi_set_int32(struct ffi_arg *arg, uint32_t v);
void ffi_set_int64(struct ffi_arg *arg, uint64_t v);
void ffi_set_ptr(struct ffi_arg *arg, void *v);
void ffi_set_double(struct ffi_arg *arg, double v);

#endif /* MJS_FFI_FFI_H_ */
