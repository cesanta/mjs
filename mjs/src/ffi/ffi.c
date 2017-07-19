/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#include "mjs/src/ffi/ffi.h"

#define IS_W(arg) ((arg).ctype == FFI_CTYPE_WORD)
#define IS_D(arg) ((arg).ctype == FFI_CTYPE_DOUBLE)

#define W(arg) ((ffi_word_t)(arg).v.i)
#define D(arg) ((arg).v.d)

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

typedef ffi_word_t (*wwwd_t)(ffi_word_t, ffi_word_t, double);
typedef ffi_word_t (*wwdw_t)(ffi_word_t, double, ffi_word_t);
typedef ffi_word_t (*wwdd_t)(ffi_word_t, double, double);
typedef ffi_word_t (*wdww_t)(double, ffi_word_t, ffi_word_t);
typedef ffi_word_t (*wdwd_t)(double, ffi_word_t, double);
typedef ffi_word_t (*wddw_t)(double, double, ffi_word_t);
typedef ffi_word_t (*wddd_t)(double, double, double);

typedef bool (*b4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef bool (*b5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                      ffi_word_t);
typedef bool (*b6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                      ffi_word_t, ffi_word_t);
typedef bool (*bdw_t)(double, ffi_word_t);
typedef bool (*bwd_t)(ffi_word_t, double);
typedef bool (*bdd_t)(double, double);

typedef bool (*bwwd_t)(ffi_word_t, ffi_word_t, double);
typedef bool (*bwdw_t)(ffi_word_t, double, ffi_word_t);
typedef bool (*bwdd_t)(ffi_word_t, double, double);
typedef bool (*bdww_t)(double, ffi_word_t, ffi_word_t);
typedef bool (*bdwd_t)(double, ffi_word_t, double);
typedef bool (*bddw_t)(double, double, ffi_word_t);
typedef bool (*bddd_t)(double, double, double);

typedef double (*d4w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t);
typedef double (*d5w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                        ffi_word_t);
typedef double (*d6w_t)(ffi_word_t, ffi_word_t, ffi_word_t, ffi_word_t,
                        ffi_word_t, ffi_word_t);
typedef double (*ddw_t)(double, ffi_word_t);
typedef double (*dwd_t)(ffi_word_t, double);
typedef double (*ddd_t)(double, double);

typedef double (*dwwd_t)(ffi_word_t, ffi_word_t, double);
typedef double (*dwdw_t)(ffi_word_t, double, ffi_word_t);
typedef double (*dwdd_t)(ffi_word_t, double, double);
typedef double (*ddww_t)(double, ffi_word_t, ffi_word_t);
typedef double (*ddwd_t)(double, ffi_word_t, double);
typedef double (*dddw_t)(double, double, ffi_word_t);
typedef double (*dddd_t)(double, double, double);

int ffi_call(ffi_fn_t *func, int nargs, struct ffi_arg *res,
             struct ffi_arg *args) {
  int i, doubles = 0;

  if (nargs > 6) return -1;
  for (i = 0; i < nargs; i++) {
    doubles += (IS_D(args[i]));
  }

  switch (res->ctype) {
    case FFI_CTYPE_WORD: {
      ffi_word_t r;
      switch (doubles) {
        case 0: {
          /* No double args: we currently support up to 6 word-sized arguments
           */
          if (nargs <= 4) {
            w4w_t f = (w4w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]));
          } else if (nargs == 5) {
            w5w_t f = (w5w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]));
          } else if (nargs == 6) {
            w6w_t f = (w6w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]),
                  W(args[5]));
          } else {
            abort();
          }
          break;
        }
        case 1:
          switch (nargs) {
            case 0:
            case 1:
            case 2:
              if (IS_D(args[0])) {
                wdw_t f = (wdw_t) func;
                r = f(D(args[0]), W(args[1]));
              } else {
                wwd_t f = (wwd_t) func;
                r = f(W(args[0]), D(args[1]));
              }
              break;

            case 3:
              if (IS_W(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
                wwwd_t f = (wwwd_t) func;
                r = f(W(args[0]), W(args[1]), D(args[2]));
              } else if (IS_W(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
                wwdw_t f = (wwdw_t) func;
                r = f(W(args[0]), D(args[1]), W(args[2]));
              } else if (IS_W(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
                wwdd_t f = (wwdd_t) func;
                r = f(W(args[0]), D(args[1]), D(args[2]));
              } else if (IS_D(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
                wdww_t f = (wdww_t) func;
                r = f(D(args[0]), W(args[1]), W(args[2]));
              } else if (IS_D(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
                wdwd_t f = (wdwd_t) func;
                r = f(D(args[0]), W(args[1]), D(args[2]));
              } else if (IS_D(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
                wddw_t f = (wddw_t) func;
                r = f(D(args[0]), D(args[1]), W(args[2]));
              } else if (IS_D(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
                wddd_t f = (wddd_t) func;
                r = f(D(args[0]), D(args[1]), D(args[2]));
              } else {
                // The above checks should be exhaustive
                abort();
              }
              break;
            default:
              return -1;
          }
          break;
        case 2: {
          wdd_t f = (wdd_t) func;
          r = f(D(args[0]), D(args[1]));
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
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]));
          } else if (nargs == 5) {
            b5w_t f = (b5w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]));
          } else if (nargs == 6) {
            b6w_t f = (b6w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]),
                  W(args[5]));
          } else {
            abort();
          }
          break;
        }
        case 1: {
          switch (nargs) {
            case 0:
            case 1:
            case 2:
              if (IS_D(args[0])) {
                bdw_t f = (bdw_t) func;
                r = f(D(args[0]), W(args[1]));
              } else {
                bwd_t f = (bwd_t) func;
                r = f(W(args[0]), D(args[1]));
              }
              break;

            case 3:
              if (IS_W(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
                bwwd_t f = (bwwd_t) func;
                r = f(W(args[0]), W(args[1]), D(args[2]));
              } else if (IS_W(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
                bwdw_t f = (bwdw_t) func;
                r = f(W(args[0]), D(args[1]), W(args[2]));
              } else if (IS_W(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
                bwdd_t f = (bwdd_t) func;
                r = f(W(args[0]), D(args[1]), D(args[2]));
              } else if (IS_D(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
                bdww_t f = (bdww_t) func;
                r = f(D(args[0]), W(args[1]), W(args[2]));
              } else if (IS_D(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
                bdwd_t f = (bdwd_t) func;
                r = f(D(args[0]), W(args[1]), D(args[2]));
              } else if (IS_D(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
                bddw_t f = (bddw_t) func;
                r = f(D(args[0]), D(args[1]), W(args[2]));
              } else if (IS_D(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
                bddd_t f = (bddd_t) func;
                r = f(D(args[0]), D(args[1]), D(args[2]));
              } else {
                // The above checks should be exhaustive
                abort();
              }
              break;
            default:
              return -1;
          }
          break;
        }
        case 2: {
          bdd_t f = (bdd_t) func;
          r = f(D(args[0]), D(args[1]));
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
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]));
          } else if (nargs == 5) {
            d5w_t f = (d5w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]));
          } else if (nargs == 6) {
            d6w_t f = (d6w_t) func;
            r = f(W(args[0]), W(args[1]), W(args[2]), W(args[3]), W(args[4]),
                  W(args[5]));
          } else {
            abort();
          }
          break;
        }
        case 1: {
          switch (nargs) {
            case 0:
            case 1:
            case 2:
              if (IS_D(args[0])) {
                ddw_t f = (ddw_t) func;
                r = f(D(args[0]), W(args[1]));
              } else {
                dwd_t f = (dwd_t) func;
                r = f(W(args[0]), D(args[1]));
              }
              break;

            case 3:
              if (IS_W(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
                dwwd_t f = (dwwd_t) func;
                r = f(W(args[0]), W(args[1]), D(args[2]));
              } else if (IS_W(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
                dwdw_t f = (dwdw_t) func;
                r = f(W(args[0]), D(args[1]), W(args[2]));
              } else if (IS_W(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
                dwdd_t f = (dwdd_t) func;
                r = f(W(args[0]), D(args[1]), D(args[2]));
              } else if (IS_D(args[0]) && IS_W(args[1]) && IS_W(args[2])) {
                ddww_t f = (ddww_t) func;
                r = f(D(args[0]), W(args[1]), W(args[2]));
              } else if (IS_D(args[0]) && IS_W(args[1]) && IS_D(args[2])) {
                ddwd_t f = (ddwd_t) func;
                r = f(D(args[0]), W(args[1]), D(args[2]));
              } else if (IS_D(args[0]) && IS_D(args[1]) && IS_W(args[2])) {
                dddw_t f = (dddw_t) func;
                r = f(D(args[0]), D(args[1]), W(args[2]));
              } else if (IS_D(args[0]) && IS_D(args[1]) && IS_D(args[2])) {
                dddd_t f = (dddd_t) func;
                r = f(D(args[0]), D(args[1]), D(args[2]));
              } else {
                // The above checks should be exhaustive
                abort();
              }
              break;
            default:
              return -1;
          }
          break;
        }
        case 2: {
          ddd_t f = (ddd_t) func;
          r = f(D(args[0]), D(args[1]));
        } break;
        default:
          return -1;
      }
      res->v.d = r;
    } break;
  }

  return 0;
}
