/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_FFI_H_
#define MJS_FFI_H_

#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_ffi_public.h"

mjs_ffi_resolver_t dlsym;

#define MJS_CB_ARGS_MAX_CNT 6
#define MJS_CB_SIGNATURE_MAX_SIZE (MJS_CB_ARGS_MAX_CNT + 1 /* return type */)

enum cval_type {
  CVAL_TYPE_NONE,
  CVAL_TYPE_USERDATA,
  CVAL_TYPE_INT,
  CVAL_TYPE_BOOL,
  CVAL_TYPE_DOUBLE,
  CVAL_TYPE_CHAR_PTR,
  CVAL_TYPE_VOID_PTR,
  CVAL_TYPE_INVALID,
};
typedef uint8_t cval_type_t;

struct ffi_sig_stat {
  int8_t is_valid;
  int8_t userdata_idx;
  int8_t args_cnt;
  int8_t args_double_cnt;
};

struct ffi_sig {
  /*
   * The first item is the return value type (for `void`, `CVAL_TYPE_NONE` is
   * used); the rest are arguments. If some argument is `CVAL_TYPE_NONE`, it
   * means that there are no more arguments.
   */
  cval_type_t val_types[MJS_CB_SIGNATURE_MAX_SIZE];
  struct ffi_sig_stat stat;
};
typedef struct ffi_sig ffi_sig_t;

MJS_PRIVATE void mjs_ffi_sig_init(ffi_sig_t *sig);
MJS_PRIVATE int mjs_ffi_sig_set_val_type(ffi_sig_t *sig, int idx,
                                         cval_type_t type);
MJS_PRIVATE struct ffi_sig_stat mjs_ffi_sig_stat_get(struct mjs *mjs,
                                                     const ffi_sig_t *sig);
MJS_PRIVATE int mjs_ffi_is_regular_word(cval_type_t type);
MJS_PRIVATE int mjs_ffi_is_regular_word_or_void(cval_type_t type);

struct ffi_cb_args {
  struct ffi_cb_args *next;
  struct mjs *mjs;
  ffi_sig_t sig;
  mjs_val_t func;
  mjs_val_t userdata;
};
typedef struct ffi_cb_args ffi_cb_args_t;

MJS_PRIVATE mjs_err_t mjs_ffi_call(struct mjs *mjs);
MJS_PRIVATE mjs_err_t mjs_ffi_call2(struct mjs *mjs);
MJS_PRIVATE void mjs_ffi_cb_free(struct mjs *);
MJS_PRIVATE void mjs_ffi_args_free_list(struct mjs *mjs);

#endif /* MJS_FFI_H_ */
