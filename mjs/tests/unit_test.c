#include "mjs.h"

/* clang-format off */

#define STRINGIFY(x) #x
#define MJS_ENABLE_DEBUG 1
#include "common/cs_dirent.h"
#include "common/test_util.h"
#include "mjs.c"

#include <stdbool.h>

#define ASSERT_EXEC_OK(_exec_)                                              \
  do {                                                                      \
    mjs_err_t err = _exec_;                                                 \
    if (err != MJS_OK) {                                                    \
      fprintf(stderr, "exec error: %d [%s]\n", mjs->error, mjs->error_msg); \
    }                                                                       \
    ASSERT_EQ(err, MJS_OK);                                                 \
    if (mjs->stack.len != 0) {                                              \
      fprintf(stderr, "stack len is not zero: %d\n", (int)mjs->stack.len);  \
    }                                                                       \
    ASSERT_EQ(mjs->stack.len, 0);                                           \
  } while (0)

#define CHECK_NUMERIC(str, result)                        \
  do {                                                    \
    ASSERT_EXEC_OK(mjs_exec(mjs, str, &res));             \
    ASSERT_EQ(mjs_get_double(mjs, res), (double) result); \
  } while (0)

static void cleanup_mjs(struct mjs **mjs) {
  if (*mjs != NULL) {
    mjs_destroy(*mjs);
  }
  *mjs = NULL;
}

static void cleanup_dir(DIR **d) {
  if (*d != NULL) {
    closedir(*d);
  }
  *d = NULL;
}

static void test_this_plus_arg(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_val_t arg0 = mjs_arg(mjs, 0);
  mjs_val_t arg1 = mjs_arg(mjs, 1);
  mjs_val_t this_obj = mjs_get_this(mjs);
  mjs_val_t num = mjs_get(mjs, this_obj, "foo", ~0);

  res = mjs_mk_number(mjs,
      mjs_get_double(mjs, num) + mjs_get_double(mjs, arg0) - mjs_get_double(mjs, arg1)
      );

  mjs_return(mjs, res);
}

const char *test_arithmetic() {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  CHECK_NUMERIC("0x64", 100);
  CHECK_NUMERIC("0x7fffffff", 0x7fffffff);
  CHECK_NUMERIC("0xffffffff", 0xffffffff);
  CHECK_NUMERIC("123.4", 123.4);
  CHECK_NUMERIC("200+50", 250);
  CHECK_NUMERIC("1-2*3", -5);
  CHECK_NUMERIC("1-2+3", 2);
  CHECK_NUMERIC("200-50", 150);
  CHECK_NUMERIC("200*50", 10000);
  CHECK_NUMERIC("200/50", 4);
  CHECK_NUMERIC("200 % 21", 11);
  CHECK_NUMERIC("100 << 3", 800);
  CHECK_NUMERIC("(0-14) >> 2", -4);
  CHECK_NUMERIC("(0-14) >>> 2", 1073741820);
  CHECK_NUMERIC("6 & 3", 2);
  CHECK_NUMERIC("6 | 3", 7);
  CHECK_NUMERIC("6 ^ 3", 5);

  // /* double arithmetic */
  // CHECK_NUMERIC("0.1 + 0.2", 0.3);
  CHECK_NUMERIC("123.4 + 0.1", 123.5);

  // /* test operation+assignment */
  CHECK_NUMERIC("let a = 200; a += 50; a", 250);
  CHECK_NUMERIC("let a = 200; a -= 50; a", 150);
  CHECK_NUMERIC("let a = 200; a *= 50; a", 10000);
  CHECK_NUMERIC("let a = 200; a /= 50; a", 4);
  CHECK_NUMERIC("let a = 200; a %= 21; a", 11);
  CHECK_NUMERIC("let a = 100; a <<= 3; a", 800);
  CHECK_NUMERIC("let a = 0-14; a >>= 2; a", -4);
  CHECK_NUMERIC("let a = 0-14; a >>>= 2; a", 1073741820);
  CHECK_NUMERIC("let a = 6; a &= 3; a", 2);
  CHECK_NUMERIC("let a = 6; a |= 3; a", 7);
  CHECK_NUMERIC("let a = 6; a ^= 3; a", 5);

  // /* unary ops */
  CHECK_NUMERIC("~10", -11);
  CHECK_NUMERIC("-100", -100);
  CHECK_NUMERIC("+100", 100);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);
  return NULL;
}

const char *test_block(void) {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  CHECK_NUMERIC("if (1) 2", 2);
  ASSERT_EXEC_OK(mjs_exec(mjs, "if (0) 2;", &res));
  ASSERT_EQ(res, MJS_UNDEFINED);
  CHECK_NUMERIC("{let a = 42; }", 42);
  CHECK_NUMERIC("let a = 1, b = 2; { let a = 3; b += a; } b;", 5);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);
  return NULL;
}

const char *test_function(void) {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  CHECK_NUMERIC("let f = function(){ 1; }; 1;", 1);
  CHECK_NUMERIC("let f = function(a){ 1; }; 1;", 1);
  CHECK_NUMERIC("let f = function(a,b){ 1; }; 1;", 1);
  CHECK_NUMERIC("let f = function(a,b){ return a; }; f(1,2);", 1);
  CHECK_NUMERIC("let f = function(a,b){ return b; }; f(1,2);", 2);
  CHECK_NUMERIC("let f = function(a,b){ return b; }; f(1,2,3);", 2);
  ASSERT_EXEC_OK(mjs_exec(mjs, "let f = function(a,b){return b;};f(1);", &res));
  ASSERT_EQ(res, MJS_UNDEFINED);
  CHECK_NUMERIC("function foo(a,b){ return b; }; foo(1,2,3);", 2);
  CHECK_NUMERIC("let bar = function foo(a,b){ return b; }; foo(1,2,3) + bar(4,5);", 7);

  CHECK_NUMERIC("let f = function(a){return a.b;}; f({b: {c: 7}}).c;", 7);
  CHECK_NUMERIC("function f(){}; f ? 1 : 2", 1);
  CHECK_NUMERIC("function f(x){return x ? {x:x} : 0}; f(f).x(0);", 0);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);
  return NULL;
}

const char *test_cfunction(void) {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set(mjs, mjs_get_global(mjs), "test_this_plus_arg", ~0, mjs_mk_foreign(mjs, test_this_plus_arg));

  CHECK_NUMERIC("let o = {foo: 100, f:test_this_plus_arg}; o.f(20, 5);", 100+20-5);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);
  return NULL;
}

const char *test_exec(void) {
  struct mjs *mjs = NULL;
  DIR *dirp;
  struct dirent *dp;
  const char *dir = "tests";

  if ((dirp = (opendir(dir))) != NULL) {
    while ((dp = readdir(dirp)) != NULL) {
      char path[256];
      const char *prefix = "test_";
      mjs_val_t res = MJS_UNDEFINED;

      if (strncmp(dp->d_name, prefix, strlen(prefix)) != 0) continue;
      snprintf(path, sizeof(path), "%s/%s", dir, dp->d_name);
      LOG(LL_INFO, ("executing %s", path));

      mjs = mjs_create();
      mjs_own(mjs, &res);
      ASSERT_EXEC_OK(mjs_exec_file(mjs, path, &res));
      ASSERT_EQ(mjs_get_bool(mjs, res), 1);
      mjs_disown(mjs, &res);
      ASSERT_EQ(mjs->owned_values.len, 0);
      cleanup_mjs(&mjs);
    }
  }
  cleanup_dir(&dirp);
  return NULL;
}

const char *test_if(void) {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  CHECK_NUMERIC( STRINGIFY(
        let a = 0; let b = 1; if (a === 0) { b = 10; }; b;
        ), 10);
  CHECK_NUMERIC( STRINGIFY(
        let a = 0; let b = 1; if (a === 1) { b = 10; }; b;
        ), 1);
  CHECK_NUMERIC( STRINGIFY(
        let a = 0; let b = 1; if (a === 0) { b = 10; } else { b = 20; }; b;
        ), 10);
  CHECK_NUMERIC( STRINGIFY(
        let a = 0; let b = 1; if (a === 1) { b = 10; } else { b = 20; }; b;
        ), 20);
  CHECK_NUMERIC( STRINGIFY(
        let a = 0;
        let b = 1;
        if (a === 1) {
          b = 10;
        } else if (a === 1) {
          b = 20;
        };
        b;
        ), 1);
  CHECK_NUMERIC( STRINGIFY(
        let a = 0;
        let b = 1;
        if (a === 1) {
          b = 10;
        } else if (a === 1) {
          b = 20;
        } else {
          b = 30;
        };
        b;
        ), 30);
  CHECK_NUMERIC( STRINGIFY(
        let a = 0;
        let b = 1;
        if (a === 1) {
          b = 10;
        } else if (a === 0) {
          b = 20;
        } else {
          b = 30;
        };
        b;
        ), 20);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);
  return NULL;
}

const char *test_comparison(void) {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 > 2", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 > 1", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 > 0", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 >= 2", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 >= 1", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 >= 0", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 < 2", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 > 1", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 < 0", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 <= 2", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 <= 1", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 <= 0", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 === 1", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 === 2", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 !== 1", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 !== 2", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "0 === 0", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "0 !== 0", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 0));

  ASSERT_EXEC_OK(mjs_exec(mjs, "null === null", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "undefined === undefined", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "true === true", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "false === false", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' === 'foo'", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' === 'fo0'", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 0));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' === undefined", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 0));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' === null", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 0));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' !== undefined", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' !== null", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o1={}, o2={}; o1===o2", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 0));

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o1={}, o2=o1; o1===o2", &res));
  ASSERT_EQ(res, mjs_mk_boolean(mjs, 1));

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);
  return NULL;
}

const char *test_logic() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs, "!true", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "!false", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "true || false", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "true || true", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "true && false", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "false && false", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "!(false && true) || (true || false)", &res));
  ASSERT_EQ(mjs_is_boolean(res), 1);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 || 2", &res));
  ASSERT_EQ(mjs_is_boolean(res), 0);
  ASSERT_EQ(mjs_get_double(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "0 || 2", &res));
  ASSERT_EQ(mjs_is_boolean(res), 0);
  ASSERT_EQ(mjs_get_double(mjs, res), 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 || 2 || 3", &res));
  ASSERT_EQ(mjs_is_boolean(res), 0);
  ASSERT_EQ(mjs_get_double(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 || 0 || 3", &res));
  ASSERT_EQ(mjs_is_boolean(res), 0);
  ASSERT_EQ(mjs_get_double(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 && 2 && 3", &res));
  ASSERT_EQ(mjs_is_boolean(res), 0);
  ASSERT_EQ(mjs_get_double(mjs, res), 3);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 && 0 && 3", &res));
  ASSERT_EQ(mjs_is_boolean(res), 0);
  ASSERT_EQ(mjs_get_double(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 && 2 || 3", &res));
  ASSERT_EQ(mjs_is_boolean(res), 0);
  ASSERT_EQ(mjs_get_double(mjs, res), 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 && 0 || 3", &res));
  ASSERT_EQ(mjs_is_boolean(res), 0);
  ASSERT_EQ(mjs_get_double(mjs, res), 3);

  ASSERT_EXEC_OK(mjs_exec(mjs, "1 || 0 && 3", &res));
  ASSERT_EQ(mjs_is_boolean(res), 0);
  ASSERT_EQ(mjs_get_double(mjs, res), 1);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}

int testfunc1(int a, int b, int c, int d) {
  // printf("called testfunc1 with a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
  return a + b + c + d;
}

static const char *test_func1() {
  struct ffi_arg res;
  struct ffi_arg args[4];

  res.ctype = FFI_CTYPE_WORD;
  res.v.i = 0;
  ffi_set_word(&args[0], 1);
  ffi_set_word(&args[1], 2);
  ffi_set_word(&args[2], 3);
  ffi_set_word(&args[3], 4);

  ffi_call((ffi_fn_t) testfunc1, 4, &res, args);

  ASSERT_EQ(res.v.i, 10);

  return NULL;
}

int testfunc2(int a, double b) {
  // printf("called testfunc2 with a=%d, b=%lg\n", a, b);
  return a + b;
}

static const char *test_func2() {
  struct ffi_arg res;
  struct ffi_arg args[2];
  res.ctype = FFI_CTYPE_WORD;
  ffi_set_word(&args[0], 1);
  ffi_set_double(&args[1], 2);

  ffi_call((ffi_fn_t) testfunc2, 2, &res, args);

  ASSERT_EQ(res.v.i, 3);

  return NULL;
}

int testfunc3(double a, double b) {
  // printf("called testfunc3 with a=%lg, b=%lg\n", a, b);
  return a + b;
}

static const char *test_func3() {
  struct ffi_arg res;
  struct ffi_arg args[2];
  res.ctype = FFI_CTYPE_WORD;
  ffi_set_double(&args[0], 1);
  ffi_set_double(&args[1], 2);

  ffi_call((ffi_fn_t) testfunc3, 2, &res, args);

  ASSERT_EQ(res.v.i, 3);

  return NULL;
}

double testfunc4(int a, int b, int c, int d) {
  // printf("called testfunc4 with a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
  return a + b + c + d;
}

static const char *test_func4() {
  struct ffi_arg res;
  struct ffi_arg args[4];

  res.ctype = FFI_CTYPE_DOUBLE;
  res.v.d = 0;
  ffi_set_word(&args[0], 1);
  ffi_set_word(&args[1], 2);
  ffi_set_word(&args[2], 3);
  ffi_set_word(&args[3], 4);

  ffi_call((ffi_fn_t) testfunc4, 4, &res, args);

  ASSERT_EQ(res.v.d, 10);

  return NULL;
}

double testfunc5(int a, double b) {
  // printf("called testfunc1 with a=%d, b=%lg\n", a, b);
  return a + b;
}

static const char *test_func5() {
  struct ffi_arg res;
  struct ffi_arg args[2];
  res.ctype = FFI_CTYPE_DOUBLE;
  ffi_set_word(&args[0], 1);
  ffi_set_double(&args[1], 2);

  ffi_call((ffi_fn_t) testfunc5, 2, &res, args);

  ASSERT_EQ(res.v.d, 3);

  return NULL;
}

double testfunc6(double a, double b) {
  // printf("called testfunc6 with a=%lg, b=%lg\n", a, b);
  return a + b;
}

static const char *test_func6() {
  struct ffi_arg res;
  struct ffi_arg args[2];
  res.ctype = FFI_CTYPE_DOUBLE;
  ffi_set_double(&args[0], 1);
  ffi_set_double(&args[1], 2);

  ffi_call((ffi_fn_t) testfunc6, 2, &res, args);

  ASSERT_EQ(res.v.d, 3);

  return NULL;
}

const void *ffi_get_null(void) {
  return NULL;
}

int ffi_test_i2i(int a0, int a1) {
  return a0 - a1;
}

int ffi_test_iib(int a0, bool b) {
  return a0 - (b ? 10 : 20);
}

bool ffi_test_bi(int a0) {
  return a0 > 50;
}

int ffi_test_i5i(int a0, int a1, int a2, int a3, int a4) {
  return (a0 - a1) / ((a2 - a3) * a4);
}

int ffi_test_i6i(int a0, int a1, int a2, int a3, int a4, int a5) {
  return (a0 - a1) / ((a2 - a3) * a4) + a5 * 2;
}

double ffi_test_d2d(double a, double b) {
  return 12.34 + a + b;
}

int ffi_test_iid(int a, double b) {
  return 1234 + a + b * 100;
}

const char *ffi_test_s1s(const char *str) {
  return str;
}

/* callback void(*)(userdata) {{{ */
typedef void(cb_vu)(void *userdata);
static cb_vu *saved_cb_vu = NULL;
void *saved_cb_vu_arg = NULL;

void ffi_test_cb_vu(int a, int b, cb_vu *cb, void *userdata) {
  (void) a;
  (void) b;
  saved_cb_vu = cb;
  saved_cb_vu_arg = userdata;
}

void ffi_dummy(void) {
}
/* }}} */

/* callback void(*)(int, userdata) {{{ */
typedef void(cb_viu)(int a, void *userdata);
static cb_viu *saved_cb_viu = NULL;
void *saved_cb_viu_arg = NULL;

void ffi_test_cb_viu(int a, cb_viu *cb, int b, void *userdata) {
  (void) a;
  (void) b;
  saved_cb_viu = cb;
  saved_cb_viu_arg = userdata;
}
/* }}} */

/* callback void(*)(userdata, int) {{{ */
typedef void(cb_vui)(void *userdata, int a);
static cb_vui *saved_cb_vui = NULL;
void *saved_cb_vui_arg = NULL;

void ffi_test_cb_vui(int a, void *userdata, int b, cb_vui *cb) {
  (void) a;
  (void) b;
  saved_cb_vui = cb;
  saved_cb_vui_arg = userdata;
}
/* }}} */

/* callback int(*)(int, userdata, int) {{{ */
typedef int(cb_iiui)(int a, void *userdata, int b);
static cb_iiui *saved_cb_iiui = NULL;
void *saved_cb_iiui_arg = NULL;

void ffi_test_cb_iiui(void *userdata, cb_iiui *cb, int a) {
  (void) a;
  saved_cb_iiui = cb;
  saved_cb_iiui_arg = userdata;
}

void ffi_test_cb_iiui2(int a, int b, int c, int d, cb_iiui *cb,
                       void *userdata) {
  (void) a;
  (void) b;
  (void) c;
  (void) d;
  saved_cb_iiui = cb;
  saved_cb_iiui_arg = userdata;
}
/* }}} */

/* callback void(*)(int, int, int, int, int, userdata) {{{ */
typedef void (cb_viiiiiu)(int a, int b, int c, int d, int e, void *userdata);
static cb_viiiiiu *saved_cb_viiiiiu = NULL;
void *saved_cb_viiiiiu_arg = NULL;

void ffi_test_cb_viiiiiu(cb_viiiiiu *cb, void *userdata) {
  saved_cb_viiiiiu = cb;
  saved_cb_viiiiiu_arg = userdata;
}
/* }}} */

void *stub_dlsym(void *handle, const char *name) {
  (void) handle;
  if (strcmp(name, "ffi_get_null") == 0) return ffi_get_null;
  if (strcmp(name, "ffi_test_i2i") == 0) return ffi_test_i2i;
  if (strcmp(name, "ffi_test_iib") == 0) return ffi_test_iib;
  if (strcmp(name, "ffi_test_bi") == 0) return ffi_test_bi;
  if (strcmp(name, "ffi_test_i5i") == 0) return ffi_test_i5i;
  if (strcmp(name, "ffi_test_i6i") == 0) return ffi_test_i6i;
  if (strcmp(name, "ffi_test_d2d") == 0) return ffi_test_d2d;
  if (strcmp(name, "ffi_test_iid") == 0) return ffi_test_iid;
  if (strcmp(name, "ffi_test_s1s") == 0) return ffi_test_s1s;
  if (strcmp(name, "ffi_dummy") == 0) return ffi_dummy;
  if (strcmp(name, "ffi_test_cb_vu") == 0) return ffi_test_cb_vu;
  if (strcmp(name, "ffi_test_cb_viu") == 0) return ffi_test_cb_viu;
  if (strcmp(name, "ffi_test_cb_vui") == 0) return ffi_test_cb_vui;
  if (strcmp(name, "ffi_test_cb_iiui") == 0) return ffi_test_cb_iiui;
  if (strcmp(name, "ffi_test_cb_iiui2") == 0) return ffi_test_cb_iiui2;
  if (strcmp(name, "ffi_test_cb_viiiiiu") == 0) return ffi_test_cb_viiiiiu;
  if (strcmp(name, "malloc") == 0) return malloc;
  if (strcmp(name, "calloc") == 0) return calloc;
  if (strcmp(name, "free") == 0) return free;
  if (strcmp(name, "mjs_mem_get_ptr") == 0) return mjs_mem_get_ptr;
  if (strcmp(name, "mjs_mem_get_uint") == 0) return mjs_mem_get_uint;
  if (strcmp(name, "mjs_mem_set_uint") == 0) return mjs_mem_set_uint;
  return NULL;
}

const char *test_call_ffi() {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  mjs_set(mjs, mjs_get_global(mjs), "ffi_test_i2i", ~0,
          mjs_mk_string(mjs, "int ffi_test_i2i(int, int)", ~0, 1));
  ASSERT_EQ(mjs_exec(mjs, "ffi_test_i2i(44, 2)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 42);

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_i2i(2, 3)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), -1);

  /* booleans should be converted to ints properly */
  ASSERT_EQ(mjs_exec(mjs, "ffi_test_i2i(44, false)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 44);

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_i2i(44, true)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 43);

  /* function which takes bool */
  mjs_set(mjs, mjs_get_global(mjs), "ffi_test_iib", ~0,
      mjs_mk_string(mjs, "int ffi_test_iib(int, bool)", ~0, 1));
  ASSERT_EQ(mjs_exec(mjs, "ffi_test_iib(40, true)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 40-10);

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_iib(40, false)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 40-20);

  /* function which returns bool */
  mjs_set(mjs, mjs_get_global(mjs), "ffi_test_bi", ~0,
      mjs_mk_string(mjs, "bool ffi_test_bi(int)", ~0, 1));
  ASSERT_EQ(mjs_exec(mjs, "ffi_test_bi(50)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), false);

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_bi(51)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), true);

  mjs_set(
      mjs, mjs_get_global(mjs), "ffi_test_i5i", ~0,
      mjs_mk_string(mjs, "int ffi_test_i5i(int, int, int, int, int)", ~0, 1));
  ASSERT_EQ(mjs_exec(mjs, "ffi_test_i5i(114, 14, 7, 1, 4)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), (114 - 14) / ((7 - 1) * 4));

  mjs_set(mjs, mjs_get_global(mjs), "ffi_test_i6i", ~0,
          mjs_mk_string(mjs, "int ffi_test_i6i(int, int, int, int, int, int)",
                        ~0, 1));
  ASSERT_EQ(mjs_exec(mjs, "ffi_test_i6i(114, 14, 7, 1, 4, 11)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_double(mjs, res), (114 - 14) / ((7 - 1) * 4) + 11 * 2);

  mjs_set(mjs, mjs_get_global(mjs), "ffi_test_s1s", ~0,
          mjs_mk_string(mjs, "char *ffi_test_s1s(char *)", ~0, 1));
  ASSERT_EQ(mjs_exec(mjs, "ffi_test_s1s('foo')", &res), MJS_OK);
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "foo");

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_s1s('\\x01')", &res), MJS_OK);
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "\x01");

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_s1s('\\x01\\x00')", &res), MJS_OK);
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "\x01");

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_s1s('\\x00')", &res), MJS_OK);
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "");

  ASSERT_EQ(
      mjs_exec(mjs, "ffi('double ffi_test_d2d(double,double)')(3.71, 1.28)",
               &res),
      MJS_OK);
  ASSERT_LT(fabs(mjs_get_double(mjs, res) - 17.33), 0.0001);

  ASSERT_EQ(
      mjs_exec(mjs, "ffi('int ffi_test_iid(int,double)')(300, 1.28)",
        &res),
      MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), (1234 + 300 + 128));

  /* Test calling ffi-ed function from JS function */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          function f1(a) {
            return a * ffi_test_i2i(a+1, 3);
          };
          f1(15);
          ), &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 15*((15+1)-3));


  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);

  return NULL;
}

const char *test_call_ffi_cb_vu() {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_test_cb_vu = ffi(
            "void ffi_test_cb_vu(int, int, void(*)(userdata), userdata)"
          );
        ), &res));

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let glob_var = 123;
          let cb = function(userdata){
            glob_var += 456 + userdata;
          };
          ffi_test_cb_vu(100, 200, cb, 1);
        ), &res));

  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), 123);
  saved_cb_vu(saved_cb_vu_arg);
  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), (123 + 457));

  /* Also, perform some tests of callback data memory management */

  /* Make sure ffi arguments are properly allocated */
  ASSERT_EQ((uintptr_t)mjs->ffi_cb_args->next, (uintptr_t)NULL);

  /* Assign the same callback again: no new arguments should be allocated */
  ASSERT_EXEC_OK(mjs_exec(mjs, "ffi_test_cb_vu(100, 200, cb, 1);", &res));
  ASSERT_EQ((uintptr_t)mjs->ffi_cb_args->next, (uintptr_t)NULL);

  /* Assign callback with different userdata: new arguments should be allocated */
  ASSERT_EXEC_OK(mjs_exec(mjs, "ffi_test_cb_vu(100, 200, cb, 2);", &res));
  ASSERT_GT((uintptr_t)mjs->ffi_cb_args->next, (uintptr_t)NULL);

  /* Try to free non-existing signature */
  ASSERT_EXEC_OK(mjs_exec(mjs, "ffi_cb_free(cb, 3);", &res));
  ASSERT_EQ(res, mjs_mk_number(mjs, 0));

  /* Free first sig */
  ASSERT_EXEC_OK(mjs_exec(mjs, "ffi_cb_free(cb, 1);", &res));
  ASSERT_EQ(res, mjs_mk_number(mjs, 1));
  ASSERT_EQ((uintptr_t)mjs->ffi_cb_args->next, (uintptr_t)NULL);
  ASSERT_EQ(mjs_get_int(mjs, mjs->ffi_cb_args->userdata), 2);

  /* Try to free it again */
  ASSERT_EXEC_OK(mjs_exec(mjs, "ffi_cb_free(cb, 1);", &res));
  ASSERT_EQ(res, mjs_mk_number(mjs, 0));

  /* Free second sig */
  ASSERT_EXEC_OK(mjs_exec(mjs, "ffi_cb_free(cb, 2);", &res));
  ASSERT_EQ(res, mjs_mk_number(mjs, 1));
  ASSERT_EQ((uintptr_t)mjs->ffi_cb_args, (uintptr_t)NULL);

  /* Try to free it again */
  ASSERT_EXEC_OK(mjs_exec(mjs, "ffi_cb_free(cb, 2);", &res));
  ASSERT_EQ(res, mjs_mk_number(mjs, 0));

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);

  return NULL;
}

const char *test_call_ffi_cb_viu() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_test_cb_viu = ffi(
            "void ffi_test_cb_viu(int, void (*)(int, userdata), int, userdata)"
            );
          ), &res));

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let glob_var = 123;
          let cb = function(num, userdata){
            glob_var = 456 - num + userdata;
          };
          ffi_test_cb_viu(100, cb, 200, 1);
        ), &res));

  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), 123);
  saved_cb_viu(10, saved_cb_viu_arg);
  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), 447);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}


const char *test_call_ffi_cb_vui() {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_test_cb_vui = ffi(
            "void ffi_test_cb_vui(int, userdata, int, void(*)(userdata, int))"
            );
          ), &res));

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let glob_var = 123;
          let cb = function(userdata, num){
            glob_var = 456 - num + userdata;
          };
          ffi_test_cb_vui(100, 3, 200, cb);
          ), &res));

  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), 123);
  saved_cb_vui(saved_cb_vui_arg, 20);
  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), 439);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);

  return NULL;
}

const char *test_call_ffi_cb_vui_unused_userdata() {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_test_cb_vui = ffi(
            "void ffi_test_cb_vui(int, userdata, int, void(*)(userdata, int))"
            );
          ), &res));

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let glob_var = 123;
          let cb = function(userdata, num){
            glob_var = 456 - num;
          };
          ffi_test_cb_vui(100, undefined, 200, cb);
          ), &res));

  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), 123);
  saved_cb_vui(saved_cb_vui_arg, 20);
  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), 456 - 20);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);

  return NULL;
}

const char *test_call_ffi_cb_iiui() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_test_cb_iiui = ffi(
            "void ffi_test_cb_iiui(userdata, int(*)(int, userdata, int), int)"
            );
          ), &res));

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let glob_var = 123;
          let cb = function(num1, userdata, num2, num3){
            glob_var += (num1 - userdata) + num2 + num2;
            return glob_var - 1;
          };
          ffi_test_cb_iiui(3, cb, 100);
          ), &res));

  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), 123);
  ASSERT_EQ(saved_cb_iiui(50, saved_cb_iiui_arg, 20), (123 + 87 - 1));
  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), (123 + 87));

  /* --- */

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_test_cb_iiui2 = ffi(
            "void ffi_test_cb_iiui2(int, int, int, int, int(*)(int, userdata, int), userdata)"
            );
          ), &res));

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let glob_var = 123;
          let cb = function(num1, userdata, num2){
            glob_var += (num1 - userdata) + num2 + num2;
            return glob_var - 1;
          };
          ffi_test_cb_iiui2(100, 200, 300, 400, cb, 4);
          ), &res));

  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), 123);
  ASSERT_EQ(saved_cb_iiui(50, saved_cb_iiui_arg, 20), (123 + 86 - 1));
  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), (123 + 86));

  /* --- */

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_test_cb_viiiiiu = ffi(
            "void ffi_test_cb_viiiiiu(void(*)(int, int, int, int, int, userdata), userdata)"
            );
          ), &res));

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let glob_var = 100;
          let cb = function(num1, num2, num3, num4, num5, userdata){
            glob_var += num1 + num2*2 + num3*3 - num4*4 + num5*5 - userdata;
          };
          ffi_test_cb_viiiiiu(cb, 123);
          ), &res));

  ASSERT_EQ(mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)), 100);
  saved_cb_viiiiiu(2, 7, 11, 17, 31, saved_cb_viiiiiu_arg);
  ASSERT_EQ(
      mjs_get_int(mjs, mjs_get(mjs, mjs_get_global(mjs), "glob_var", ~0)),
      (100 + 2 + 7*2 + 11*3 - 17*4 + 31*5 - 123)
      );

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}

const char *test_call_ffi_cb_err() {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  /* test wrong signatures */

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_dummy = ffi(
            "void ffi_dummy(int, int, foo(*)(userdata), userdata)"
            );
          ), &res));
  ASSERT_EQ(mjs_exec( mjs,
        "ffi_dummy(100, 200, function(){return 1;}, 1);",
        &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "failed to call FFI signature \"void ffi_dummy(int, int, foo(*)(userdata), userdata)\": bad callback signature: \"foo(*)(userdata)\": failed to parse val type \"foo\"");

  /* --- */

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_dummy = ffi(
            "void ffi_dummy(int, int, void(*)(userdata, foo), userdata)"
            );
          ), &res));
  ASSERT_EQ(mjs_exec( mjs,
        "ffi_dummy(100, 200, function(){return 1;}, 1);",
        &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "failed to call FFI signature \"void ffi_dummy(int, int, void(*)(userdata, foo), userdata)\": bad callback signature: \"void(*)(userdata, foo)\": failed to parse val type \"foo\"");

  /* --- */

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_dummy = ffi(
            "void ffi_dummy(int, int, void(*)(), userdata)"
            );
          ), &res));
  ASSERT_EQ(mjs_exec( mjs,
        "ffi_dummy(100, 200, function(){return 1;}, 1);",
        &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "failed to call FFI signature \"void ffi_dummy(int, int, void(*)(), userdata)\": bad callback signature: \"void(*)()\": no userdata arg");

  /* --- */

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_dummy = ffi(
            "void ffi_dummy(int, int, void(*)(userdata))"
            );
          ), &res));
  ASSERT_EQ(mjs_exec( mjs,
        "ffi_dummy(100, 200, function(){return 1;});",
        &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "failed to call FFI signature \"void ffi_dummy(int, int, void(*)(userdata))\": need both function and userdata");

  /* --- */

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_dummy = ffi(
            "void ffi_dummy(userdata, int, void(*)(userdata), userdata)"
            );
          ), &res));
  ASSERT_EQ(mjs_exec( mjs,
        "ffi_dummy(100, 200, function(){return 1;}, 1);",
        &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "failed to call FFI signature \"void ffi_dummy(userdata, int, void(*)(userdata), userdata)\": two or more userdata args: #0 and 3");

  /* --- */

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ffi_dummy = ffi(
            "void ffi_dummy(int, int, void(*)(userdata, userdata), userdata)"
            );
          ), &res));
  ASSERT_EQ(mjs_exec( mjs,
        "ffi_dummy(100, 200, function(){return 1;}, 1);",
        &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "failed to call FFI signature \"void ffi_dummy(int, int, void(*)(userdata, userdata), userdata)\": bad callback signature: \"void(*)(userdata, userdata)\": more than one userdata arg: #0 and #1");

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);

  return NULL;
}

const char *test_errors(void) {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EQ(mjs_exec(mjs, "x", &res), MJS_REFERENCE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "[x] is not defined");
  ASSERT_EQ(mjs_exec(mjs, "let o = {}; o.a", &res), MJS_OK);
  ASSERT_EQ(res, MJS_UNDEFINED);
  ASSERT_EQ(mjs_exec(mjs, "let o = {}; o.a.b", &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "type error");

  ASSERT_EQ(mjs_exec(mjs, "---", &res), MJS_SYNTAX_ERROR);
  ASSERT_EQ(mjs_exec(mjs, "1 != 2", &res), MJS_NOT_IMPLEMENTED_ERROR);
  ASSERT_STREQ(mjs->error_msg, "Use !==, not !=");
  ASSERT_EQ(mjs_exec(mjs, "1 == 2", &res), MJS_NOT_IMPLEMENTED_ERROR);
  ASSERT_STREQ(mjs->error_msg, "Use ===, not ==");

  ASSERT_EQ(mjs_exec(mjs, "var x;", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "[var] is not implemented");
  ASSERT_EQ(mjs_exec(mjs, "try {};", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "[try] is not implemented");
  ASSERT_EQ(mjs_exec(mjs, "do { 2 } while (0);", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "[do] is not implemented");
  ASSERT_EQ(mjs_exec(mjs, "instanceof [];", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "[instanceof] is not implemented");
  ASSERT_EQ(mjs_exec(mjs, "new String;", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "[new] is not implemented");
  ASSERT_EQ(mjs_exec(mjs, "switch x", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "[switch] is not implemented");
  ASSERT_EQ(mjs_exec(mjs, "throw 1;", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "[throw] is not implemented");
  ASSERT_EQ(mjs_exec(mjs, "with (x) {};", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "[with] is not implemented");
  ASSERT_EQ(mjs_exec(mjs, "void 2;", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "[void] is not implemented");

  ASSERT_EQ(mjs_exec(mjs, "//\n/* */\n// \n...", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "parse error at line 4: [...]");

  ASSERT_EQ(mjs_exec(mjs, "(1+2}+3", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "parse error at line 1: [}+3]");

  ASSERT_EQ(mjs_exec(mjs, "for (k in {a:1}) 1;", &res), MJS_REFERENCE_ERROR);

  ASSERT_EQ(mjs_exec(mjs, "'foo' + 2", &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "implicit type conversion is prohibited");

  ASSERT_EQ(mjs_exec(mjs, "let s = 'foo'; s += 12", &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "implicit type conversion is prohibited");

  ASSERT_EQ(mjs_exec(mjs, "load('foo/bar/bazzz')", &res), MJS_FILE_READ_ERROR);
  ASSERT_STREQ(mjs->error_msg, "failed to read file \"foo/bar/bazzz\"");

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);
  return NULL;
}

const char *test_varint(void) {
#define TEST_VARINT_CASE(number, encoded_length)               \
  do {                                                         \
    uint8_t buf[100];                                          \
    int llen;                                                  \
    ASSERT_EQ(cs_varint_encode((number), buf), (encoded_length)); \
    ASSERT_EQ(cs_varint_decode(buf, &llen), (number));            \
    ASSERT_EQ(llen, (encoded_length));                         \
  } while (0)

  TEST_VARINT_CASE(0, 1);
  TEST_VARINT_CASE(1, 1);
  TEST_VARINT_CASE(127, 1);
  TEST_VARINT_CASE(128, 2);
  TEST_VARINT_CASE(0xffff, 3);
  TEST_VARINT_CASE(0xffffff, 4);
  TEST_VARINT_CASE(0xffffffff, 5);
  TEST_VARINT_CASE(0xffffffffff, 6);

  return NULL;
};

const char *test_this() {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs, "this", &res));
  ASSERT_EQ(res, MJS_UNDEFINED);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        "let f = function(){return this}; f()",
        &res));
  ASSERT_EQ(res, MJS_UNDEFINED);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        "let f = function(){return this.foo};"
        "let o = {foo: 100, f: f, bar: 200}; o.f()",
        &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 100);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let o = ({
            foo: 100,
            bar: 150,
            f: function() {
              let a = this.bar - this.foo;
              let o = {
                foo: 10,
                f: function(){ return this.foo; }
              };
              /* Invoke another function with function invocation pattern */
              a *= o.f();
              /* Make sure that `this` here is back */
              a += this.foo;
              return a;
            }
          });
          o.f();
          ), &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 600);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a;
          function f(foo) {
            a = foo;
          }
          let o = ({
            s: 123,
            x: function(str) {
              this.s = str;
              f(this.s);
            },
          });
          o.x(456);
          a;
          ), &res));

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a;
          function f(foo) {
            a = foo;
          }
          let o = ({
            s: 123,
            x: function(str) {
              this.s = str;
              f(this.s);
            },
          });
          let foo = 456;
          o.x(foo);
          a;
          ), &res));

  ASSERT_EQ(mjs_get_int(mjs, res), 456);

  /* Test that `this` is handled by the GC correctly */
  /* TODO(dfrank): uncomment when f2().f() is not a syntax error */
#if 0
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let f1 = function() {
            return this.a + this.b;
          };
          let f2 = function() {
            return ({a: 1, b: 2, f: f1});
          };
          f2().f();
          ), &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 3);
#endif

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);

  return NULL;
}

const char *test_while() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EQ(mjs_exec(mjs, "let i=0; while(i<10) {i+=1;} i;", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 10);

  ASSERT_EQ(mjs_exec(mjs, "let i=50; let j=100; while(i<10) {i+=1;j+=1;} j;", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 100);

  /* while loop inside of a function */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          let f = function(x, y) {
            while (x < y) {
              x += 1;
              s += ".";
            }
            return x;
          };
          f(10, 20);
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "..........");

  /* break before side effect */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          let f = function(x, y) {
            while (x < y) {
              x += 1;
              if (x === 15) {
                break;
              }
              s += ".";
            }
            return x;
          };
          f(10, 20);
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "....");

  /* break after side effect */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          let f = function(x, y) {
            while (x < y) {
              x += 1;
              s += ".";
              if (x === 15) {
                break;
              }
            }
            return x;
          };
          f(10, 20);
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), ".....");

  /* continue */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          let f = function(x, y) {
            while (x < y) {
              x += 1;
              if (x === 15) {
                continue;
              }
              s += ".";
            }
            return x;
          };
          f(10, 20);
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), ".........");

  /* Nested while loops */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          let ch = "foo";
          let f = function(x, y) {
            while (x < y) {
            let ch = ".";
              x += 1;
              if (x === 15) {

                let a = 0;
                while (a < 10) {
                let ch = "-";
                  a++;
                  if (a === 2) {
                    continue;
                  }
                  if (a === 5) {
                    break;
                  }
                  s += ch;
                }

                continue;
              }
              s += ch;
            }
            return x;
          };
          f(10, 20);
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "....---.....");

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}

const char *test_for_loop() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let i = 123; let s="";
          for (i = 0; i < 10; i++) {
            s += "_" + JSON.stringify(i);
          }
          s += "_" + JSON.stringify(i);
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_0_1_2_3_4_5_6_7_8_9_10");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let i = 123; let s="";
          for (let i = 0; i < 10; i++) {
            s += "_" + JSON.stringify(i);
          }
          s += "_" + JSON.stringify(i);
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_0_1_2_3_4_5_6_7_8_9_123");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let i = 123; let s="";
          for (let i = 1, j = 11; i < j; i++) {
            s += "_" + JSON.stringify(i);
          }
          s += "_" + JSON.stringify(i);
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_1_2_3_4_5_6_7_8_9_10_123");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let i; let s="";
          for (i = 2; i < 11; i++) s += "_" + JSON.stringify(i);
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_2_3_4_5_6_7_8_9_10");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let i; let s="";
          for (i = 3; i < 100; i++) {
            if (i === 7) {
              continue;
            }
            s += "_" + JSON.stringify(i);
            if (i === 10) {
              break;
            }
            s += "|" + JSON.stringify(i * 2);
          };
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_3|6_4|8_5|10_6|12_8|16_9|18_10");

  /* TODO(dfrank) implement */
#if 0
  /* Try to omit various parts of for loop decl {{{ */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let i = 3; let s="";
          for (;;) {
            i++;
            if (i === 7) {
              continue;
            }
            s += "_" + JSON.stringify(i);
            if (i === 10) {
              break;
            }
            s += "|" + JSON.stringify(i * 2);
          };
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_4|8_5|10_6|12_8|16_9|18_10");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let i = 3; let s="";
          for (;; i++) {
            if (i === 7) {
              continue;
            }
            s += "_" + JSON.stringify(i);
            if (i === 10) {
              break;
            }
            s += "|" + JSON.stringify(i * 2);
          };
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_3|6_4|8_5|10_6|12_8|16_9|18_10");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let i = 3; let s="";
          for (; true;) {
            i++;
            if (i === 7) {
              continue;
            }
            s += "_" + JSON.stringify(i);
            if (i === 10) {
              break;
            }
            s += "|" + JSON.stringify(i * 2);
          };
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_4|8_5|10_6|12_8|16_9|18_10");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let i; let s="";
          for (i = 3; ;) {
            i++;
            if (i === 7) {
              continue;
            }
            s += "_" + JSON.stringify(i);
            if (i === 10) {
              break;
            }
            s += "|" + JSON.stringify(i * 2);
          };
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_4|8_5|10_6|12_8|16_9|18_10");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let i; let s="";
          for (i = 3; ;i++) {
            if (i === 7) {
              continue;
            }
            s += "_" + JSON.stringify(i);
            if (i === 10) {
              break;
            }
            s += "|" + JSON.stringify(i * 2);
          };
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_3|6_4|8_5|10_6|12_8|16_9|18_10");
  /* }}} */
#endif

  /* Mix functions, for loops, while loops, break, continue */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let i; let s="";
          let f1 = function(a) {
            let b = a-5;
            let s="";
            while(b < a+10) {
              b++;
              if (b === a-2) {
                continue;
              }
              if (b === a-1) {
                let i;
                for (i = 0; i < 50; i++) {
                  s += ".";
                  if (i === 4) {
                    break;
                  }
                }
              }
              s += "|" + JSON.stringify(b);
              if (b === a) {
                break;
              }
            }
            return s;
          };
          for (i = 0; i < 10; i++) {
            if (i === 2) {
              continue;
            }
            s += "_" + JSON.stringify(i) + ":" + f1(i);
          };
          s;
        ), &res));
        ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_0:|-4|-3.....|-1|0_1:|-3|-2.....|0|1_3:|-1|0.....|2|3_4:|0|1.....|3|4_5:|1|2.....|4|5_6:|2|3.....|5|6_7:|3|4.....|6|7_8:|4|5.....|7|8_9:|5|6.....|8|9");

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}

const char *test_for_in_loop() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let o = ({foo: 1, bar: 2}); let s="";
          for (let k in o) {
            s += "_" + k + ":" + JSON.stringify(o[k]);
          }
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_bar:2_foo:1");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let o = ({foo: 1, bar: 2, baz: 3, four: 4, five: 5}); let s="";
          for (let k in o) {
            if (k === "four") {
              continue;
            }
            s += "_" + k + ":" + JSON.stringify(o[k]);
            if (k === "bar") {
              break;
            }
          }
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_five:5_baz:3_bar:2");

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}

const char *test_primitives() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs, "0x87654321", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), (int)0x87654321);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}

const char *test_objects() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {}; o.b", &res));
  ASSERT_EQ(res, MJS_UNDEFINED);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100}; o.b", &res));
  ASSERT_EQ(res, MJS_UNDEFINED);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o.a + o.b;", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 102);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o.b = 123; o.a + o.b;", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 223);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o.c = 123; o.a + o.b + o.c;", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 225);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o.a += 5; o.a + o.b", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 107);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o.a -= 5; o.a + o.b", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 97);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o.a *= 5; o.a + o.b", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 502);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o.a /= 5; o.a + o.b", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 22);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o.a %= 21; o.a + o.b", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 18);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o.a <<= 2; o.a + o.b", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 402);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o.a >>= 1; o.a + o.b", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 52);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 0-14, b: 2}; o.a >>= 2; o.a + o.b", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), -4 + 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 0-14, b: 2}; o.a >>>= 2; o.a + o.b", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 1073741820 + 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 6, b: 2}; o.a &= 3; o.a", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 6, b: 2}; o.a |= 3; o.a", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 7);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 6, b: 2}; o.a ^= 3; o.a", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 5);

  /* test calling obj properties */

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, f: function(a){return a+1;}}; o.a + o.f(123);", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 224);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100}; o.f = function(a){return a+2;}; o.a + o.f(123);", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 225);

  /* test subscript syntax */

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {}; o['b']", &res));
  ASSERT_EQ(res, MJS_UNDEFINED);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100}; o['b']", &res));
  ASSERT_EQ(res, MJS_UNDEFINED);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o['a'] + o['b'];", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 102);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o['b'] = 123; o['a'] + o['b'];", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 223);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o['c'] = 123; o['a'] + o['b'] + o['c'];", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 225);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o['a'] += 5; o['a'] + o['b']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 107);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o['a'] -= 5; o['a'] + o['b']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 97);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o['a'] *= 5; o['a'] + o['b']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 502);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let pname = 'a'; let o = {a: 100, b: 2}; o[pname] /= 5; o['a'] + o['b']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 22);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o['a'] %= 21; o['a'] + o['b']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 18);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o['a'] <<= 2; o['a'] + o['b']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 402);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100, b: 2}; o['a'] >>= 1; o['a'] + o['b']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 52);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 0-14, b: 2}; o['a'] >>= 2; o['a'] + o['b']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), -4 + 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 0-14, b: 2}; o['a'] >>>= 2; o['a'] + o['b']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 1073741820 + 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 6, b: 2}; o['a'] &= 3; o['a']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 6, b: 2}; o['a'] |= 3; o['a']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 7);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 6, b: 2}; o['a'] ^= 3; o['a']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 5);

  /* test subscript syntax which ix not a string */

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {}; o['123'] = 1234; o[123]", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 1234);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {}; o['true'] = 100; o[1 === 1]", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 100);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {}; o['false'] = 200; o[1 === 0]", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 200);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {}; o['null'] = 300; o[null]", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 300);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {}; o[null] = 300; o['null']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 300);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {}; o['undefined'] = 400; o[undefined]", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 400);

  /* Converting from an object to string results in an error */
  ASSERT_EQ(
      mjs_exec(mjs, "let o = {}; o[{}]", &res),
      MJS_TYPE_ERROR
      );

  /* test pre- and post-increments */

  /* TODO(dfrank): fix preincrement */
#if 0
  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; ++o.a; o.a", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 21);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; ++o.a;", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 21);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; ++o.a + 1", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 22);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; ++o.a + o.a", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 42);
#endif

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o.a++; o.a", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 21);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o.a++;", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 20);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o.a++ + 1", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 21);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o.a++ + o.a", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 41);

  /* TODO(dfrank): fix preincrement */
#if 0
  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; --o.a; o.a", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 19);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; --o.a;", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 19);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; --o.a - 1", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 18);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; --o.a - o.a", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 0);
#endif

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o.a--; o.a", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 19);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o.a--;", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 20);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o.a-- - 1", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 19);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o.a-- - o.a", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 1);

  /* test pre- and post-increments for subscript syntax */

  /* TODO(dfrank): fix preincrement */
#if 0
  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; ++o['a']; o['a']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 21);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; ++o['a'];", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 21);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; ++o['a'] + 1", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 22);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; ++o['a'] + o['a']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 42);
#endif

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o['a']++; o['a']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 21);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o['a']++;", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 20);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o['a']++ + 1", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 21);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o['a']++ + o['a']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 41);

  /* TODO(dfrank): fix preincrement */
#if 0
  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; --o['a']; o['a']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 19);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; --o['a'];", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 19);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; --o['a'] - 1", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 18);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; --o['a'] - o['a']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 0);
#endif

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o['a']--; o['a']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 19);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o['a']--;", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 20);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o['a']-- - 1", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 19);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 20}; o['a']-- - o['a']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 1);

  /* Nested object variations */
  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 100);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo.bar['baz']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 100);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo['bar']['baz']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 100);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo['bar'].baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 100);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o['foo']['bar'].baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 100);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o['foo'].bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 100);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o['foo']['bar']['baz']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 100);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo.bar.baz++ + o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 201);

  /* TODO(dfrank): fix preincrement */
#if 0
  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; ++o.foo.bar.baz + o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 202);
#endif

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo.bar['baz']++ + o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 201);

  /* TODO(dfrank): fix preincrement */
#if 0
  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; ++o.foo.bar['baz'] + o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 202);
#endif

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo['bar']['baz']++ + o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 201);

  /* TODO(dfrank): fix preincrement */
#if 0
  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; ++o.foo['bar']['baz'] + o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 202);
#endif

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo.bar.baz += 20; o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 120);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo.bar['baz'] += 20; o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 120);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo['bar']['baz'] += 20; o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 120);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo.bar.baz = 20; o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 20);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo.bar['baz'] = 20; o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 20);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {foo: {bar: {baz: 100}}}; o.foo['bar']['baz'] = 20; o.foo.bar.baz", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 20);

  /* Object returned from the function */

  ASSERT_EXEC_OK(mjs_exec(mjs, "function f(){ return {foo: 123} }; f().foo", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 123);

  ASSERT_EXEC_OK(mjs_exec(mjs, "function f(){ return {foo: 123} }; f()['foo']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 123);

  /* Prototypes with Object.create() */

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let ret = "";
          let p = {foo: 1};
          let o1 = Object.create(p);
          let o2 = Object.create(p);

          ret += "p_foo:"  + JSON.stringify(p.foo) + "_";
          ret += "o1_foo:" + JSON.stringify(o1.foo) + "_";
          ret += "o2_foo:" + JSON.stringify(o2.foo) + "_";

          o1.foo = 2;

          ret += "p_foo:"  + JSON.stringify(p.foo) + "_";
          ret += "o1_foo:" + JSON.stringify(o1.foo) + "_";
          ret += "o2_foo:" + JSON.stringify(o2.foo) + "_";

          p.foo = 3;

          ret += "p_foo:"  + JSON.stringify(p.foo) + "_";
          ret += "o1_foo:" + JSON.stringify(o1.foo) + "_";
          ret += "o2_foo:" + JSON.stringify(o2.foo) + "_";

          ret;
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res),
      "p_foo:1_o1_foo:1_o2_foo:1_"
      "p_foo:1_o1_foo:2_o2_foo:1_"
      "p_foo:3_o1_foo:2_o2_foo:3_"
      );

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}

const char *test_arrays() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let a = []; a.b", &res));
  ASSERT_EQ(res, MJS_UNDEFINED);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let a = [100, 40]; a[0] - a[1]", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 60);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let a = [100, 40]; a['0'] - a['1']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 60);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let a = [100, 40]; a.foo = 200; a['foo']", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 200);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let a = [];", &res));
  ASSERT_EQ(mjs_is_object(res), 1);
  ASSERT_EQ(mjs_is_array(res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let a = {};", &res));
  ASSERT_EQ(mjs_is_object(res), 1);
  ASSERT_EQ(mjs_is_array(res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let a = [100, 40]; a.length", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let a = [100, 40]; a[10] = undefined; a.length", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 11);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([1, 2, 3, 4, 5]);
          let ret=a.splice(1, 1, 100);
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "[2]___[1,100,3,4,5]");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([1, 2, 3, 4, 5]);
          let ret=a.splice(1, 2, 100);
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "[2,3]___[1,100,4,5]");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([1, 2, 3, 4, 5]);
          let ret=a.splice(1, 2, 100, 101, 102, 103);
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "[2,3]___[1,100,101,102,103,4,5]");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([1, 2, 3, 4, 5, 6, 7, 8, 9]);
          let ret=a.splice(1, 5, 100, 101);
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "[2,3,4,5,6]___[1,100,101,7,8,9]");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([1, 2, 3, 4, 5]);
          let ret=a.splice(1, 3);
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "[2,3,4]___[1,5]");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([1, 2, 3, 4, 5]);
          let ret=a.splice(0, 3);
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "[1,2,3]___[4,5]");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([1, 2, 3, 4, 5]);
          let ret=a.splice(2);
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "[3,4,5]___[1,2]");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([1, 2, 3, 4, 5]);
          let ret=a.splice(2,1000);
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "[3,4,5]___[1,2]");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([1, 2, 3, 4, 5]);
          let ret=a.splice(2,1000,100,101);
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "[3,4,5]___[1,2,100,101]");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([1, 2, 3, 4, 5]);
          let ret=a.splice(0,3,100,101);
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "[1,2,3]___[100,101,4,5]");


  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([1, 2, 3]);
          let ret=a.splice(1,0,7);
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "[]___[1,7,2,3]");

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}

const char *test_json() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        "let o = {foo: 1, bar: 'hey', arr: [1, 2, {foo: 100,}], 'null': null, 'undefined': undefined}; "
        "JSON.stringify(o)",
        &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "{\"null\":null,\"arr\":[1,2,{\"foo\":100}],\"bar\":\"hey\",\"foo\":1}");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        "JSON.stringify(\"foo\")",
        &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "\"foo\"");

  /* Test circular links and sparse arrays */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        "o.arr[10] = o;"
        "JSON.stringify(o)",
        &res));
  ASSERT_STREQ(
      mjs_get_cstring(mjs, &res),
      "{\"null\":null,\"arr\":[1,2,{\"foo\":100},null,null,null,null,null,null,null,[Circular]],\"bar\":\"hey\",\"foo\":1}"
      );

  /* Test parse */
  const char *json_val = "{\"null\":null,\"arr\":[1,2,{\"foo\":100}],\"bar\":\"hey\",\"foo\":1}";
  ASSERT_EXEC_OK(mjs_exec(mjs,
        "let o = {foo: 1, bar: 'hey', arr: [1, 2, {foo: 100}], 'null': null, 'undefined': undefined}; "
        "let s = JSON.stringify(o);"
        "s",
        &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), json_val);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        /*
         * NOTE: each stringification reverses the order of keys, so in order
         * to get the same value, we need to do parse/stringify twice.
         */
        "JSON.stringify(JSON.parse(JSON.stringify(JSON.parse(s))))",
        &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), json_val);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}

const char *test_string() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs, "''.length", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "'f'.length", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "'fo'.length", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo'.length", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 3);

  ASSERT_EXEC_OK(mjs_exec(mjs, "'ы'.length", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "'\\x00' === '\\x00'", &res));
  ASSERT(mjs_is_truthy(mjs, res));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'\\x00'.length", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "'\x12' === '\\x12'", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  /* subscripts */

  ASSERT_EXEC_OK(mjs_exec(mjs, "'abc'[0] === 'a'", &res));
  ASSERT(mjs_is_truthy(mjs, res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abc'[1] === 'b'", &res));
  ASSERT(mjs_is_truthy(mjs, res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abc'[2] === 'c'", &res));
  ASSERT(mjs_is_truthy(mjs, res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abc'[3] === undefined", &res));
  ASSERT(mjs_is_truthy(mjs, res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abc'[-1] === undefined", &res));
  ASSERT(mjs_is_truthy(mjs, res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "'ы'[0] === '\xd1'", &res));
  ASSERT(mjs_is_truthy(mjs, res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "'ы'[1] === '\x8b'", &res));
  ASSERT(mjs_is_truthy(mjs, res));

  /* slice */
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.slice(0)", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "abcdef");
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.slice(1)", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "bcdef");
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.slice(5)", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "f");
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.slice(6)", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "");
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.slice(999)", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "");
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.slice(-2)", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "ef");
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.slice(-999)", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "abcdef");

  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.slice(1, 3)", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "bc");
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.slice(2, 2)", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "");
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.slice(2, 1)", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "");
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.slice(2, -2)", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "cd");
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.slice(2, -999)", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "");

  ASSERT_EQ(mjs_exec( mjs, "'abcdef'.slice()", &res), MJS_TYPE_ERROR);
  ASSERT_EQ(mjs_exec( mjs, "'abcdef'.slice('foo')", &res), MJS_TYPE_ERROR);
  ASSERT_EQ(mjs_exec( mjs, "'abcdef'.slice(0, 'foo')", &res), MJS_TYPE_ERROR);

  /* charCodeAt */
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.charCodeAt(0)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 'a');

  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.charCodeAt(-1)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 'f');

  ASSERT_EXEC_OK(mjs_exec(mjs, "'\\xff'.charCodeAt(0)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 255);

  ASSERT_EXEC_OK(mjs_exec(mjs, "'\\xff'.charCodeAt(1)", &res));
  ASSERT_EQ(res, MJS_UNDEFINED);

  /* concatenation */

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' + 'bar' === 'foobar'", &res));
  ASSERT(mjs_is_truthy(mjs, res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo1234567890' + 'asdfghjkl' === 'foo1234567890asdfghjkl'", &res));
  ASSERT(mjs_is_truthy(mjs, res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' + '' === 'foo'", &res));
  ASSERT(mjs_is_truthy(mjs, res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "'' + 'foo' === 'foo'", &res));
  ASSERT(mjs_is_truthy(mjs, res));

  ASSERT_EXEC_OK(mjs_exec(mjs, "let a = 'x'; a += 'y'; a", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "xy");
  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 'x'}; o.a += 'z'; o.a", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "xz");

  /* no autoconversion */
  ASSERT_EQ(mjs_exec( mjs, "'foo' + 123", &res), MJS_TYPE_ERROR);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}

const char *test_call_api() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t func = MJS_UNDEFINED;
  mjs_own(mjs, &func);

  /* function with no arguments */
  ASSERT_EQ(mjs_exec(mjs, "let a=123; function(){ a += 1; return a; }", &func), MJS_OK);

  mjs_val_t res = MJS_UNDEFINED;
  mjs_val_t obj = MJS_UNDEFINED;
  mjs_own(mjs, &res);
  mjs_own(mjs, &obj);

  ASSERT_EQ(mjs_call(mjs, &res, func, MJS_UNDEFINED, 0), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 124);

  ASSERT_EQ(mjs_call(mjs, &res, func, MJS_UNDEFINED, 0), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 125);

  /* function with 1 argument */
  ASSERT_EQ(mjs_exec(mjs, "function(a){ return a - 1; }", &func), MJS_OK);

  ASSERT_EQ(mjs_call(mjs, &res, func, MJS_UNDEFINED, 1, mjs_mk_number(mjs, 100)), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 99);

  ASSERT_EQ(mjs_call(mjs, &res, func, MJS_UNDEFINED, 1, mjs_mk_number(mjs, 123)), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 122);

  /* function with 4 arguments */
  ASSERT_EQ(mjs_exec(mjs, "function(a, b, c, d){ return a - b + c + d; }", &func), MJS_OK);

  ASSERT_EQ(mjs_call(mjs, &res, func, MJS_UNDEFINED, 4, mjs_mk_number(mjs, 100),
        mjs_mk_number(mjs, 70),
        mjs_mk_number(mjs, 2), mjs_mk_number(mjs, 3)), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 35);

  /* test `this` */
  ASSERT_EQ(mjs_exec(mjs, "function(){ return this + 10; }", &func), MJS_OK);

  ASSERT_EQ(mjs_call(mjs, &res, func, mjs_mk_number(mjs, 5), 0), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 15);

  ASSERT_EQ(mjs_exec(mjs, "let o = {foo: 100, bar: 200}; o", &obj), MJS_OK);

  ASSERT_EQ(mjs_exec(mjs, "function(){ return this.foo; }", &func), MJS_OK);

  ASSERT_EQ(mjs_call(mjs, &res, func, obj, 0), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 100);

  mjs_disown(mjs, &obj);
  mjs_disown(mjs, &res);
  mjs_disown(mjs, &func);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}

const char *test_long_jump() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  CHECK_NUMERIC( STRINGIFY(
        let a = 0;
        let i;
        for (i = 0; i < 10; i++) {
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
          a += 1; a += 1; a += 1; a += 1; a += 1;
        }
        a;
        ), 1000);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);

  return NULL;
}

const char *test_foreign_str() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  uint8_t *ptr = NULL;

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let calloc = ffi('void *calloc(int, int)');
          let ptr = calloc(100, 1);
          let str = fstr(ptr, 3);
          ptr
          ), &res));
  ptr = (uint8_t *)mjs_get_ptr(mjs, res);

  ASSERT_EXEC_OK(mjs_exec(mjs, "str.length", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 3);

  ASSERT_EXEC_OK(mjs_exec(mjs, "str[0] === '\\x00'", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "str === '\\x00\\x00\\x00'", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ptr[0] = 'a';
  ptr[2] = 'b';

  ASSERT_EXEC_OK(mjs_exec(mjs, "str === 'a\\x00b'", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let str2 = fstr(ptr, 2, 10); str2", &res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "str2 === 'b\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00'", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  /* TODO(dfrank): make foreign strings mutable? */

  free(ptr);
  ptr = NULL;

  return NULL;
}

const char *test_foreign_ptr() {
  struct mjs *mjs __attribute__((cleanup(cleanup_mjs))) = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let get_null = ffi('void *ffi_get_null()');
          let ptr = get_null();
          ptr === null
          ), &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let calloc = ffi('void *calloc(int, int)');
          let free = ffi('void free(void *)');
          let ptr = calloc(100, 1);
          free(ptr);
          ptr === null
          ), &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  return NULL;
}

const char *test_dataview(void) {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  uint8_t buf[20] = "abcd1234 :-)\xff\xff\xff\xff";
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  ASSERT_EQ(mjs_mem_get_uint(buf + 12, 4, 1), 0xffffffff);
  ASSERT_EQ(mjs_mem_get_uint(buf + 12, 2, 1), 0xffff);
  ASSERT_EQ(mjs_mem_get_uint(buf + 12, 1, 1), 0xff);
  ASSERT_EQ(mjs_mem_get_int(buf + 12, 1, 1), -1);
  ASSERT_EQ(mjs_mem_get_int(buf + 12, 4, 1), -1);
  ASSERT_EQ(mjs_mem_get_int(buf + 12, 2, 1), -1);

  mjs_mem_set_int(buf + 8, -1, 2, 0);
  ASSERT_EQ(mjs_mem_get_uint(buf + 8, 2, 0), 0xffff);

  mjs_set(mjs, mjs_get_global(mjs), "buf", ~0, mjs_mk_foreign(mjs, buf));
  ASSERT_EXEC_OK(mjs_exec(mjs, "let peek = ffi('void *mjs_mem_get_ptr(void*,int)')", &res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "let peeku = ffi('int mjs_mem_get_uint(void*,int,int)')", &res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "let pokeu = ffi('int mjs_mem_set_uint(void*,int,int,int)')", &res));

  ASSERT_EXEC_OK(mjs_exec(mjs, "let b2 = peek('booo', 0);", &res));

  CHECK_NUMERIC("peeku(buf, 1, 1)", 'a');
  CHECK_NUMERIC("peeku(peek(buf,1), 1, 1)", 'b');
  CHECK_NUMERIC("peeku(buf, 2, 1)", 0x6162);
  CHECK_NUMERIC("peeku(buf, 2, 0)", 0x6261);
  CHECK_NUMERIC("peeku(buf, 3, 1)", 0x616263);
  CHECK_NUMERIC("peeku(buf, 4, 1)", 0x61626364);

  /* TODO(lsm): fix this - make FFI marshal unsigned values */
  CHECK_NUMERIC("peeku(peek(buf,12), 4, 1)", -1);

  mjs_disown(mjs, &res);
  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);
  return NULL;
}

static const char *run_all_tests(const char *filter, double *total_elapsed) {
  cs_log_set_level(2);
  RUN_TEST(test_arithmetic);
  RUN_TEST(test_block);
  RUN_TEST(test_function);
  RUN_TEST(test_cfunction);
  RUN_TEST(test_exec);
  RUN_TEST(test_if);
  RUN_TEST(test_comparison);
  RUN_TEST(test_logic);
  RUN_TEST(test_errors);
  RUN_TEST(test_this);
  RUN_TEST(test_while);
  RUN_TEST(test_for_loop);
  RUN_TEST(test_for_in_loop);
  RUN_TEST(test_primitives);
  RUN_TEST(test_objects);
  RUN_TEST(test_arrays);
  RUN_TEST(test_json);
  RUN_TEST(test_string);
  RUN_TEST(test_call_api);
  RUN_TEST(test_long_jump);
  RUN_TEST(test_foreign_str);
  RUN_TEST(test_foreign_ptr);

  /* FFI */
  RUN_TEST(test_func1);
  RUN_TEST(test_func2);
  RUN_TEST(test_func3);
  RUN_TEST(test_func4);
  RUN_TEST(test_func5);
  RUN_TEST(test_func6);

  RUN_TEST(test_call_ffi);
  RUN_TEST(test_call_ffi_cb_vu);
  RUN_TEST(test_call_ffi_cb_viu);
  RUN_TEST(test_call_ffi_cb_vui);
  RUN_TEST(test_call_ffi_cb_vui_unused_userdata);
  RUN_TEST(test_call_ffi_cb_iiui);
  RUN_TEST(test_call_ffi_cb_err);

  RUN_TEST(test_varint);
  RUN_TEST(test_dataview);

  return NULL;
}

int main(void) {
  double seconds = 0.0;
  const char *msg = run_all_tests("", &seconds);
  printf("%s, run %d in %.3fs\n", msg ? "FAIL" : "PASS", num_tests, seconds);
  return msg == NULL ? EXIT_SUCCESS : EXIT_FAILURE;
}
