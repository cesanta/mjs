/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#include "mjs/src/ffi/ffi.h"

void ffi_set_word(struct ffi_arg *arg, ffi_word_t v) {
  arg->ctype = FFI_CTYPE_WORD;
  arg->v.i = v;
}

void ffi_set_bool(struct ffi_arg *arg, bool v) {
  arg->ctype = FFI_CTYPE_BOOL;
  arg->v.i = v;
}

void ffi_set_ptr(struct ffi_arg *arg, void *v) {
  ffi_set_word(arg, (ffi_word_t) v);
}

void ffi_set_double(struct ffi_arg *arg, double v) {
  arg->ctype = FFI_CTYPE_DOUBLE;
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

typedef ffi_word_t (*w4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef ffi_word_t (*w5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                            ffi_word_t);
typedef ffi_word_t (*w6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                            ffi_word_t, ffi_word_t);
typedef ffi_word_t (*wdw_t)(double, ffi_word_t);
typedef ffi_word_t (*wwd_t)(ffi_word_t, double);
typedef ffi_word_t (*wdd_t)(double, double);

typedef bool (*b4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef bool (*b5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                      ffi_word_t);
typedef bool (*b6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                      ffi_word_t, ffi_word_t);
typedef bool (*bdw_t)(double, ffi_word_t);
typedef bool (*bwd_t)(ffi_word_t, double);
typedef bool (*bdd_t)(double, double);

typedef double (*d4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef double (*d5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                        ffi_word_t);
typedef double (*d6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                        ffi_word_t, ffi_word_t);
typedef double (*ddw_t)(double, ffi_word_t);
typedef double (*dwd_t)(ffi_word_t, double);
typedef double (*ddd_t)(double, double);

int ffi_call(ffi_fn_t *func, int nargs, struct ffi_arg *res,
             struct ffi_arg *args) {
  int i, doubles = 0;

  if (nargs > 6) return -1;
  for (i = 0; i < nargs; i++) {
    doubles += (args[i].ctype == FFI_CTYPE_DOUBLE);
  }
  if (doubles > 0 && nargs > 2) return -1;

  switch (res->ctype) {
    case FFI_CTYPE_WORD: {
      ffi_word_t r;
      switch (doubles) {
        case 0: {
          /* No double args: we currently support up to 6 word-sized arguments
           */
          if (nargs <= 4) {
            w4w_t f = (w4w_t) func;
            r = f((ffi_word_t) args[0].v.i, (ffi_word_t) args[1].v.i,
                  (ffi_word_t) args[2].v.i, (ffi_word_t) args[3].v.i);
          } else if (nargs == 5) {
            w5w_t f = (w5w_t) func;
            r = f((ffi_word_t) args[0].v.i, (ffi_word_t) args[1].v.i,
                  (ffi_word_t) args[2].v.i, (ffi_word_t) args[3].v.i,
                  (ffi_word_t) args[4].v.i);
          } else if (nargs == 6) {
            w6w_t f = (w6w_t) func;
            r = f((ffi_word_t) args[0].v.i, (ffi_word_t) args[1].v.i,
                  (ffi_word_t) args[2].v.i, (ffi_word_t) args[3].v.i,
                  (ffi_word_t) args[4].v.i, (ffi_word_t) args[5].v.i);
          } else {
            abort();
          }
          break;
        }
        case 1:
          if (args[0].ctype == FFI_CTYPE_DOUBLE) {
            wdw_t f = (wdw_t) func;
            r = f(args[0].v.d, (ffi_word_t) args[1].v.i);
          } else {
            wwd_t f = (wwd_t) func;
            r = f((ffi_word_t) args[0].v.i, args[1].v.d);
          }
          break;
        case 2: {
          wdd_t f = (wdd_t) func;
          r = f(args[0].v.d, args[1].v.d);
        } break;
        default:
          return -1;
      }
      res->v.i = (uint64_t) r;
    } break;
    case FFI_CTYPE_BOOL: {
      ffi_word_t r;
      switch (doubles) {
        case 0: {
          /* No double args: we currently support up to 6 word-sized arguments
           */
          if (nargs <= 4) {
            b4w_t f = (b4w_t) func;
            r = f((ffi_word_t) args[0].v.i, (ffi_word_t) args[1].v.i,
                  (ffi_word_t) args[2].v.i, (ffi_word_t) args[3].v.i);
          } else if (nargs == 5) {
            b5w_t f = (b5w_t) func;
            r = f((ffi_word_t) args[0].v.i, (ffi_word_t) args[1].v.i,
                  (ffi_word_t) args[2].v.i, (ffi_word_t) args[3].v.i,
                  (ffi_word_t) args[4].v.i);
          } else if (nargs == 6) {
            b6w_t f = (b6w_t) func;
            r = f((ffi_word_t) args[0].v.i, (ffi_word_t) args[1].v.i,
                  (ffi_word_t) args[2].v.i, (ffi_word_t) args[3].v.i,
                  (ffi_word_t) args[4].v.i, (ffi_word_t) args[5].v.i);
          } else {
            abort();
          }
          break;
        }
        case 1: {
          if (args[0].ctype == FFI_CTYPE_DOUBLE) {
            bdw_t f = (bdw_t) func;
            r = f(args[0].v.d, (ffi_word_t) args[1].v.i);
          } else {
            bwd_t f = (bwd_t) func;
            r = f((ffi_word_t) args[0].v.i, args[1].v.d);
          }
          break;
        }
        case 2: {
          bdd_t f = (bdd_t) func;
          r = f(args[0].v.d, args[1].v.d);
        } break;
        default:
          return -1;
      }
      res->v.i = (uint64_t) r;
    } break;
    case FFI_CTYPE_DOUBLE: {
      double r;
      switch (doubles) {
        case 0: {
          /* No double args: we currently support up to 6 word-sized arguments
           */
          if (nargs <= 4) {
            d4w_t f = (d4w_t) func;
            r = f((ffi_word_t) args[0].v.i, (ffi_word_t) args[1].v.i,
                  (ffi_word_t) args[2].v.i, (ffi_word_t) args[3].v.i);
          } else if (nargs == 5) {
            d5w_t f = (d5w_t) func;
            r = f((ffi_word_t) args[0].v.i, (ffi_word_t) args[1].v.i,
                  (ffi_word_t) args[2].v.i, (ffi_word_t) args[3].v.i,
                  (ffi_word_t) args[4].v.i);
          } else if (nargs == 6) {
            d6w_t f = (d6w_t) func;
            r = f((ffi_word_t) args[0].v.i, (ffi_word_t) args[1].v.i,
                  (ffi_word_t) args[2].v.i, (ffi_word_t) args[3].v.i,
                  (ffi_word_t) args[4].v.i, (ffi_word_t) args[5].v.i);
          } else {
            abort();
          }
          break;
        }
        case 1: {
          if (args[0].ctype == FFI_CTYPE_DOUBLE) {
            ddw_t f = (ddw_t) func;
            r = f(args[0].v.d, (ffi_word_t) args[1].v.i);
          } else {
            dwd_t f = (dwd_t) func;
            r = f((ffi_word_t) args[0].v.i, args[1].v.d);
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
    } break;
  }

  return 0;
}
