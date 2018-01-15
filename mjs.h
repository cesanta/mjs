#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_license.h"
#endif
/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 *
 * This software is dual-licensed: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation. For the terms of this
 * license, see <http://www.gnu.org/licenses/>.
 *
 * You are free to use this software under the terms of the GNU General
 * Public License, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * Alternatively, you can license this software under a commercial
 * license, as set out in <https://www.cesanta.com/license>.
 */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_features.h"
#endif
/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_FEATURES_H_
#define MJS_FEATURES_H_

#if !defined(MJS_AGGRESSIVE_GC)
#define MJS_AGGRESSIVE_GC 0
#endif

#if !defined(MJS_MEMORY_STATS)
#define MJS_MEMORY_STATS 0
#endif

/*
 * MJS_GENERATE_JSC: if enabled, and if mmapping is also enabled (CS_MMAP),
 * then execution of any .js file will result in creation of a .jsc file with
 * precompiled bcode, and this .jsc file will be mmapped, instead of keeping
 * bcode in RAM.
 *
 * By default it's enabled (provided that CS_MMAP is defined)
 */
#if !defined(MJS_GENERATE_JSC)
#if defined(CS_MMAP)
#define MJS_GENERATE_JSC 1
#else
#define MJS_GENERATE_JSC 0
#endif
#endif

#endif /* MJS_FEATURES_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_core_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_CORE_PUBLIC_H_
#define MJS_CORE_PUBLIC_H_

#if !defined(_MSC_VER) || _MSC_VER >= 1700
#include <stdint.h>
#else
typedef unsigned __int64 uint64_t;
typedef int int32_t;
typedef unsigned char uint8_t;
#endif
#include <stdio.h>
#include <stddef.h>
/* Amalgamated: #include "mjs/src/mjs_license.h" */
/* Amalgamated: #include "mjs/src/mjs_features.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define MJS_ENABLE_DEBUG 1

/*
 *  Double-precision floating-point number, IEEE 754
 *
 *  64 bit (8 bytes) in total
 *  1  bit sign
 *  11 bits exponent
 *  52 bits mantissa
 *      7         6        5        4        3        2        1        0
 *  seeeeeee|eeeemmmm|mmmmmmmm|mmmmmmmm|mmmmmmmm|mmmmmmmm|mmmmmmmm|mmmmmmmm
 *
 * If an exponent is all-1 and mantissa is all-0, then it is an INFINITY:
 *  11111111|11110000|00000000|00000000|00000000|00000000|00000000|00000000
 *
 * If an exponent is all-1 and mantissa's MSB is 1, it is a quiet NaN:
 *  11111111|11111000|00000000|00000000|00000000|00000000|00000000|00000000
 *
 *  MJS NaN-packing:
 *    sign and exponent is 0xfff
 *    4 bits specify type (tag), must be non-zero
 *    48 bits specify value
 *
 *  11111111|1111tttt|vvvvvvvv|vvvvvvvv|vvvvvvvv|vvvvvvvv|vvvvvvvv|vvvvvvvv
 *   NaN marker |type|  48-bit placeholder for values: pointers, strings
 *
 * On 64-bit platforms, pointers are really 48 bit only, so they can fit,
 * provided they are sign extended
 */

typedef uint64_t mjs_val_t;

/* This if-0 is a dirty workaround to force etags to pick `struct mjs` */
#if 0
/* Opaque structure. MJS engine context. */
struct mjs {
  /* ... */
};
#endif

struct mjs;

typedef enum mjs_err {
  MJS_OK,
  MJS_SYNTAX_ERROR,
  MJS_REFERENCE_ERROR,
  MJS_TYPE_ERROR,
  MJS_OUT_OF_MEMORY,
  MJS_INTERNAL_ERROR,
  MJS_NOT_IMPLEMENTED_ERROR,
  MJS_FILE_READ_ERROR,
  MJS_BAD_ARGS_ERROR,

  MJS_ERRS_CNT
} mjs_err_t;
struct mjs;

/* Create MJS instance */
struct mjs *mjs_create();

struct mjs_create_opts {
  /* use non-default bytecode definition file, testing-only */
  const struct bf_code *code;
};

/*
 * Like `msj_create()`, but allows to customize initial MJS state, see `struct
 * mjs_create_opts`.
 */
struct mjs *mjs_create_opt(struct mjs_create_opts opts);

/* Destroy MJS instance */
void mjs_destroy(struct mjs *mjs);

mjs_val_t mjs_get_global(struct mjs *mjs);

/*
 * Tells the GC about an MJS value variable/field owned by C code.
 *
 * The user's C code should own mjs_val_t variables if the value's lifetime
 * crosses any invocation of `mjs_exec()` and friends, including `mjs_call()`.
 *
 * The registration of the variable prevents the GC from mistakenly treat the
 * object as garbage.
 *
 * User code should also explicitly disown the variables with `mjs_disown()`
 * once it goes out of scope or the structure containing the mjs_val_t field is
 * freed.
 *
 * Consider the following examples:
 *
 * Correct (owning is not necessary):
 * ```c
 * mjs_val_t res;
 * mjs_exec(mjs, "....some script", &res);
 * // ... use res somehow
 *
 * mjs_val_t res;
 * mjs_exec(mjs, "....some script2", &res);
 * // ... use new res somehow
 * ```
 *
 * WRONG:
 * ```c
 * mjs_val_t res1;
 * mjs_exec(mjs, "....some script", &res1);
 *
 * mjs_val_t res2;
 * mjs_exec(mjs, "....some script2", &res2);
 *
 * // ... use res1 (WRONG!) and res2
 * ```
 *
 * The code above is wrong, because after the second invocation of
 * `mjs_exec()`, the value of `res1` is invalidated.
 *
 * Correct (res1 is owned)
 * ```c
 * mjs_val_t res1 = MJS_UNDEFINED;
 * mjs_own(mjs, &res1);
 * mjs_exec(mjs, "....some script", &res1);
 *
 * mjs_val_t res2 = MJS_UNDEFINED;
 * mjs_exec(mjs, "....some script2", &res2);
 *
 * // ... use res1 and res2
 * mjs_disown(mjs, &res1);
 * ```
 *
 * NOTE that we explicly initialized `res1` to a valid value before owning it
 * (in this case, the value is `MJS_UNDEFINED`). Owning an uninitialized
 * variable is an undefined behaviour.
 *
 * Of course, it's not an error to own a variable even if it's not mandatory:
 * e.g. in the last example we could own both `res1` and `res2`. Probably it
 * would help us in the future, when we refactor the code so that `res2` has to
 * be owned, and we could forget to do that.
 *
 * Also, if the user code has some C function called from MJS, and in this C
 * function some MJS value (`mjs_val_t`) needs to be stored somewhhere and to
 * stay alive after the C function has returned, it also needs to be properly
 * owned.
 */
void mjs_own(struct mjs *mjs, mjs_val_t *v);

/*
 * Disowns the value previously owned by `mjs_own()`.
 *
 * Returns 1 if value is found, 0 otherwise.
 */
int mjs_disown(struct mjs *mjs, mjs_val_t *v);

mjs_err_t mjs_set_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt, ...);

/*
 * If there is no error message already set, then it's equal to
 * `mjs_set_errorf()`.
 *
 * Otherwise, an old message gets prepended with the new one, followed by a
 * colon. (the previously set error code is kept)
 */
mjs_err_t mjs_prepend_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt,
                             ...);

/*
 * Print the last error details. If print_stack_trace is non-zero, also
 * print stack trace. `msg` is the message which gets prepended to the actual
 * error message, if it's NULL, then "MJS error" is used.
 */
void mjs_print_error(struct mjs *mjs, FILE *fp, const char *msg,
                     int print_stack_trace);

/*
 * return a string representation of an error.
 * the error string might be overwritten by calls to `mjs_set_errorf`.
 */
const char *mjs_strerror(struct mjs *mjs, enum mjs_err err);

/*
 * Sets whether *.jsc files are generated when *.js file is executed. By
 * default it's 0.
 *
 * If either `MJS_GENERATE_JSC` or `CS_MMAP` is off, then this function has no
 * effect.
 */
void mjs_set_generate_jsc(struct mjs *mjs, int generate_jsc);

/*
 * When invoked from a cfunction, returns number of arguments passed to the
 * current JS function call.
 */
int mjs_nargs(struct mjs *mjs);

/*
 * When invoked from a cfunction, returns n-th argument to the current JS
 * function call.
 */
mjs_val_t mjs_arg(struct mjs *mjs, int n);

/*
 * Sets return value for the current JS function call.
 */
void mjs_return(struct mjs *mjs, mjs_val_t v);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_CORE_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_ffi_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_FFI_PUBLIC_H_
#define MJS_FFI_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

enum mjs_ffi_ctype {
  MJS_FFI_CTYPE_NONE,
  MJS_FFI_CTYPE_USERDATA,
  MJS_FFI_CTYPE_CALLBACK,
  MJS_FFI_CTYPE_INT,
  MJS_FFI_CTYPE_BOOL,
  MJS_FFI_CTYPE_DOUBLE,
  MJS_FFI_CTYPE_FLOAT,
  MJS_FFI_CTYPE_CHAR_PTR,
  MJS_FFI_CTYPE_VOID_PTR,
  MJS_FFI_CTYPE_STRUCT_MG_STR_PTR,
  MJS_FFI_CTYPE_STRUCT_MG_STR,
  MJS_FFI_CTYPE_INVALID,
};

typedef void *(mjs_ffi_resolver_t)(void *handle, const char *symbol);

void mjs_set_ffi_resolver(struct mjs *mjs, mjs_ffi_resolver_t *dlsym);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_FFI_PUBLIC_H_ */
#ifndef MJS_EXPORT_INTERNAL_HEADERS
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_array_public.h"
#endif
/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

/*
 * === Arrays
 */

#ifndef MJS_ARRAY_PUBLIC_H_
#define MJS_ARRAY_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* Make an empty array object */
mjs_val_t mjs_mk_array(struct mjs *mjs);

/* Returns length on an array. If `arr` is not an array, 0 is returned. */
unsigned long mjs_array_length(struct mjs *mjs, mjs_val_t arr);

/* Insert value `v` in array `arr` at the end of the array. */
mjs_err_t mjs_array_push(struct mjs *mjs, mjs_val_t arr, mjs_val_t v);

/*
 * Return array member at index `index`. If `index` is out of bounds, undefined
 * is returned.
 */
mjs_val_t mjs_array_get(struct mjs *, mjs_val_t arr, unsigned long index);

/* Insert value `v` into `arr` at index `index`. */
mjs_err_t mjs_array_set(struct mjs *mjs, mjs_val_t arr, unsigned long index,
                        mjs_val_t v);

/* Returns true if the given value is an array */
int mjs_is_array(mjs_val_t v);

/* Delete value in array `arr` at index `index`, if it exists. */
void mjs_array_del(struct mjs *mjs, mjs_val_t arr, unsigned long index);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_ARRAY_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_core_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_CORE_PUBLIC_H_
#define MJS_CORE_PUBLIC_H_

#if !defined(_MSC_VER) || _MSC_VER >= 1700
#include <stdint.h>
#else
typedef unsigned __int64 uint64_t;
typedef int int32_t;
typedef unsigned char uint8_t;
#endif
#include <stdio.h>
#include <stddef.h>
/* Amalgamated: #include "mjs/src/mjs_license.h" */
/* Amalgamated: #include "mjs/src/mjs_features.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define MJS_ENABLE_DEBUG 1

/*
 *  Double-precision floating-point number, IEEE 754
 *
 *  64 bit (8 bytes) in total
 *  1  bit sign
 *  11 bits exponent
 *  52 bits mantissa
 *      7         6        5        4        3        2        1        0
 *  seeeeeee|eeeemmmm|mmmmmmmm|mmmmmmmm|mmmmmmmm|mmmmmmmm|mmmmmmmm|mmmmmmmm
 *
 * If an exponent is all-1 and mantissa is all-0, then it is an INFINITY:
 *  11111111|11110000|00000000|00000000|00000000|00000000|00000000|00000000
 *
 * If an exponent is all-1 and mantissa's MSB is 1, it is a quiet NaN:
 *  11111111|11111000|00000000|00000000|00000000|00000000|00000000|00000000
 *
 *  MJS NaN-packing:
 *    sign and exponent is 0xfff
 *    4 bits specify type (tag), must be non-zero
 *    48 bits specify value
 *
 *  11111111|1111tttt|vvvvvvvv|vvvvvvvv|vvvvvvvv|vvvvvvvv|vvvvvvvv|vvvvvvvv
 *   NaN marker |type|  48-bit placeholder for values: pointers, strings
 *
 * On 64-bit platforms, pointers are really 48 bit only, so they can fit,
 * provided they are sign extended
 */

typedef uint64_t mjs_val_t;

/* This if-0 is a dirty workaround to force etags to pick `struct mjs` */
#if 0
/* Opaque structure. MJS engine context. */
struct mjs {
  /* ... */
};
#endif

struct mjs;

typedef enum mjs_err {
  MJS_OK,
  MJS_SYNTAX_ERROR,
  MJS_REFERENCE_ERROR,
  MJS_TYPE_ERROR,
  MJS_OUT_OF_MEMORY,
  MJS_INTERNAL_ERROR,
  MJS_NOT_IMPLEMENTED_ERROR,
  MJS_FILE_READ_ERROR,
  MJS_BAD_ARGS_ERROR,

  MJS_ERRS_CNT
} mjs_err_t;
struct mjs;

/* Create MJS instance */
struct mjs *mjs_create();

struct mjs_create_opts {
  /* use non-default bytecode definition file, testing-only */
  const struct bf_code *code;
};

/*
 * Like `msj_create()`, but allows to customize initial MJS state, see `struct
 * mjs_create_opts`.
 */
struct mjs *mjs_create_opt(struct mjs_create_opts opts);

/* Destroy MJS instance */
void mjs_destroy(struct mjs *mjs);

mjs_val_t mjs_get_global(struct mjs *mjs);

/*
 * Tells the GC about an MJS value variable/field owned by C code.
 *
 * The user's C code should own mjs_val_t variables if the value's lifetime
 * crosses any invocation of `mjs_exec()` and friends, including `mjs_call()`.
 *
 * The registration of the variable prevents the GC from mistakenly treat the
 * object as garbage.
 *
 * User code should also explicitly disown the variables with `mjs_disown()`
 * once it goes out of scope or the structure containing the mjs_val_t field is
 * freed.
 *
 * Consider the following examples:
 *
 * Correct (owning is not necessary):
 * ```c
 * mjs_val_t res;
 * mjs_exec(mjs, "....some script", &res);
 * // ... use res somehow
 *
 * mjs_val_t res;
 * mjs_exec(mjs, "....some script2", &res);
 * // ... use new res somehow
 * ```
 *
 * WRONG:
 * ```c
 * mjs_val_t res1;
 * mjs_exec(mjs, "....some script", &res1);
 *
 * mjs_val_t res2;
 * mjs_exec(mjs, "....some script2", &res2);
 *
 * // ... use res1 (WRONG!) and res2
 * ```
 *
 * The code above is wrong, because after the second invocation of
 * `mjs_exec()`, the value of `res1` is invalidated.
 *
 * Correct (res1 is owned)
 * ```c
 * mjs_val_t res1 = MJS_UNDEFINED;
 * mjs_own(mjs, &res1);
 * mjs_exec(mjs, "....some script", &res1);
 *
 * mjs_val_t res2 = MJS_UNDEFINED;
 * mjs_exec(mjs, "....some script2", &res2);
 *
 * // ... use res1 and res2
 * mjs_disown(mjs, &res1);
 * ```
 *
 * NOTE that we explicly initialized `res1` to a valid value before owning it
 * (in this case, the value is `MJS_UNDEFINED`). Owning an uninitialized
 * variable is an undefined behaviour.
 *
 * Of course, it's not an error to own a variable even if it's not mandatory:
 * e.g. in the last example we could own both `res1` and `res2`. Probably it
 * would help us in the future, when we refactor the code so that `res2` has to
 * be owned, and we could forget to do that.
 *
 * Also, if the user code has some C function called from MJS, and in this C
 * function some MJS value (`mjs_val_t`) needs to be stored somewhhere and to
 * stay alive after the C function has returned, it also needs to be properly
 * owned.
 */
void mjs_own(struct mjs *mjs, mjs_val_t *v);

/*
 * Disowns the value previously owned by `mjs_own()`.
 *
 * Returns 1 if value is found, 0 otherwise.
 */
int mjs_disown(struct mjs *mjs, mjs_val_t *v);

mjs_err_t mjs_set_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt, ...);

/*
 * If there is no error message already set, then it's equal to
 * `mjs_set_errorf()`.
 *
 * Otherwise, an old message gets prepended with the new one, followed by a
 * colon. (the previously set error code is kept)
 */
mjs_err_t mjs_prepend_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt,
                             ...);

/*
 * Print the last error details. If print_stack_trace is non-zero, also
 * print stack trace. `msg` is the message which gets prepended to the actual
 * error message, if it's NULL, then "MJS error" is used.
 */
void mjs_print_error(struct mjs *mjs, FILE *fp, const char *msg,
                     int print_stack_trace);

/*
 * return a string representation of an error.
 * the error string might be overwritten by calls to `mjs_set_errorf`.
 */
const char *mjs_strerror(struct mjs *mjs, enum mjs_err err);

/*
 * Sets whether *.jsc files are generated when *.js file is executed. By
 * default it's 0.
 *
 * If either `MJS_GENERATE_JSC` or `CS_MMAP` is off, then this function has no
 * effect.
 */
void mjs_set_generate_jsc(struct mjs *mjs, int generate_jsc);

/*
 * When invoked from a cfunction, returns number of arguments passed to the
 * current JS function call.
 */
int mjs_nargs(struct mjs *mjs);

/*
 * When invoked from a cfunction, returns n-th argument to the current JS
 * function call.
 */
mjs_val_t mjs_arg(struct mjs *mjs, int n);

/*
 * Sets return value for the current JS function call.
 */
void mjs_return(struct mjs *mjs, mjs_val_t v);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_CORE_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_exec_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_EXEC_PUBLIC_H_
#define MJS_EXEC_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */
#include <stdio.h>

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

mjs_err_t mjs_exec(struct mjs *, const char *src, mjs_val_t *res);
mjs_err_t mjs_exec_buf(struct mjs *, const char *src, size_t, mjs_val_t *res);

mjs_err_t mjs_exec_file(struct mjs *mjs, const char *path, mjs_val_t *res);
mjs_err_t mjs_apply(struct mjs *mjs, mjs_val_t *res, mjs_val_t func,
                    mjs_val_t this_val, int nargs, mjs_val_t *args);
mjs_err_t mjs_call(struct mjs *mjs, mjs_val_t *res, mjs_val_t func,
                   mjs_val_t this_val, int nargs, ...);
mjs_val_t mjs_get_this(struct mjs *mjs);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_EXEC_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_ffi_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_FFI_PUBLIC_H_
#define MJS_FFI_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

enum mjs_ffi_ctype {
  MJS_FFI_CTYPE_NONE,
  MJS_FFI_CTYPE_USERDATA,
  MJS_FFI_CTYPE_CALLBACK,
  MJS_FFI_CTYPE_INT,
  MJS_FFI_CTYPE_BOOL,
  MJS_FFI_CTYPE_DOUBLE,
  MJS_FFI_CTYPE_FLOAT,
  MJS_FFI_CTYPE_CHAR_PTR,
  MJS_FFI_CTYPE_VOID_PTR,
  MJS_FFI_CTYPE_STRUCT_MG_STR_PTR,
  MJS_FFI_CTYPE_STRUCT_MG_STR,
  MJS_FFI_CTYPE_INVALID,
};

typedef void *(mjs_ffi_resolver_t)(void *handle, const char *symbol);

void mjs_set_ffi_resolver(struct mjs *mjs, mjs_ffi_resolver_t *dlsym);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_FFI_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_object_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_OBJECT_PUBLIC_H_
#define MJS_OBJECT_PUBLIC_H_

#include <stddef.h>
/* Amalgamated: #include "mjs/src/mjs_core_public.h" */
/* Amalgamated: #include "mjs/src/mjs_ffi_public.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*
 * Returns true if the given value is an object or array.
 */
int mjs_is_object(mjs_val_t v);

/* Make an empty object */
mjs_val_t mjs_mk_object(struct mjs *mjs);

/* C structure layout descriptor - needed by mjs_struct_to_obj */
struct mjs_c_struct_member {
  const char *name;
  size_t offset;
  enum mjs_ffi_ctype type;
};

/* Create flat JS object from a C memory descriptor */
mjs_val_t mjs_struct_to_obj(struct mjs *mjs, const void *base,
                            const struct mjs_c_struct_member *members);

/*
 * Lookup property `name` in object `obj`. If `obj` holds no such property,
 * an `undefined` value is returned.
 *
 * If `name_len` is ~0, `name` is assumed to be NUL-terminated and
 * `strlen(name)` is used.
 */
mjs_val_t mjs_get(struct mjs *mjs, mjs_val_t obj, const char *name,
                  size_t name_len);

/*
 * Like mjs_get but with a JS string.
 */
mjs_val_t mjs_get_v(struct mjs *mjs, mjs_val_t obj, mjs_val_t name);

/*
 * Like mjs_get_v but lookup the prototype chain.
 */
mjs_val_t mjs_get_v_proto(struct mjs *mjs, mjs_val_t obj, mjs_val_t key);

/*
 * Set object property. Behaves just like JavaScript assignment.
 */
mjs_err_t mjs_set(struct mjs *mjs, mjs_val_t obj, const char *name, size_t len,
                  mjs_val_t val);

/*
 * Like mjs_set but the name is already a JS string.
 */
mjs_err_t mjs_set_v(struct mjs *mjs, mjs_val_t obj, mjs_val_t name,
                    mjs_val_t val);

/*
 * Delete own property `name` of the object `obj`. Does not follow the
 * prototype chain.
 *
 * If `name_len` is ~0, `name` is assumed to be NUL-terminated and
 * `strlen(name)` is used.
 *
 * Returns 0 on success, -1 on error.
 */
int mjs_del(struct mjs *mjs, mjs_val_t obj, const char *name, size_t len);

/*
 * Iterate over `obj` properties.
 * First call should set `iterator` to MJS_UNDEFINED.
 * Return object's key (a string), or MJS_UNDEFINED when no more keys left.
 * Do not mutate the object during iteration.
 *
 * Example:
 *   mjs_val_t key, iter = MJS_UNDEFINED;
 *   while ((key = mjs_next(mjs, obj, &iter)) != MJS_UNDEFINED) {
 *     // Do something with the obj/key ...
 *   }
 */
mjs_val_t mjs_next(struct mjs *mjs, mjs_val_t obj, mjs_val_t *iterator);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_OBJECT_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_primitive_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_PRIMITIVE_PUBLIC_H_
#define MJS_PRIMITIVE_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* JavaScript `null` value */
#define MJS_NULL MJS_TAG_NULL

/* JavaScript `undefined` value */
#define MJS_UNDEFINED MJS_TAG_UNDEFINED

/* Function pointer type used in `mjs_mk_foreign_func`. */
typedef void (*mjs_func_ptr_t)(void);

/*
 * Make `null` primitive value.
 *
 * NOTE: this function is deprecated and will be removed in future releases.
 * Use `MJS_NULL` instead.
 */
mjs_val_t mjs_mk_null(void);

/* Returns true if given value is a primitive `null` value */
int mjs_is_null(mjs_val_t v);

/*
 * Make `undefined` primitive value.
 *
 * NOTE: this function is deprecated and will be removed in future releases.
 * Use `MJS_UNDEFINED` instead.
 */
mjs_val_t mjs_mk_undefined(void);

/* Returns true if given value is a primitive `undefined` value */
int mjs_is_undefined(mjs_val_t v);

/* Make numeric primitive value */
mjs_val_t mjs_mk_number(struct mjs *mjs, double num);

/*
 * Returns number value stored in `mjs_val_t` as `double`.
 *
 * Returns NaN for non-numbers.
 */
double mjs_get_double(struct mjs *mjs, mjs_val_t v);

/*
 * Returns number value stored in `mjs_val_t` as `int`. If the number value is
 * not an integer, the fraction part will be discarded.
 *
 * If the given value is a non-number, or NaN, the result is undefined.
 */
int mjs_get_int(struct mjs *mjs, mjs_val_t v);

/*
 * Like mjs_get_int but ensures that the returned type
 * is a 32-bit signed integer.
 */
int32_t mjs_get_int32(struct mjs *mjs, mjs_val_t v);

/* Returns true if given value is a primitive number value */
int mjs_is_number(mjs_val_t v);

/*
 * Make JavaScript value that holds C/C++ `void *` pointer.
 *
 * A foreign value is completely opaque and JS code cannot do anything useful
 * with it except holding it in properties and passing it around.
 * It behaves like a sealed object with no properties.
 *
 * NOTE:
 * Only valid pointers (as defined by each supported architecture) will fully
 * preserved. In particular, all supported 64-bit architectures (x86_64, ARM-64)
 * actually define a 48-bit virtual address space.
 * Foreign values will be sign-extended as required, i.e creating a foreign
 * value of something like `(void *) -1` will work as expected. This is
 * important because in some 64-bit OSs (e.g. Solaris) the user stack grows
 * downwards from the end of the address space.
 *
 * If you need to store exactly sizeof(void*) bytes of raw data where
 * `sizeof(void*)` >= 8, please use byte arrays instead.
 */
mjs_val_t mjs_mk_foreign(struct mjs *mjs, void *ptr);

/*
 * Make JavaScript value that holds C/C++ function pointer, similarly to
 * `mjs_mk_foreign`.
 */
mjs_val_t mjs_mk_foreign_func(struct mjs *mjs, mjs_func_ptr_t fn);

/*
 * Returns `void *` pointer stored in `mjs_val_t`.
 *
 * Returns NULL if the value is not a foreign pointer.
 */
void *mjs_get_ptr(struct mjs *mjs, mjs_val_t v);

/* Returns true if given value holds `void *` pointer */
int mjs_is_foreign(mjs_val_t v);

mjs_val_t mjs_mk_boolean(struct mjs *mjs, int v);
int mjs_get_bool(struct mjs *mjs, mjs_val_t v);
int mjs_is_boolean(mjs_val_t v);

mjs_val_t mjs_mk_function(struct mjs *mjs, size_t off);
int mjs_is_function(mjs_val_t v);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_PRIMITIVE_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_string_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_STRING_PUBLIC_H_
#define MJS_STRING_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */

#define MJS_STRING_LITERAL_MAX_LEN 128

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*
 * Creates a string primitive value.
 * `str` must point to the utf8 string of length `len`.
 * If `len` is ~0, `str` is assumed to be NUL-terminated and `strlen(str)` is
 * used.
 *
 * If `copy` is non-zero, the string data is copied and owned by the GC. The
 * caller can free the string data afterwards. Otherwise (`copy` is zero), the
 * caller owns the string data, and is responsible for not freeing it while it
 * is used.
 */
mjs_val_t mjs_mk_string(struct mjs *mjs, const char *str, size_t len, int copy);

/* Returns true if given value is a primitive string value */
int mjs_is_string(mjs_val_t v);

/*
 * Returns a pointer to the string stored in `mjs_val_t`.
 *
 * String length returned in `len`, which is allowed to be NULL. Returns NULL
 * if the value is not a string.
 *
 * JS strings can contain embedded NUL chars and may or may not be NUL
 * terminated.
 *
 * CAUTION: creating new JavaScript object, array, or string may kick in a
 * garbage collector, which in turn may relocate string data and invalidate
 * pointer returned by `mjs_get_string()`.
 *
 * Short JS strings are embedded inside the `mjs_val_t` value itself. This
 * is why a pointer to a `mjs_val_t` is required. It also means that the string
 * data will become invalid once that `mjs_val_t` value goes out of scope.
 */
const char *mjs_get_string(struct mjs *mjs, mjs_val_t *v, size_t *len);

/*
 * Returns a pointer to the string stored in `mjs_val_t`.
 *
 * Returns NULL if the value is not a string or if the string is not compatible
 * with a C string.
 *
 * C compatible strings contain exactly one NUL char, in terminal position.
 *
 * All strings owned by the MJS engine (see `mjs_mk_string()`) are guaranteed to
 * be NUL terminated. Out of these, those that don't include embedded NUL chars
 * are guaranteed to be C compatible.
 */
const char *mjs_get_cstring(struct mjs *mjs, mjs_val_t *v);

/*
 * Returns the standard strcmp comparison code after comparing a JS string a
 * with a possibly non null-terminated string b. NOTE: the strings are equal
 * only if their length is equal, i.e. the len field doesn't imply strncmp
 * behaviour.
 */
int mjs_strcmp(struct mjs *mjs, mjs_val_t *a, const char *b, size_t len);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_STRING_PUBLIC_H_ */
#ifdef MJS_MODULE_LINES
#line 1 "mjs/src/mjs_util_public.h"
#endif
/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_UTIL_PUBLIC_H_
#define MJS_UTIL_PUBLIC_H_

/* Amalgamated: #include "mjs/src/mjs_core_public.h" */
#include <stdio.h>

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

const char *mjs_typeof(mjs_val_t v);

void mjs_fprintf(mjs_val_t v, struct mjs *mjs, FILE *fp);
void mjs_sprintf(mjs_val_t v, struct mjs *mjs, char *buf, size_t buflen);

#if MJS_ENABLE_DEBUG

void mjs_disasm(const uint8_t *code, size_t len);
void mjs_dump(struct mjs *mjs, int do_disasm);

#endif

/*
 * Returns the filename corresponding to the given bcode offset.
 */
const char *mjs_get_bcode_filename_by_offset(struct mjs *mjs, int offset);

/*
 * Returns the line number corresponding to the given bcode offset.
 */
int mjs_get_lineno_by_offset(struct mjs *mjs, int offset);

/*
 * Returns bcode offset of the corresponding call frame cf_num, where 0 means
 * the currently executing function, 1 means the first return address, etc.
 *
 * If given cf_num is too large, -1 is returned.
 */
int mjs_get_offset_by_call_frame_num(struct mjs *mjs, int cf_num);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_UTIL_PUBLIC_H_ */
#endif /* MJS_EXPORT_INTERNAL_HEADERS */
