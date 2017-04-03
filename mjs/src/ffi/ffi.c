/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#include "mjs/src/ffi/ffi.h"

typedef uintptr_t word_t;

void ffi_set_int32(struct ffi_arg *arg, uint32_t v) {
  arg->size = 4;
  arg->is_float = 0;
  arg->v.i = v;
}

void ffi_set_int64(struct ffi_arg *arg, uint64_t v) {
  arg->size = 8;
  arg->is_float = 0;
  arg->v.i = v;
}

void ffi_set_ptr(struct ffi_arg *arg, void *v) {
  if (sizeof(v) == 8) {
    ffi_set_int64(arg, (uint64_t)(uintptr_t) v);
  } else {
    ffi_set_int32(arg, (uint32_t)(uintptr_t) v);
  }
}

void ffi_set_double(struct ffi_arg *arg, double v) {
  arg->size = 8;
  arg->is_float = 1;
  arg->v.d = v;
}

/*
 * The ARM ABI uses only 4 32-bit registers for paramter passing.
 * Xtensa call0 calling-convention (as used by Espressif) has 6.
 *
 * Focusing only on implementing FFI with registers means we can simplify a lot.
 *
 * ARM has some quasi-alignment rules when mixing double and integers as
 * arguments. Only:
 *   a) double, int32_t, int32_t
 *   b) int32_t, double
 * would fit in 4 registers. (the same goes for uint64_t).
 *
 * In order to simplify further, when a double-width argument is present, we
 * allow only two arguments.
 */

/*
 * We need to support x86_64 in order to support local tests.
 * x86_64 has more and wider registers, but unlike the two main
 * embedded platforms we target it has a separate register file for
 * integer values and for floating point values (both for passing args and
 * return values). E.g. if a double value is passed as a second argument
 * it gets passed in the first available floating point register.
 *
 * I.e, the compiler generates exactly the same code for:
 *
 * void foo(int a, double b) {...}
 *
 * and
 *
 * void foo(double b, int a) {...}
 *
 *
 */

typedef word_t (*w4w_t)(word_t, word_t, word_t, word_t);
typedef word_t (*w5w_t)(word_t, word_t, word_t, word_t, word_t);
typedef word_t (*w6w_t)(word_t, word_t, word_t, word_t, word_t, word_t);
typedef word_t (*wdw_t)(double, word_t);
typedef word_t (*wdd_t)(double, double);

typedef double (*d4w_t)(word_t, word_t, word_t, word_t);
typedef double (*d5w_t)(word_t, word_t, word_t, word_t, word_t);
typedef double (*d6w_t)(word_t, word_t, word_t, word_t, word_t, word_t);
typedef double (*ddw_t)(double, word_t);
typedef double (*ddd_t)(double, double);

int ffi_call(ffi_fn_t func, int nargs, struct ffi_arg *res,
             struct ffi_arg *args) {
  int i, doubles = 0;

  if (nargs > 6) return -1;
  for (i = 0; i < nargs; i++) {
    doubles += !!args[i].is_float;
  }
  if (doubles > 0 && nargs > 2) return -1;

  if (!res->is_float) {
    word_t r;
    switch (doubles) {
      case 0: {
        /* No double args: we currently support up to 6 word-sized arguments */
        if (nargs <= 4) {
          w4w_t f = (w4w_t) func;
          r = f((word_t) args[0].v.i, (word_t) args[1].v.i,
                (word_t) args[2].v.i, (word_t) args[3].v.i);
        } else if (nargs == 5) {
          w5w_t f = (w5w_t) func;
          r = f((word_t) args[0].v.i, (word_t) args[1].v.i,
                (word_t) args[2].v.i, (word_t) args[3].v.i,
                (word_t) args[4].v.i);
        } else if (nargs == 6) {
          w6w_t f = (w6w_t) func;
          r = f((word_t) args[0].v.i, (word_t) args[1].v.i,
                (word_t) args[2].v.i, (word_t) args[3].v.i,
                (word_t) args[4].v.i, (word_t) args[5].v.i);
        } else {
          abort();
        }
        break;
      }
      case 1: {
        wdw_t f = (wdw_t) func;
        if (args[0].is_float) {
          r = f(args[0].v.d, (word_t) args[1].v.i);
        } else {
          r = f(args[1].v.d, (word_t) args[0].v.i);
        }
        break;
      }
      case 2: {
        wdd_t f = (wdd_t) func;
        r = f(args[0].v.d, args[1].v.d);
      } break;
      default:
        return -1;
    }
    res->v.i = (uint64_t) r;
  } else {
    double r;
    switch (doubles) {
      case 0: {
        /* No double args: we currently support up to 6 word-sized arguments */
        if (nargs <= 4) {
          d4w_t f = (d4w_t) func;
          r = f((word_t) args[0].v.i, (word_t) args[1].v.i,
                (word_t) args[2].v.i, (word_t) args[3].v.i);
        } else if (nargs == 5) {
          d5w_t f = (d5w_t) func;
          r = f((word_t) args[0].v.i, (word_t) args[1].v.i,
                (word_t) args[2].v.i, (word_t) args[3].v.i,
                (word_t) args[4].v.i);
        } else if (nargs == 6) {
          d6w_t f = (d6w_t) func;
          r = f((word_t) args[0].v.i, (word_t) args[1].v.i,
                (word_t) args[2].v.i, (word_t) args[3].v.i,
                (word_t) args[4].v.i, (word_t) args[5].v.i);
        } else {
          abort();
        }
        break;
      }
      case 1: {
        ddw_t f = (ddw_t) func;
        if (args[0].is_float) {
          r = f(args[0].v.d, (word_t) args[1].v.i);
        } else {
          r = f(args[1].v.d, (word_t) args[0].v.i);
        }
        break;
      }
      case 2: {
        ddd_t f = (ddd_t) func;
        r = f(args[0].v.d, args[1].v.d);
      } break;
      default:
        return -1;
    }
    res->v.d = r;
  }

  return 0;
}
