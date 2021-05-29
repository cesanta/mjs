#include <math.h>
#include <stdlib.h>
#include "mjs.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* clang-format off */

#define STRINGIFY(x) #x
#define MJS_ENABLE_DEBUG 1
#include "common/cs_dirent.h"
#include "common/test_main.h"
#include "common/test_util.h"
#include "mjs.c"

#define ASSERT_EXEC_OK(_exec_) ASSERT_EXEC_RES(_exec_, MJS_OK)

#define ASSERT_EXEC_RES(_exec_, _res_)                                      \
  do {                                                                      \
    mjs_err_t err = _exec_;                                                 \
    if (err != MJS_OK && _res_ == MJS_OK) {                                 \
      mjs_print_error(mjs, stderr, "exec error", 1 /* print_stack_trace */);\
    }                                                                       \
    ASSERT_EQ(err, _res_);                                                  \
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

#define CHECK_TRUE(str)                       \
  do {                                        \
    ASSERT_EXEC_OK(mjs_exec(mjs, str, &res)); \
    ASSERT_EQ64(res, mjs_mk_boolean(mjs, 1));   \
  } while (0)


/*
 * Like `RUN_TEST()`, but the test function should have a prototype
 * test_func_t.
 */
#define RUN_TEST_MJS(func) do {            \
  s_test_func = (func);                    \
  RUN_TEST_WNAME(s_run_test_mjs, #func);   \
} while(0)

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

/*
 * mjs test function prototype, it takes mjs instance as a parameter.
 * This way, we can run the same test twice, and check if the second pass did
 * not occupy any extra GC cell. If it did, it's a memory leak.
 */
typedef const char *(test_func_t)(struct mjs *mjs);

/*
 * Test function suitable for the common RUN_TEST() macro; it takes a
 * "parameter" as a static test function pointer s_test_func.
 *
 * The purpose of this indirection is that mjs test function should take
 * an mjs instance as a parameter: See comment for `test_func_t`.
 */
static test_func_t *s_test_func;
static const char *s_run_test_mjs(void) {
  uint32_t objects_alive, props_alive, ffi_sigs_alive; 
  struct mjs *mjs = mjs_create();
  const char *ret = s_test_func(mjs);
  mjs_gc(mjs, 1);
  objects_alive = mjs->object_arena.alive;
  props_alive = mjs->property_arena.alive;
  ffi_sigs_alive = mjs->ffi_sig_arena.alive;

  /*
   * If test succeeds, run it again and check if memory usage is still the same
   */
  if (ret == NULL) {
    ret = s_test_func(mjs);
    mjs_gc(mjs, 1);

    ASSERT_EQ(objects_alive, mjs->object_arena.alive);
    ASSERT_EQ(props_alive, mjs->property_arena.alive);
    ASSERT_EQ(ffi_sigs_alive, mjs->ffi_sig_arena.alive);
  }

  ASSERT_EQ(mjs->owned_values.len, 0);
  cleanup_mjs(&mjs);

  return ret;
}

const char *test_arithmetic(struct mjs *mjs) {
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
  ASSERT_EXEC_OK(mjs_exec(mjs, "200 % 0.999", &res));
  ASSERT(isnan(mjs_get_double(mjs, res)));
  CHECK_NUMERIC("5 % 2", 1);
  CHECK_NUMERIC("5 % -2", 1);
  CHECK_NUMERIC("-5 % 2", -1);
  CHECK_NUMERIC("-5 % -2", -1);
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

  ASSERT_EXEC_OK(mjs_exec(mjs, "NaN", &res));
  ASSERT_EQ(!!isnan(mjs_get_double(mjs, res)), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "NaN === NaN", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "NaN !== NaN", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "NaN === 0", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "NaN === 1", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "NaN === null", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "NaN === undefined", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "NaN === ''", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "NaN === {}", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "NaN === []", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "isNaN(NaN)", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "isNaN(NaN * 10)", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "isNaN(0)", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "isNaN('')", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  mjs_disown(mjs, &res);

  return NULL;
}

const char *test_block(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  CHECK_NUMERIC("if (1) 2", 2);
  ASSERT_EXEC_OK(mjs_exec(mjs, "if (0) 2;", &res));
  ASSERT(res == MJS_UNDEFINED);
  CHECK_NUMERIC("{let a = 42; }", 42);
  CHECK_NUMERIC("let a = 1, b = 2; { let a = 3; b += a; } b;", 5);
  ASSERT_EXEC_OK(mjs_exec(mjs, "{}", &res));
  ASSERT(res == MJS_UNDEFINED);

  mjs_disown(mjs, &res);
  return NULL;
}

const char *test_function(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  CHECK_NUMERIC("let f = function(){ 1; }; 1;", 1);
  CHECK_NUMERIC("let f = function(a){ 1; }; 1;", 1);
  CHECK_NUMERIC("let f = function(a,b){ 1; }; 1;", 1);
  CHECK_NUMERIC("let f = function(a,b){ return a; }; f(1,2);", 1);
  CHECK_NUMERIC("let f = function(a,b){ return b; }; f(1,2);", 2);
  CHECK_NUMERIC("let f = function(a,b){ return b; }; f(1,2,3);", 2);
  ASSERT_EXEC_OK(mjs_exec(mjs, "let f = function(a,b){return b;};f(1);", &res));
  ASSERT(res == MJS_UNDEFINED);
  CHECK_NUMERIC("function foo(a,b){ return b; }; foo(1,2,3);", 2);
  CHECK_NUMERIC("let bar = function foo(a,b){ return b; }; foo(1,2,3) + bar(4,5);", 7);

  CHECK_NUMERIC("let f = function(a){return a.b;}; f({b: {c: 7}}).c;", 7);
  CHECK_NUMERIC("function f(){}; f ? 1 : 2", 1);
  CHECK_NUMERIC("function f(x){return x ? {x:x} : 0}; f(f).x(0);", 0);

  /* Test return without a value */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          function foo() {
            return;
          }
          foo();
        ), &res));

  /* Invalid expression after "return" should result in a syntax error */
  ASSERT_EQ(mjs_exec(mjs, "return function f(x)", &res), MJS_SYNTAX_ERROR);

  mjs_disown(mjs, &res);
  return NULL;
}

const char *test_cfunction(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set(mjs, mjs_get_global(mjs), "test_this_plus_arg", ~0, mjs_mk_foreign(mjs, test_this_plus_arg));

  CHECK_NUMERIC("let o = {foo: 100, f:test_this_plus_arg}; o.f(20, 5);", 100+20-5);

  mjs_disown(mjs, &res);
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
      const char *jsext = ".js";
      mjs_val_t res = MJS_UNDEFINED;
      int basename_len = (int)strlen(dp->d_name) - strlen(jsext);

      if (strncmp(dp->d_name, prefix, strlen(prefix)) != 0) continue;
      if (strncmp(dp->d_name + basename_len, jsext, strlen(jsext)) != 0) continue;
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

const char *test_if(struct mjs *mjs) {
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
  return NULL;
}

const char *test_comparison(struct mjs *mjs) {
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
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "0 !== 0", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 0));

  ASSERT_EXEC_OK(mjs_exec(mjs, "null === null", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "undefined === undefined", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "true === true", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "false === false", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' === 'foo'", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' === 'fo0'", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 0));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' === undefined", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 0));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' === null", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 0));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' !== undefined", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo' !== null", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 1));

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o1={}, o2={}; o1===o2", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 0));

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o1={}, o2=o1; o1===o2", &res));
  ASSERT_EQ64(res, mjs_mk_boolean(mjs, 1));

  mjs_disown(mjs, &res);
  return NULL;
}

const char *test_logic(struct mjs *mjs) {
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

  /* Test short-circuit for && */
  ASSERT_EXEC_OK(mjs_exec(mjs, "let a=1, b=2, c=0; if (a > 1 && (b = b+1) > 2) { c=b; } b", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 2);

  /* Test short-circuit for || */
  ASSERT_EXEC_OK(mjs_exec(mjs, "let a=1, b=2, c=0; if (a === 1 || (b = b+1) > 2) { c=b; } b", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 2);

  mjs_disown(mjs, &res);

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

  ffi_call((ffi_fn_t *) testfunc1, 4, &res, args);

  ASSERT_EQ((int64_t) res.v.i, 10);

  return NULL;
}

int testfunc2(int a, double b) {
  // printf("called testfunc2 with a=%d, b=%lg\n", a, b);
  return (int) (a + b);
}

static const char *test_func2() {
  struct ffi_arg res;
  struct ffi_arg args[2];
  res.ctype = FFI_CTYPE_WORD;
  ffi_set_word(&args[0], 1);
  ffi_set_double(&args[1], 2);

  ffi_call((ffi_fn_t *) testfunc2, 2, &res, args);

  ASSERT_EQ((int64_t) res.v.i, 3);

  return NULL;
}

int testfunc3(double a, double b) {
  // printf("called testfunc3 with a=%lg, b=%lg\n", a, b);
  return (int) (a + b);
}

static const char *test_func3() {
  struct ffi_arg res;
  struct ffi_arg args[2];
  res.ctype = FFI_CTYPE_WORD;
  ffi_set_double(&args[0], 1);
  ffi_set_double(&args[1], 2);

  ffi_call((ffi_fn_t *) testfunc3, 2, &res, args);

  ASSERT_EQ((int64_t) res.v.i, 3);

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

  ffi_call((ffi_fn_t *) testfunc4, 4, &res, args);

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

  ffi_call((ffi_fn_t *) testfunc5, 2, &res, args);

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

  ffi_call((ffi_fn_t *) testfunc6, 2, &res, args);

  ASSERT_EQ(res.v.d, 3);

  return NULL;
}

const void *ffi_get_null(void) {
  return NULL;
}

void ffi_set_byte(void *ptr, int val) {
  *((char *)ptr) = val;
}

int ffi_test_i2i(int a0, int a1) {
  return a0 - a1;
}

/* 3 arg, one double {{{ */
int ffi_test_iiid(int a0, int a1, double d2) {
  return (int) ((d2 * a0 - a1) * 1000);
}

bool ffi_test_biid(int a0, int a1, double d2) {
  (void) a0;
  (void) a1;
  return d2 > 10.0;
}

double ffi_test_diid(int a0, int a1, double d2) {
  return d2 * a0 - a1;
}
/* }}} */

/* 3 arg, two doubles {{{ */
int ffi_test_iidd(int a0, double a1, double d2) {
  return (int) ((d2 * a0 - a1) * 1000);
}

bool ffi_test_bidd(int a0, double a1, double d2) {
  (void) a0;
  (void) a1;
  return d2 > 10.0;
}

double ffi_test_didd(int a0, double a1, double d2) {
  return d2 * a0 - a1;
}
/* }}} */

/* 3 arg, one float {{{ */
int ffi_test_iiif(int a0, int a1, float f2) {
  return (int) ((f2 * a0 - a1) * 1000);
}

bool ffi_test_biif(int a0, int a1, float f2) {
  (void) a0;
  (void) a1;
  return f2 > 10.0;
}

float ffi_test_fiif(int a0, int a1, float f2) {
  return f2 * a0 - a1;
}
/* }}} */

/* 3 arg, two floats {{{ */
int ffi_test_iiff(int a0, float a1, float f2) {
  return (int) ((f2 * a0 - a1) * 1000);
}

bool ffi_test_biff(int a0, float a1, float f2) {
  (void) a0;
  (void) a1;
  return f2 > 10.0;
}

float ffi_test_fiff(int a0, float a1, float f2) {
  return f2 * a0 - a1;
}
/* }}} */

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
  return (int) (1234 + a + b * 100);
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

static void ffi_test_inbuf(char *buf, int len) {
  char pattern[] = { 'a', 'b', 0, 'c', 'd', 1 };
  int i;
  for (i = 0; i < len; i++) {
    buf[i] = pattern[i % sizeof(pattern)];
  }
}

/* Old Visual Studio MSVC98 */
#if _MSC_VER && _MSC_VER < 1700
double round(double v) {
  double intpart;
  double fractpart = modf(v, &intpart);
  return intpart + (fractpart < 0.5 ? 0 : 1);
}

double fmax(double a, double b) {
  return a > b ? a : b;
}

double fmin(double a, double b) {
  return a < b ? a : b;
}
#endif

static const void *get_my_struct(void);
static const struct mjs_c_struct_member *get_my_struct_descr(void);

void *stub_dlsym(void *handle, const char *name) {
  if (strcmp(name, "ffi_get_null") == 0) return (void *) ffi_get_null;
  if (strcmp(name, "ffi_set_byte") == 0) return (void *) ffi_set_byte;
  if (strcmp(name, "ffi_test_i2i") == 0) return (void *) ffi_test_i2i;
  if (strcmp(name, "ffi_test_iiid") == 0) return (void *) ffi_test_iiid;
  if (strcmp(name, "ffi_test_biid") == 0) return (void *) ffi_test_biid;
  if (strcmp(name, "ffi_test_diid") == 0) return (void *) ffi_test_diid;
  if (strcmp(name, "ffi_test_iidd") == 0) return (void *) ffi_test_iidd;
  if (strcmp(name, "ffi_test_bidd") == 0) return (void *) ffi_test_bidd;
  if (strcmp(name, "ffi_test_didd") == 0) return (void *) ffi_test_didd;
  if (strcmp(name, "ffi_test_iiif") == 0) return (void *) ffi_test_iiif;
  if (strcmp(name, "ffi_test_biif") == 0) return (void *) ffi_test_biif;
  if (strcmp(name, "ffi_test_fiif") == 0) return (void *) ffi_test_fiif;
  if (strcmp(name, "ffi_test_iiff") == 0) return (void *) ffi_test_iiff;
  if (strcmp(name, "ffi_test_biff") == 0) return (void *) ffi_test_biff;
  if (strcmp(name, "ffi_test_fiff") == 0) return (void *) ffi_test_fiff;
  if (strcmp(name, "ffi_test_iib") == 0) return (void *) ffi_test_iib;
  if (strcmp(name, "ffi_test_bi") == 0) return (void *) ffi_test_bi;
  if (strcmp(name, "ffi_test_i5i") == 0) return (void *) ffi_test_i5i;
  if (strcmp(name, "ffi_test_i6i") == 0) return (void *) ffi_test_i6i;
  if (strcmp(name, "ffi_test_d2d") == 0) return (void *) ffi_test_d2d;
  if (strcmp(name, "ffi_test_iid") == 0) return (void *) ffi_test_iid;
  if (strcmp(name, "ffi_test_s1s") == 0) return (void *) ffi_test_s1s;
  if (strcmp(name, "ffi_dummy") == 0) return (void *) ffi_dummy;
  if (strcmp(name, "ffi_test_cb_vu") == 0) return (void *) ffi_test_cb_vu;
  if (strcmp(name, "ffi_test_cb_viu") == 0) return (void *) ffi_test_cb_viu;
  if (strcmp(name, "ffi_test_cb_vui") == 0) return (void *) ffi_test_cb_vui;
  if (strcmp(name, "ffi_test_cb_iiui") == 0) return (void *) ffi_test_cb_iiui;
  if (strcmp(name, "ffi_test_cb_iiui2") == 0) return (void *) ffi_test_cb_iiui2;
  if (strcmp(name, "ffi_test_cb_viiiiiu") == 0) return (void *) ffi_test_cb_viiiiiu;
  if (strcmp(name, "ffi_test_inbuf") == 0) return (void *) ffi_test_inbuf;
  if (strcmp(name, "mg_vcasecmp") == 0) return (void *) mg_vcasecmp;
  if (strcmp(name, "malloc") == 0) return (void *) malloc;
  if (strcmp(name, "calloc") == 0) return (void *) calloc;
  if (strcmp(name, "free") == 0) return (void *) free;
  if (strcmp(name, "mjs_mem_to_ptr") == 0) return (void *) mjs_mem_to_ptr;
  if (strcmp(name, "mjs_mem_get_ptr") == 0) return (void *) mjs_mem_get_ptr;
  if (strcmp(name, "mjs_mem_get_uint") == 0) return (void *) mjs_mem_get_uint;
  if (strcmp(name, "mjs_mem_set_uint") == 0) return (void *) mjs_mem_set_uint;
  if (strcmp(name, "mjs_mem_get_int") == 0) return (void *) mjs_mem_get_int;
  if (strcmp(name, "ceil") == 0) return (void *) ceil;
  if (strcmp(name, "floor") == 0) return (void *) floor;
  if (strcmp(name, "rand") == 0) return (void *) rand;
  if (strcmp(name, "round") == 0) return (void *) round;
  if (strcmp(name, "fmax") == 0) return (void *) fmax;
  if (strcmp(name, "fmin") == 0) return (void *) fmin;
  if (strcmp(name, "fabs") == 0) return (void *) fabs;
  if (strcmp(name, "sqrt") == 0) return (void *) sqrt;
  if (strcmp(name, "exp") == 0) return (void *) exp;
  if (strcmp(name, "log") == 0) return (void *) log;
  if (strcmp(name, "pow") == 0) return (void *) pow;
  if (strcmp(name, "sin") == 0) return (void *) sin;
  if (strcmp(name, "cos") == 0) return (void *) cos;
  if (strcmp(name, "get_my_struct") == 0) return (void *) get_my_struct;
  if (strcmp(name, "get_my_struct_descr") == 0) {
    return (void *) get_my_struct_descr;
  }
  return NULL;
  (void) handle;
}

const char *test_parse_ffi_signature(struct mjs *mjs) {
  mjs_ffi_sig_t sig;

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  mjs_set_errorf(mjs, MJS_OK, NULL);
  ASSERT_EXEC_OK(
      mjs_parse_ffi_signature(mjs, "void ffi_dummy(int, int)", ~0, &sig, FFI_SIG_FUNC));
  ASSERT_EQ(sig.val_types[0], MJS_FFI_CTYPE_NONE);
  ASSERT_EQ(sig.val_types[1], MJS_FFI_CTYPE_INT);
  ASSERT_EQ(sig.val_types[2], MJS_FFI_CTYPE_INT);
  ASSERT_EQ(sig.val_types[3], MJS_FFI_CTYPE_NONE);
  ASSERT_PTREQ(sig.cb_sig, NULL);
  ASSERT_PTREQ(sig.fn, (ffi_fn_t *)ffi_dummy);
  ASSERT_EQ(sig.is_valid, 1);
  ASSERT_EQ(sig.args_cnt, 2);
  mjs_ffi_sig_free(&sig);

  /* check the same signature differently formatted */
  {
    mjs_ffi_sig_t sig2;
    mjs_set_errorf(mjs, MJS_OK, NULL);
    ASSERT_EXEC_OK(
        mjs_parse_ffi_signature(mjs, " \tvoid \t ffi_dummy (\tint, int)", ~0, &sig2, FFI_SIG_FUNC));
    ASSERT_EQ(memcmp(&sig, &sig2, sizeof(sig)), 0);
    mjs_ffi_sig_free(&sig);
  }

  /* check a few wrong signatures */
  mjs_set_errorf(mjs, MJS_OK, NULL);
  ASSERT_EQ(
      mjs_parse_ffi_signature(mjs, "sdf ffi_dummy(int, int)", ~0, &sig, FFI_SIG_FUNC), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"sdf ffi_dummy(int, int)\": failed to parse val type \"sdf\"";
    ASSERT_STREQ(mjs->error_msg, rs);
  }
  mjs_ffi_sig_free(&sig);

  mjs_set_errorf(mjs, MJS_OK, NULL);
  ASSERT_EQ(
      mjs_parse_ffi_signature(mjs, "sdf ffi_dummy (int, int)", ~0, &sig, FFI_SIG_FUNC), MJS_TYPE_ERROR);
  mjs_ffi_sig_free(&sig);

  mjs_set_errorf(mjs, MJS_OK, NULL);
  ASSERT_EQ(
      mjs_parse_ffi_signature(mjs, "void ffi_dummy(sdf, int)", ~0, &sig, FFI_SIG_FUNC), MJS_TYPE_ERROR);
  mjs_ffi_sig_free(&sig);

  /* check signature with the callback */
  mjs_set_errorf(mjs, MJS_OK, NULL);
  ASSERT_EXEC_OK(
      mjs_parse_ffi_signature(mjs, "int ffi_dummy(int, void(*)(int, userdata), userdata)", ~0, &sig, FFI_SIG_FUNC));
  ASSERT_EQ(sig.val_types[0], MJS_FFI_CTYPE_INT);
  ASSERT_EQ(sig.val_types[1], MJS_FFI_CTYPE_INT);
  ASSERT_EQ(sig.val_types[2], MJS_FFI_CTYPE_CALLBACK);
  ASSERT_EQ(sig.val_types[3], MJS_FFI_CTYPE_USERDATA);
  ASSERT_EQ(sig.val_types[4], MJS_FFI_CTYPE_NONE);
  ASSERT_PTRNE(sig.cb_sig, NULL);
  ASSERT_PTREQ(sig.fn, (ffi_fn_t *)ffi_dummy);
  ASSERT_EQ(sig.is_valid, 1);
  ASSERT_EQ(sig.args_cnt, 3);

  ASSERT_EQ(sig.cb_sig->val_types[0], MJS_FFI_CTYPE_NONE);
  ASSERT_EQ(sig.cb_sig->val_types[1], MJS_FFI_CTYPE_INT);
  ASSERT_EQ(sig.cb_sig->val_types[2], MJS_FFI_CTYPE_USERDATA);
  ASSERT_EQ(sig.cb_sig->val_types[3], MJS_FFI_CTYPE_NONE);
  ASSERT_EQ(sig.cb_sig->is_valid, 1);
  ASSERT_PTREQ(sig.cb_sig->fn, (ffi_fn_t *)ffi_cb_impl_wwpwwww);
  mjs_ffi_sig_free(&sig);

  /* check signature with the callback */
  mjs_set_errorf(mjs, MJS_OK, NULL);
  ASSERT_EXEC_OK(
      mjs_parse_ffi_signature(mjs, "int ffi_dummy(void(*)(userdata), userdata)", ~0, &sig, FFI_SIG_FUNC));
  ASSERT_EQ(sig.val_types[0], MJS_FFI_CTYPE_INT);
  ASSERT_EQ(sig.val_types[1], MJS_FFI_CTYPE_CALLBACK);
  ASSERT_EQ(sig.val_types[2], MJS_FFI_CTYPE_USERDATA);
  ASSERT_EQ(sig.val_types[3], MJS_FFI_CTYPE_NONE);
  ASSERT_PTRNE(sig.cb_sig, NULL);
  ASSERT_PTREQ(sig.fn, (ffi_fn_t *)ffi_dummy);
  ASSERT_EQ(sig.is_valid, 1);
  ASSERT_EQ(sig.args_cnt, 2);

  ASSERT_EQ(sig.cb_sig->val_types[0], MJS_FFI_CTYPE_NONE);
  ASSERT_EQ(sig.cb_sig->val_types[1], MJS_FFI_CTYPE_USERDATA);
  ASSERT_EQ(sig.cb_sig->val_types[2], MJS_FFI_CTYPE_NONE);
  ASSERT_EQ(sig.cb_sig->is_valid, 1);
  ASSERT_PTREQ(sig.cb_sig->fn, (ffi_fn_t *)ffi_cb_impl_wpwwwww);
  mjs_ffi_sig_free(&sig);

  /* wrong signature: two callbacks */
  mjs_set_errorf(mjs, MJS_OK, NULL);
  ASSERT_EQ(
      mjs_parse_ffi_signature(mjs, "int ffi_dummy(int, void(*)(int, userdata), void(*)(), userdata)", ~0, &sig, FFI_SIG_FUNC), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"int ffi_dummy(int, void(*)(int, userdata), void(*)(), userdata)\": only one callback is allowed";
    ASSERT_STREQ(mjs->error_msg, rs);
  }
  mjs_ffi_sig_free(&sig);

  /* wrong signature: callback without userdata */
  mjs_set_errorf(mjs, MJS_OK, NULL);
  ASSERT_EQ(
      mjs_parse_ffi_signature(mjs, "int ffi_dummy(void(*)(), userdata)", ~0, &sig, FFI_SIG_FUNC), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"int ffi_dummy(void(*)(), userdata)\": bad ffi signature: \"void(*)()\": no userdata arg";
    ASSERT_STREQ(mjs->error_msg, rs);
  }
  mjs_ffi_sig_free(&sig);

  /* wrong signature: callback is present, userdata is not */
  mjs_set_errorf(mjs, MJS_OK, NULL);
  ASSERT_EQ(
      mjs_parse_ffi_signature(mjs, "int ffi_dummy(int, void(*)(userdata))", ~0, &sig, FFI_SIG_FUNC), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"int ffi_dummy(int, void(*)(userdata))\": callback and userdata should be either both present or both absent";
    ASSERT_STREQ(mjs->error_msg, rs);
  }
  mjs_ffi_sig_free(&sig);

  /* wrong signature: callback is not present, userdata is */
  mjs_set_errorf(mjs, MJS_OK, NULL);
  ASSERT_EQ(
      mjs_parse_ffi_signature(mjs, "int ffi_dummy(int, userdata)", ~0, &sig, FFI_SIG_FUNC), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"int ffi_dummy(int, userdata)\": callback and userdata should be either both present or both absent";
    ASSERT_STREQ(mjs->error_msg, rs);
  }
  mjs_ffi_sig_free(&sig);

  /* wrong signature: callback taking another callback */
  mjs_set_errorf(mjs, MJS_OK, NULL);
  ASSERT_EQ(
      mjs_parse_ffi_signature(mjs, "int ffi_dummy(void(*)(void(*)(userdata), userdata), userdata)", ~0, &sig, FFI_SIG_FUNC), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"int ffi_dummy(void(*)(void(*)(userdata), userdata), userdata)\": bad ffi signature: \"void(*)(void(*)(userdata), userdata)\": callback can't take another callback";
    ASSERT_STREQ(mjs->error_msg, rs);
  }
  mjs_ffi_sig_free(&sig);

  /* wrong signature: callback with double arg */
  mjs_set_errorf(mjs, MJS_OK, NULL);
  ASSERT_EQ(
      mjs_parse_ffi_signature(mjs, "int ffi_dummy(int, void(*)(double, double, userdata), userdata)", ~0, &sig, FFI_SIG_FUNC), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"int ffi_dummy(int, void(*)(double, double, userdata), userdata)\": bad ffi signature: \"void(*)(double, double, userdata)\": the callback signature is valid, but there's no existing callback implementation for it";
    ASSERT_STREQ(mjs->error_msg, rs);
  }
  mjs_ffi_sig_free(&sig);

  return NULL;
}

const char *test_call_ffi(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);
  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_i2i = ffi('int ffi_test_i2i(int, int)')",
        &res));

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
  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_iib = ffi('int ffi_test_iib(int, bool)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_iib(40, true)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 40-10);

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_iib(40, false)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 40-20);

  /* function which returns bool */
  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_bi = ffi('bool ffi_test_bi(int)')",
        &res));
  ASSERT_EQ(mjs_exec(mjs, "ffi_test_bi(50)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), false);

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_bi(51)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), true);

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_i5i = ffi('int ffi_test_i5i(int, int, int, int, int)')",
        &res));
  ASSERT_EQ(mjs_exec(mjs, "ffi_test_i5i(114, 14, 7, 1, 4)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), (114 - 14) / ((7 - 1) * 4));

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_i6i = ffi('int ffi_test_i6i(int, int, int, int, int, int)')",
        &res));
  ASSERT_EQ(mjs_exec(mjs, "ffi_test_i6i(114, 14, 7, 1, 4, 11)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_double(mjs, res), (114 - 14) / ((7 - 1) * 4) + 11 * 2);

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_s1s = ffi('char *ffi_test_s1s(char *)')",
        &res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "ffi_test_s1s('foo')", &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "foo");

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_s1s('\\x01')", &res), MJS_OK);
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "\x01");

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_s1s('\\x01\\x00')", &res), MJS_OK);
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "\x01");

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_s1s('\\x00')", &res), MJS_OK);
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "");

  /* null as an argument is allowed and becomes NULL;
   * return value of NULL becomes null. */
  ASSERT_EQ(mjs_exec(mjs, "ffi_test_s1s(null)", &res), MJS_OK);
  ASSERT_TRUE(mjs_is_null(res));

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "ffi('double ffi_test_d2d(double,double)')(3.71, 1.28)",
               &res));
  ASSERT_LT(fabs(mjs_get_double(mjs, res) - 17.33), 0.0001);

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "ffi('int ffi_test_iid(int,double)')(300, 1.28)",
        &res));
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

  /* calling strings is not supported anymore */
  mjs_set(mjs, mjs_get_global(mjs), "ffi_test_s1s", ~0,
      mjs_mk_string(mjs, "char *ffi_test_s1s(char *)", ~0, 1));
  ASSERT_EQ(mjs_exec(mjs, "ffi_test_s1s('\\x01')", &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "failed to call FFIed function: non-ffi-callable value");

  /* Test struct mg_str * FFI, long and short strings */
  ASSERT_EQ(mjs_exec(mjs, "let mg_vcasecmp = ffi('int mg_vcasecmp(struct mg_str *, char *)');", &res), MJS_OK);
  ASSERT_EQ(mjs_exec(mjs, "mg_vcasecmp('foobar', 'FooBar') === 0;", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);
  ASSERT_EQ(mjs_exec(mjs, "mg_vcasecmp('foobar', 'Foo') !== 0;", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);
  ASSERT_EQ(mjs_exec(mjs, "mg_vcasecmp('a', 'A') === 0;", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  /* Test the ability to pass char buffers to C */
  {
    size_t len;
    const char *p, *result = "\x61\x62\x00\x63\x64\x01\x61\x62\x00\x63";

    /* Try big string, big read */
    ASSERT_EQ(mjs_exec(mjs, "let buf = 'o1o2o3o4o5'; ", &res), MJS_OK);
    ASSERT_EQ(mjs_exec(mjs, "let f = ffi('void ffi_test_inbuf(char *, int)');", &res), MJS_OK);
    ASSERT_EQ(mjs_exec(mjs, "f(buf, buf.length);", &res), MJS_OK);
    ASSERT_EQ(mjs_exec(mjs, "buf", &res), MJS_OK);
    p = mjs_get_string(mjs, &res, &len);
    ASSERT(p != NULL);
    ASSERT_EQ(len, 10);
    ASSERT_EQ(memcmp(p, result, len), 0);

    /* Try big string, small read */
    ASSERT_EQ(mjs_exec(mjs, "buf = 'o1o2o3o4o5';", &res), MJS_OK);
    ASSERT_EQ(mjs_exec(mjs, "f(buf, 2);", &res), MJS_OK);
    ASSERT_EQ(mjs_exec(mjs, "buf", &res), MJS_OK);
    p = mjs_get_string(mjs, &res, &len);
    ASSERT(p != NULL);
    ASSERT_EQ(len, 10);
    ASSERT_STREQ(p, "abo2o3o4o5");

    /* Try small string, small read */
    ASSERT_EQ(mjs_exec(mjs, "buf = 'o1';", &res), MJS_OK);
    ASSERT_EQ(mjs_exec(mjs, "f(buf, buf.length);", &res), MJS_OK);
    ASSERT_EQ(mjs_exec(mjs, "buf", &res), MJS_OK);
    p = mjs_get_string(mjs, &res, &len);
    ASSERT(p != NULL);
    ASSERT_EQ(len, 2);
    /* TODO(lsm): enable */
    /* ASSERT_STREQ(p, "ab"); */
  }

  /* 3 arg, one double {{{ */
  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_iiid = ffi('int ffi_test_iiid(int, int, double)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_iiid(3, 2, 13.4)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 38200);

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_diid = ffi('double ffi_test_diid(int, int, double)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_diid(3, 2, 13.4)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_double(mjs, res), 38.2);

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_biid = ffi('bool ffi_test_biid(int, int, double)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_biid(0, 0, 10)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_biid(0, 0, 10.1)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);
  /* }}} */

  /* 3 arg, two doubles {{{ */
  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_iidd = ffi('int ffi_test_iidd(int, double, double)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_iidd(3, 2.1, 13.4)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 38100);

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_didd = ffi('double ffi_test_didd(int, double, double)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_didd(3, 2.1, 13.4)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_double(mjs, res), 38.1);

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_bidd = ffi('bool ffi_test_bidd(int, double, double)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_bidd(0, 0, 10)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_bidd(0, 0, 10.1)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);
  /* }}} */

  /* 3 arg, one float {{{ */
  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_iiif = ffi('int ffi_test_iiif(int, int, float)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_iiif(3, 2, 13.5)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 38500);

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_fiif = ffi('float ffi_test_fiif(int, int, float)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_fiif(3, 2, 13.5)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_double(mjs, res), 38.5);

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_biif = ffi('bool ffi_test_biif(int, int, float)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_biif(0, 0, 10)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_biif(0, 0, 10.1)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);
  /* }}} */

  /* 3 arg, two floats {{{ */
  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_iiff = ffi('int ffi_test_iiff(int, float, float)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_iiff(3, 2.0, 13.5)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_int(mjs, res), 38500);

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_fiff = ffi('float ffi_test_fiff(int, float, float)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_fiff(3, 2.0, 13.5)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_double(mjs, res), 38.5);

  ASSERT_EXEC_OK(
      mjs_exec(mjs, "let ffi_test_biff = ffi('bool ffi_test_biff(int, float, float)')",
        &res));

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_biff(0, 0, 10)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EQ(mjs_exec(mjs, "ffi_test_biff(0, 0, 10.1)", &res), MJS_OK);
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);
  /* }}} */

  mjs_disown(mjs, &res);

  return NULL;
}

const char *test_call_ffi_cb_vu(struct mjs *mjs) {
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
  ASSERT_EQ64(res, mjs_mk_number(mjs, 0));

  /* Free first sig */
  ASSERT_EXEC_OK(mjs_exec(mjs, "ffi_cb_free(cb, 1);", &res));
  ASSERT_EQ64(res, mjs_mk_number(mjs, 1));
  ASSERT_EQ((uintptr_t)mjs->ffi_cb_args->next, (uintptr_t)NULL);
  ASSERT_EQ(mjs_get_int(mjs, mjs->ffi_cb_args->userdata), 2);

  /* Try to free it again */
  ASSERT_EXEC_OK(mjs_exec(mjs, "ffi_cb_free(cb, 1);", &res));
  ASSERT_EQ64(res, mjs_mk_number(mjs, 0));

  /* Free second sig */
  ASSERT_EXEC_OK(mjs_exec(mjs, "ffi_cb_free(cb, 2);", &res));
  ASSERT_EQ64(res, mjs_mk_number(mjs, 1));
  ASSERT_EQ((uintptr_t)mjs->ffi_cb_args, (uintptr_t)NULL);

  /* Try to free it again */
  ASSERT_EXEC_OK(mjs_exec(mjs, "ffi_cb_free(cb, 2);", &res));
  ASSERT_EQ64(res, mjs_mk_number(mjs, 0));

  mjs_disown(mjs, &res);

  return NULL;
}

const char *test_call_ffi_cb_viu(struct mjs *mjs) {
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

  return NULL;
}


const char *test_call_ffi_cb_vui(struct mjs *mjs) {
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

  return NULL;
}

const char *test_call_ffi_cb_vui_unused_userdata(struct mjs *mjs) {
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

  return NULL;
}

const char *test_call_ffi_cb_iiui(struct mjs *mjs) {
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

  return NULL;
}

const char *test_call_ffi_cb_err(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  /* test wrong signatures */

  ASSERT_EQ(mjs_exec(mjs,
        STRINGIFY(
          let ffi_dummy = ffi(
            "void ffi_dummy(int, int, foo(*)(userdata), userdata)"
            );
          ), &res), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"void ffi_dummy(int, int, foo(*)(userdata), userdata)\": bad ffi signature: \"foo(*)(userdata)\": failed to parse val type \"foo\"";
    ASSERT_STREQ(mjs->error_msg, rs);
  }

  /* --- */

  ASSERT_EQ(mjs_exec(mjs,
        STRINGIFY(
          let ffi_dummy = ffi(
            "void ffi_dummy(int, int, void(*)(userdata, foo), userdata)"
            );
          ), &res), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"void ffi_dummy(int, int, void(*)(userdata, foo), userdata)\": bad ffi signature: \"void(*)(userdata, foo)\": failed to parse val type \"foo\"";
    ASSERT_STREQ(mjs->error_msg, rs);
  }

  /* --- */

  ASSERT_EQ(mjs_exec(mjs,
        STRINGIFY(
          let ffi_dummy = ffi(
            "void ffi_dummy(int, int, void(*)(), userdata)"
            );
          ), &res), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"void ffi_dummy(int, int, void(*)(), userdata)\": bad ffi signature: \"void(*)()\": no userdata arg";
    ASSERT_STREQ(mjs->error_msg, rs);
  }

  /* --- */

  ASSERT_EQ(mjs_exec(mjs,
        STRINGIFY(
          let ffi_dummy = ffi(
            "void ffi_dummy(int, int, void(*)(userdata))"
            );
          ), &res), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"void ffi_dummy(int, int, void(*)(userdata))\": callback and userdata should be either both present or both absent";
    ASSERT_STREQ(mjs->error_msg, rs);
  }

  /* --- */

  ASSERT_EQ(mjs_exec(mjs,
        STRINGIFY(
          let ffi_dummy = ffi(
            "void ffi_dummy(userdata, int, void(*)(userdata), userdata)"
            );
          ), &res), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"void ffi_dummy(userdata, int, void(*)(userdata), userdata)\": more than one userdata arg: #0 and #3";
    ASSERT_STREQ(mjs->error_msg, rs);
  }

  /* --- */

  ASSERT_EQ(mjs_exec(mjs,
        STRINGIFY(
          let ffi_dummy = ffi(
            "void ffi_dummy(int, int, void(*)(userdata, userdata), userdata)"
            );
          ), &res), MJS_TYPE_ERROR);
  {
    const char *rs = "bad ffi signature: \"void ffi_dummy(int, int, void(*)(userdata, userdata), userdata)\": bad ffi signature: \"void(*)(userdata, userdata)\": more than one userdata arg: #0 and #1";
    ASSERT_STREQ(mjs->error_msg, rs);
  }

  mjs_disown(mjs, &res);

  return NULL;
}

const char *test_errors(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EQ(mjs_exec(mjs, "x", &res), MJS_REFERENCE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "[x] is not defined");
  ASSERT_EQ(mjs_exec(mjs, "let o = {}; o.a", &res), MJS_OK);
  ASSERT(res == MJS_UNDEFINED);
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

  ASSERT_EQ(mjs_exec(mjs, "continue;", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "misplaced 'continue'");

  ASSERT_EQ(mjs_exec(mjs, "break;", &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "misplaced 'break'");

  ASSERT_EQ(mjs_exec(mjs, "load('foo/bar/bazzz')", &res), MJS_FILE_READ_ERROR);
  {
    const char *rs = "failed to exec file \"foo/bar/bazzz\": failed to read file \"foo/bar/bazzz\"";
    ASSERT_STREQ(mjs->error_msg, rs);
  }

  ASSERT_EQ(mjs_exec(mjs, "load('tests/module2.js')", &res), MJS_TYPE_ERROR);
  {
    const char *rs = "failed to exec file \"tests/module2.js\": bad ffi signature: \"int foo(int)\": dlsym('foo') failed";
    ASSERT_STREQ(mjs->error_msg, rs);
  }

  ASSERT_EQ(mjs_exec(mjs, "for (let i in 0) {}", &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "can't iterate over non-object value");

  mjs_disown(mjs, &res);
  return NULL;
}

const char *test_this(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs, "this", &res));
  ASSERT(res == MJS_UNDEFINED);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        "let f = function(){return this}; f()",
        &res));
  ASSERT(res == MJS_UNDEFINED);

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

  return NULL;
}

const char *test_while(struct mjs *mjs) {
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

  return NULL;
}

const char *test_for_loop(struct mjs *mjs) {
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

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          function foo() {
            for (i = 0; i < 10; i++) {
              if (i === 2) {
                return true;
              }
            }
          }
          foo();
        ), &res));
  ASSERT_EQ(mjs->loop_addresses.len, 0);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          for (i = 0; i < 10; i++) {}
          ), &res));

  mjs_disown(mjs, &res);

  return NULL;
}

const char *test_for_in_loop(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

#if 0
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let o = ({foo: 1, bar: 2}); let s="";
          for (let k in o) {
            s += "_" + k + ":" + JSON.stringify(o[k]);
          }
          s;
        ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_bar:2_foo:1");
#endif

#if 1
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
  //ASSERT_STREQ(mjs_get_cstring(mjs, &res), "_five:5_baz:3_bar:2");
#endif

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          function foo() {
            let o = ({foo: 1, bar: 2, baz: 3, four: 4, five: 5}); let s="";
            for (let k in o) {
              return true;
            }
          }
          foo();
        ), &res));
  ASSERT_EQ(mjs->loop_addresses.len, 0);


  mjs_disown(mjs, &res);

  return NULL;
}

const char *test_primitives(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs, "0x87654321", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), (int)0x87654321);

  mjs_disown(mjs, &res);

  return NULL;
}

const char *test_objects(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {}; o.b", &res));
  ASSERT(res == MJS_UNDEFINED);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100}; o.b", &res));
  ASSERT(res == MJS_UNDEFINED);

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
  ASSERT(res == MJS_UNDEFINED);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o = {a: 100}; o['b']", &res));
  ASSERT(res == MJS_UNDEFINED);

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

  return NULL;
}

const char *test_arrays(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let a = []; a.b", &res));
  ASSERT(res == MJS_UNDEFINED);

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

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([1, 2, 3]);
          let ret=a.push(10,20,30);
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "6___[1,2,3,10,20,30]");

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let a=([]);
          let ret=a.push();
          JSON.stringify(ret) + '___' + JSON.stringify(a)
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "0___[]");

  mjs_disown(mjs, &res);

  return NULL;
}

const char *test_json(struct mjs *mjs) {
  const char *json_val = "{\"null\":null,\"arr\":[1,2,{\"foo\":100}],\"bar\":\"hey\",\"foo\":1}";
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  /*
   * Test parsing of object containing a lot of strings: this way, new strings
   * will be allocated as we go, which should lead to the mjs string buffer
   * reallocation, and if it's not handled correctly, we'll get the asan
   * failure.
   */
  {
    /* We have to use temp string var because of vc98 */
    const char *is =
      "let s = '{\"foo1\": \"sdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdf\", \"foo2\": \"sdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdf\", \"foo3\": \"sdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdf\", \"foo4\": \"sdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdf\", \"foo5\": \"sdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdf\", \"foo6\": \"sdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdf\", \"foo7\": \"sdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdf\", \"foo8\": \"sdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdfsdf\"}'; "
      "let o = JSON.parse(s);"
      "1;"
      ;
    ASSERT_EXEC_OK(mjs_exec(mjs, is, &res));
  }

  ASSERT_EXEC_OK(mjs_exec(mjs,
        "let o = {foo: 1, bar: 'hey', arr: [1, 2, {foo: 100,}], 'null': null, 'undefined': undefined}; "
        "JSON.stringify(o)",
        &res));
  {
    const char *rs = "{\"null\":null,\"arr\":[1,2,{\"foo\":100}],\"bar\":\"hey\",\"foo\":1}";
    ASSERT_STREQ(mjs_get_cstring(mjs, &res), rs);
  }

  {
    const char *aa = "JSON.stringify(\"foo\")", *bb = "\"foo\"";
    ASSERT_EXEC_OK(mjs_exec(mjs, aa, &res));
    ASSERT_STREQ(mjs_get_cstring(mjs, &res), bb);
  }

  /* Test circular links and sparse arrays */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        "o.arr[10] = o;"
        "JSON.stringify(o)",
        &res));
  {
    const char *rs = "{\"null\":null,\"arr\":[1,2,{\"foo\":100},null,null,null,null,null,null,null,[Circular]],\"bar\":\"hey\",\"foo\":1}";
    ASSERT_STREQ(mjs_get_cstring(mjs, &res), rs);
  }

  /* Test parse */
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

  /* Test unicode escapes, valid and invalid */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        "let s = '{\"foo\": \"\\u0025\"}'; "
        "let o = JSON.parse(s);"
        "JSON.stringify(o)",
        &res));
  {
    /* We have to use temp string var because of vc98 */
    const char *rs = "{\"foo\":\"%\"}";
    ASSERT_STREQ(mjs_get_cstring(mjs, &res), rs);
  }

  /* Test unicode escapes, valid and invalid */
  {
    /* We have to use temp string var because of vc98 */
    const char *is =
      "let s = '{\"foo\": \"\\u002\"}'; "
      "let o = JSON.parse(s);";
    ASSERT_EQ(mjs_exec(mjs, is, &res), MJS_TYPE_ERROR);
  }

  mjs_disown(mjs, &res);

  return NULL;
}

const char *test_string(struct mjs *mjs) {
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

  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.at(0)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 'a');

  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.charCodeAt(-1)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 'f');

  ASSERT_EXEC_OK(mjs_exec(mjs, "'abcdef'.at(-1)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 'f');

  ASSERT_EXEC_OK(mjs_exec(mjs, "'\\xff'.charCodeAt(0)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 255);

  ASSERT_EXEC_OK(mjs_exec(mjs, "'\\xff'.at(0)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 255);

  ASSERT_EXEC_OK(mjs_exec(mjs, "'\\xff'.charCodeAt(1)", &res));
  ASSERT(res == MJS_UNDEFINED);

  ASSERT_EXEC_OK(mjs_exec(mjs, "'\\xff'.at(1)", &res));
  ASSERT(res == MJS_UNDEFINED);

  /* indexOf */
  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo bar'.indexOf('foo')", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 0);
  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo bar'.indexOf('bar')", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 4);
  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo bar'.indexOf('baz')", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), -1);
  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo bar'.indexOf('foo', 1)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), -1);
  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo bar'.indexOf('bar', 4)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 4);
  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo bar'.indexOf('bar', 5)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), -1);
  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo bar'.indexOf('bar', 10)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), -1);
  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo bar'.indexOf('')", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 0);
  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo bar'.indexOf('', 5)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 5);
  ASSERT_EXEC_OK(mjs_exec(mjs, "'foo bar'.indexOf('', 10)", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 7);
  ASSERT_EXEC_OK(mjs_exec(mjs, "'abc'.indexOf('bc')", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 1);

  /* chr(), error conditions - wrong argument */
  CHECK_TRUE("chr() === null;");
  CHECK_TRUE("chr('x') === null;");
  CHECK_TRUE("chr({}) === null;");
  CHECK_TRUE("chr([]) === null;");
  CHECK_TRUE("chr(false) === null;");
  CHECK_TRUE("chr(0x100) === null;");
  CHECK_TRUE("chr(-1) === null;");

  /* chr(), success */
  CHECK_TRUE("chr(0) === '\\x00';");
  CHECK_TRUE("chr(1) === '\\x01';");
  CHECK_TRUE("chr(0x61) === 'a';");
  CHECK_TRUE("chr(0xff) === '\\xff';");

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

  return NULL;
}

const char *test_call_api(struct mjs *mjs) {
  mjs_val_t func = MJS_UNDEFINED;
  mjs_val_t res = MJS_UNDEFINED;
  mjs_val_t obj = MJS_UNDEFINED;

  mjs_own(mjs, &func);

  /* function with no arguments */
  ASSERT_EQ(mjs_exec(mjs, "let a=123; function(){ a += 1; return a; }", &func), MJS_OK);

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

  /* test calling non-callable */
  ASSERT_EQ(mjs_call(mjs, &res, MJS_UNDEFINED, MJS_UNDEFINED, 0), MJS_TYPE_ERROR);
  ASSERT_EQ(mjs_apply(mjs, &res, MJS_UNDEFINED, MJS_UNDEFINED, 0, NULL), MJS_TYPE_ERROR);

  CHECK_NUMERIC("let f = function(a,b){return a+b;}; f.apply(null,[1,2])", 3);

  mjs_disown(mjs, &obj);
  mjs_disown(mjs, &res);
  mjs_disown(mjs, &func);

  return NULL;
}

const char *test_long_jump(struct mjs *mjs) {
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

  return NULL;
}

const char *test_foreign_str(struct mjs *mjs) {
  unsigned char *ptr = NULL;
  mjs_val_t res = MJS_UNDEFINED;

  mjs_own(mjs, &res);
  mjs_set_ffi_resolver(mjs, stub_dlsym);
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let calloc = ffi('void *calloc(int, int)');
          let ptr = calloc(100, 1);
          let str = mkstr(ptr, 3);
          ptr
          ), &res));
  ptr = (unsigned char *)mjs_get_ptr(mjs, res);

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

  ASSERT_EXEC_OK(mjs_exec(mjs, "let str2 = mkstr(ptr, 2, 10); str2", &res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "str2 === 'b\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00'", &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  /* TODO(dfrank): make foreign strings mutable? */

  free(ptr);
  ptr = NULL;
  mjs_disown(mjs, &res);

  return NULL;
}

const char *test_foreign_ptr(struct mjs *mjs) {
  unsigned char *ptr = NULL;
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
          let free = ffi('void free(void *)');
          free(null);  // null is allowed
          true;
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

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let get_null = ffi('void *ffi_get_null()');
          let ptr = get_null();
          ptr !== null
          ), &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 0);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let calloc = ffi('void *calloc(int, int)');
          let free = ffi('void free(void *)');
          let ptr = calloc(100, 1);
          free(ptr);
          ptr !== null
          ), &res));
  ASSERT_EQ(mjs_get_bool(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let set_byte = ffi('void ffi_set_byte(void *, int)');
          let calloc = ffi('void *calloc(int, int)');
          let free = ffi('void free(void *)');
          let ptr = calloc(100, 1);
          ptr;
          ), &res));
  ptr = (unsigned char *)mjs_get_ptr(mjs, res);
  ASSERT_EQ(ptr[0], 0);

  ASSERT_EXEC_OK(mjs_exec(mjs, "ptr[0] = 10; ptr[10] = 20;", &res));
  ASSERT_EQ(ptr[0], 10);
  ASSERT_EQ(ptr[10], 20);

  ptr[15] = 100;
  ASSERT_EXEC_OK(mjs_exec(mjs, "ptr[10] + ptr[15];", &res));
  ASSERT_EQ(mjs_get_int(mjs, res), 20 + 100);

  ASSERT_EXEC_OK(mjs_exec(mjs, "ptr[0] = 0", &res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "ptr[0] = 255", &res));

  ASSERT_EQ(mjs_exec(mjs, "ptr[0] = -1;", &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "only number 0 .. 255 can be assigned");

  ASSERT_EQ(mjs_exec(mjs, "ptr[0] = 256;", &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "only number 0 .. 255 can be assigned");

  ASSERT_EQ(mjs_exec(mjs, "ptr[0] = 'bar';", &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "only number 0 .. 255 can be assigned");

  ASSERT_EQ(mjs_exec(mjs, "ptr['foo'];", &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "index must be a number");

  ASSERT_EQ(mjs_exec(mjs, "ptr['foo'] = 1;", &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "index must be a number");

  /*
   * TODO(dfrank): probably support non-numeric values which could be converted
   * to number.
   */
  ASSERT_EQ(mjs_exec(mjs, "ptr['1'] = 1;", &res), MJS_TYPE_ERROR);
  ASSERT_STREQ(mjs->error_msg, "index must be a number");

  memset(ptr, 0x00, 100);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          set_byte(ptr, 0xf0);

          let ptr2 = ptr + 10;
          set_byte(ptr2, 0xf1);

          ptr2 += 10;
          set_byte(ptr2, 0xf2);

          set_byte(ptr2-1, 0xf3);

          ptr2 -= 2;
          set_byte(ptr2, 0xf4);

          ptr2 = 5 + ptr;
          set_byte(ptr + 1, ptr2 - ptr);

          ptr2++;
          set_byte(ptr + 2, ptr2 - ptr);

          ptr2--;
          set_byte(ptr + 3, ptr2 - ptr);
          ), &res));

  ASSERT_EQ(ptr[0], 0xf0);
  ASSERT_EQ(ptr[10], 0xf1);
  ASSERT_EQ(ptr[20], 0xf2);
  ASSERT_EQ(ptr[19], 0xf3);
  ASSERT_EQ(ptr[18], 0xf4);
  ASSERT_EQ(ptr[1], 5);
  ASSERT_EQ(ptr[2], 6);
  ASSERT_EQ(ptr[3], 5);

  /* ptr + ptr2 is not allowed */
  ASSERT_EQ(mjs_exec( mjs, "ptr + ptr2", &res), MJS_TYPE_ERROR);

  /* ptr * ptr2 is also not allowed */
  ASSERT_EQ(mjs_exec( mjs, "ptr * ptr2", &res), MJS_TYPE_ERROR);

  free(ptr);
  mjs_disown(mjs, &res);

  return NULL;
}

const char *test_backtrace(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  ASSERT_EQ(mjs_exec(mjs, "foo", &res), MJS_REFERENCE_ERROR);
  ASSERT_STREQ(mjs->stack_trace, "  at <stdin>:1\n");

  ASSERT_EQ(mjs_exec(mjs, "function f1() { return bar; };\nf1();\n", &res), MJS_REFERENCE_ERROR);
  ASSERT_STREQ(mjs->stack_trace,
      "  at <stdin>:1\n"
      "  at <stdin>:2\n"
      );

  ASSERT_EQ(mjs_exec(mjs, 
        "function f1() { return bar; };"
        "\n\n\n\n\n\n\n\n\n\n"
        "\n\n\n\n\n\n\n\n\n\n"
        "\n\n\n\n\n\n\n\n\n\n"
        "\n\n\n\n\n\n\n\n\n\n"
        "\n\n\n\n\n\n\n\n\n\n"
        "\n\n\n\n\n\n\n\n\n\n"
        "\n\n\n\n\n\n\n\n\n\n"
        "\n\n\n\n\n\n\n\n\n\n"
        "\n\n\n\n\n\n\n\n\n\n"
        "\n\n\n\n\n\n\n\n\n\n"
        "f1();\n",
        &res), MJS_REFERENCE_ERROR);
  ASSERT_STREQ(mjs->stack_trace,
      "  at <stdin>:1\n"
      "  at <stdin>:101\n"
      );

  ASSERT_EQ(mjs_exec(mjs, "load('tests/err1.js'); err1f1();", &res), MJS_REFERENCE_ERROR);
  ASSERT_STREQ(mjs->stack_trace,
      "  at tests/err1.js:3\n"
      "  at tests/err1.js:7\n"
      "  at <stdin>:1\n"
      );

  ASSERT_EQ(mjs_exec(mjs, "load('tests/err2.js'); err2f1();", &res), MJS_REFERENCE_ERROR);
  ASSERT_STREQ(mjs->stack_trace,
      "  at tests/err2.js:7\n"
      "  at tests/err2.js:3\n"
      "  at <stdin>:1\n"
      );

  /* Exception in the argument to a JS function */
  ASSERT_EQ(mjs_exec(mjs, STRINGIFY(
          function f1(a) { return a; };
          load('tests/err1.js');
          f1(err1f1());
          ), &res), MJS_REFERENCE_ERROR);
  ASSERT_STREQ(mjs->stack_trace,
      "  at tests/err1.js:3\n"
      "  at tests/err1.js:7\n"
      "  at <stdin>:1\n"
      );

  /* Exception in the argument to a ffi-ed function */
  ASSERT_EQ(mjs_exec(mjs, STRINGIFY(
          let malloc = ffi('void *malloc(int)');
          load('tests/err1.js');
          malloc(err1f1());
          ), &res), MJS_REFERENCE_ERROR);
  ASSERT_STREQ(mjs->stack_trace,
      "  at tests/err1.js:3\n"
      "  at tests/err1.js:7\n"
      "  at <stdin>:1\n"
      );

  /* Exception in the argument to a cfunction */
  ASSERT_EQ(mjs_exec(mjs, STRINGIFY(
          load('tests/err1.js');
          print(err1f1());
          ), &res), MJS_REFERENCE_ERROR);
  ASSERT_STREQ(mjs->stack_trace,
      "  at tests/err1.js:3\n"
      "  at tests/err1.js:7\n"
      "  at <stdin>:1\n"
      );

  mjs_disown(mjs, &res);

  return NULL;
}

/*
 * NOTE: this function should not be used with RUN_TEST_MJS, because this test
 * relies on the fact that "test/module1.js" is not loaded yet, but
 * when RUN_TEST_MJS does the second pass, it's already loaded.
 */
const char *test_load(void) {
  size_t len1, len2;
  struct mjs *mjs = mjs_create();

  mjs_val_t func_load = MJS_UNDEFINED;
  mjs_val_t func_add_foo_to_s = MJS_UNDEFINED;
  mjs_val_t func_get_s = MJS_UNDEFINED;
  mjs_val_t func_set_foo = MJS_UNDEFINED;
  mjs_val_t func_faulty = MJS_UNDEFINED;
  mjs_val_t res = MJS_UNDEFINED;

  mjs_own(mjs, &func_add_foo_to_s);
  mjs_own(mjs, &func_get_s);
  mjs_own(mjs, &func_set_foo);
  mjs_own(mjs, &func_faulty);
  mjs_own(mjs, &func_load);
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  /*
   * Make sure repeated load of the same file does not generate new bcode
   *
   * Note that the code which actually loads the file should be a function
   * which we'll save and call twice; if we were executing load() directly
   * a few times, the code which calls load() would be added to bcode.
   */
  ASSERT_EXEC_OK(mjs_exec(mjs, "let s = ''; let foo = 2;", &res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "function(){s += JSON.stringify(foo) + '_';}", &func_add_foo_to_s));
  ASSERT_EXEC_OK(mjs_exec(mjs, "function(){return s;}", &func_get_s));
  ASSERT_EXEC_OK(mjs_exec(mjs, "function(newfoo){foo = newfoo;}", &func_set_foo));
  ASSERT_EXEC_OK(mjs_exec(mjs, "function(){load('tests/module1.js'); return foo;}", &func_load));
  ASSERT_EXEC_OK(mjs_exec(mjs, "function(){return non_existing;}", &func_faulty));

  ASSERT_EXEC_OK(mjs_apply(mjs, &res, func_add_foo_to_s, MJS_UNDEFINED, 0, NULL));

  ASSERT_EXEC_OK(mjs_apply(mjs, &res, func_load, MJS_UNDEFINED, 0, NULL));
  len1 = mjs->bcode_parts.len;

  ASSERT_EXEC_OK(mjs_call(mjs, &res, func_set_foo, MJS_UNDEFINED, 1, res));

  ASSERT_EXEC_OK(mjs_apply(mjs, &res, func_add_foo_to_s, MJS_UNDEFINED, 0, NULL));

  ASSERT_EXEC_OK(mjs_call(mjs, &res, func_set_foo, MJS_UNDEFINED, 1, mjs_mk_number(mjs, 100)));

  ASSERT_EXEC_OK(mjs_apply(mjs, &res, func_add_foo_to_s, MJS_UNDEFINED, 0, NULL));

  ASSERT_EXEC_OK(mjs_apply(mjs, &res, func_load, MJS_UNDEFINED, 0, NULL));
  len2 = mjs->bcode_parts.len;
  ASSERT_EQ(len1, len2);

  ASSERT_EXEC_OK(mjs_call(mjs, &res, func_set_foo, MJS_UNDEFINED, 1, res));

  ASSERT_EXEC_OK(mjs_apply(mjs, &res, func_add_foo_to_s, MJS_UNDEFINED, 0, NULL));

  ASSERT_EXEC_OK(mjs_apply(mjs, &res, func_get_s, MJS_UNDEFINED, 0, NULL));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res), "2_1_100_100_");

  ASSERT_EXEC_RES(mjs_apply(mjs, &res, func_faulty, MJS_UNDEFINED, 0, NULL), MJS_REFERENCE_ERROR);

  ASSERT_EXEC_OK(mjs_exec(mjs, "let o={}; load('tests/module1.js', o); o.foo", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "function test(){ let o={}; load('tests/module1.js', o); return o.foo; }; test()", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 1);

  mjs_disown(mjs, &res);
  mjs_disown(mjs, &func_add_foo_to_s);
  mjs_disown(mjs, &func_get_s);
  mjs_disown(mjs, &func_set_foo);
  mjs_disown(mjs, &func_faulty);
  mjs_disown(mjs, &func_load);

  cleanup_mjs(&mjs);

  return NULL;
}

const char *test_dataview(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  unsigned char *ptr = NULL;
  unsigned char buf[20] = "abcd1234 :-)\xff\xff\xff\xff";

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
  ASSERT_EXEC_OK(mjs_exec(mjs, "let peeku = ffi('double mjs_mem_get_uint(void*,int,int)')", &res));
  ASSERT_EXEC_OK(mjs_exec(mjs, "let pokeu = ffi('void mjs_mem_set_uint(void*,int,int,int)')", &res));

  ASSERT_EXEC_OK(mjs_exec(mjs, "let b2 = peek('booo', 0);", &res));

  CHECK_NUMERIC("peeku(buf, 1, 1)", 'a');
  CHECK_NUMERIC("peeku(peek(buf,1), 1, 1)", 'b');
  CHECK_NUMERIC("peeku(buf, 2, 1)", 0x6162);
  CHECK_NUMERIC("peeku(buf, 2, 0)", 0x6261);
  CHECK_NUMERIC("peeku(buf, 3, 1)", 0x616263);
  CHECK_NUMERIC("peeku(buf, 4, 1)", 0x61626364);

  CHECK_NUMERIC("peeku(peek(buf,12), 4, 1)", 0xffffffff);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let calloc = ffi('void *calloc(int, int)');
          let ptr = calloc(100, 1);
          ptr;
          ), &res));
  ptr = (unsigned char *)mjs_get_ptr(mjs, res);

  ptr[5] = 0x30;
  ptr[6] = 0x31;
  ptr[7] = 0x32;

  ptr[10] = 0xff;
  ptr[11] = 0xfe;
  ptr[12] = 0xfd;

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          load("lib/api_dataview.js");
          let dw = DataView.create(ptr, 0, 16);
          ), &res));

  // Test 8bit values
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          for (let i = 0; i < 16; i++) {
            s += JSON.stringify(dw.getUint8(i)) + ":" + JSON.stringify(dw.getInt8(i)) + "_";
          }
          s;
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res),
      "0:0_0:0_0:0_0:0_0:0_48:48_49:49_50:50_0:0_0:0_255:-1_254:-2_253:-3_0:0_0:0_0:0_"
      );

  // Test 16bit values
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          for (let i = 0; i < 16; i += 2) {
            s += JSON.stringify(dw.getUint16(i)) + ":" + JSON.stringify(dw.getInt16(i)) + "_";
          }
          s;
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res),
      "0:0_0:0_48:48_12594:12594_0:0_65534:-2_64768:-768_0:0_"
      );

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          for (let i = 0; i < 16; i += 2) {
            s += JSON.stringify(dw.getUint16(i, true)) + ":" + JSON.stringify(dw.getInt16(i, true)) + "_";
          }
          s;
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res),
      "0:0_0:0_12288:12288_12849:12849_0:0_65279:-257_253:253_0:0_"
      );

  // Test 32bit values
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          for (let i = 0; i < 16; i += 4) {
            s += JSON.stringify(dw.getUint32(i)) + ":" + JSON.stringify(dw.getInt32(i)) + "_";
          }
          s;
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res),
      "0:0_3158322:3158322_65534:65534_4244635648:-50331648_"
      );

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          for (let i = 0; i < 16; i += 4) {
            s += JSON.stringify(dw.getUint32(i, true)) + ":" + JSON.stringify(dw.getInt32(i, true)) + "_";
          }
          s;
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res),
      "0:0_842084352:842084352_4278124544:-16842752_253:253_"
      );

  // Test setting

  memset(ptr, 0x00, 100);
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          dw.setInt8(2, -2);
          dw.setInt8(3, 10);
          dw.setUint8(4, 0xff);
          for (let i = 0; i < 8; i++) {
            s += JSON.stringify(dw.getUint8(i)) + "_";
          }
          s;
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res),
      "0_0_254_10_255_0_0_0_"
      );

  memset(ptr, 0x00, 100);
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          dw.setInt16(1, -2);
          dw.setUint16(4, 0x1234);
          dw.setUint16(6, -2, true);
          for (let i = 0; i < 8; i++) {
            s += JSON.stringify(dw.getUint8(i)) + "_";
          }
          s;
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res),
      "0_255_254_0_18_52_254_255_"
      );

  memset(ptr, 0x00, 100);
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          dw.setInt32(1, -2);
          dw.setUint32(5, 0x87654321);
          dw.setUint32(9, -2, true);
          for (let i = 0; i < 16; i++) {
            s += JSON.stringify(dw.getUint8(i)) + "_";
          }
          s;
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res),
      "0_255_255_255_254_135_101_67_33_254_255_255_255_0_0_0_"
      );
  /* Test non-zero offset */
  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          let s = "";
          let dw2 = DataView.create(ptr, 2);
          for (let i = 0; i < 16; i++) {
            s += JSON.stringify(dw2.getUint8(i)) + "_";
          }
          s;
          ), &res));
  ASSERT_STREQ(mjs_get_cstring(mjs, &res),
      "255_255_254_135_101_67_33_254_255_255_255_0_0_0_0_0_"
      );

  /* Make sure out-of-bounds check works */
  ASSERT_EQ(mjs_exec(mjs,
        STRINGIFY(
          let dw2 = DataView.create(ptr, 0, 16);
          dw2.getUint8(16);
          ), &res), MJS_TYPE_ERROR);

  ASSERT_EQ(mjs_exec(mjs,
        STRINGIFY(
          let dw2 = DataView.create(ptr, 0, 16);
          dw2.getUint16(15);
          ), &res), MJS_TYPE_ERROR);

  ASSERT_EQ(mjs_exec(mjs,
        STRINGIFY(
          let dw2 = DataView.create(ptr, 0, 16);
          dw2.getUint32(13);
          ), &res), MJS_TYPE_ERROR);

  free(ptr);
  ptr = NULL;

  mjs_disown(mjs, &res);
  return NULL;
}

const char *test_lib_math(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);

  mjs_set_ffi_resolver(mjs, stub_dlsym);

  ASSERT_EXEC_OK(mjs_exec(mjs,
        STRINGIFY(
          load("lib/api_math.js");
          ), &res));

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.ceil(1.4)", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.floor(1.4)", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.round(1.4)", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 1);

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.round(1.5)", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 2);

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.max(100, 200)", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 200);

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.min(100, 200)", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 100);

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.abs(123)", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 123);

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.abs(-123)", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 123);

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.sqrt(1024)", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), 32);

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.exp(5)", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), exp(5));

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.log(5.5)", &res));
  ASSERT(fabs(mjs_get_double(mjs, res) - log(5.5)) < 0.0001);

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.pow(3, 5)", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), pow(3, 5));

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.sin(0.2)", &res));
  ASSERT(fabs(mjs_get_double(mjs, res) - sin(0.2)) < 0.0001);

  ASSERT_EXEC_OK(mjs_exec(mjs, "Math.cos(0.2)", &res));
  ASSERT_EQ(mjs_get_double(mjs, res), cos(0.2));

  mjs_disown(mjs, &res);
  return NULL;
}

struct my_struct2 {
  int8_t i8;
  int16_t i16;
  uint8_t u8;
  uint16_t u16;
};

static const struct mjs_c_struct_member my_struct2_descr[] = {
  {"i8", offsetof(struct my_struct2, i8), MJS_STRUCT_FIELD_TYPE_INT8, NULL},
  {"i16", offsetof(struct my_struct2, i16), MJS_STRUCT_FIELD_TYPE_INT16, NULL},
  {"u8", offsetof(struct my_struct2, u8), MJS_STRUCT_FIELD_TYPE_UINT8, NULL},
  {"u16", offsetof(struct my_struct2, u16), MJS_STRUCT_FIELD_TYPE_UINT16, NULL},
  {NULL, 0, MJS_STRUCT_FIELD_TYPE_INVALID, NULL},
};

struct my_struct {
  int a;
  const char *b;
  double c;
  struct mg_str d;
  struct mg_str *e;
  float f;
  bool g;
  struct my_struct2 s;
  struct my_struct2 *sp;
  int x;
};

static struct my_struct *s_ts = NULL;

mjs_val_t custom_value_func(struct mjs *mjs, void *ap) {
  return mjs_mk_number(mjs, (*((int *) ap)) + 10);
}

static const struct mjs_c_struct_member my_struct_descr[] = {
  {"a", offsetof(struct my_struct, a), MJS_STRUCT_FIELD_TYPE_INT, NULL},
  {"b", offsetof(struct my_struct, b), MJS_STRUCT_FIELD_TYPE_CHAR_PTR, NULL},
  {"c", offsetof(struct my_struct, c), MJS_STRUCT_FIELD_TYPE_DOUBLE, NULL},
  {"d", offsetof(struct my_struct, d), MJS_STRUCT_FIELD_TYPE_MG_STR, NULL},
  {"e", offsetof(struct my_struct, e), MJS_STRUCT_FIELD_TYPE_MG_STR_PTR, NULL},
  {"f", offsetof(struct my_struct, f), MJS_STRUCT_FIELD_TYPE_FLOAT, NULL},
  {"g", offsetof(struct my_struct, g), MJS_STRUCT_FIELD_TYPE_BOOL, NULL},
  {"s", offsetof(struct my_struct, s), MJS_STRUCT_FIELD_TYPE_STRUCT, my_struct2_descr},
  {"sp", offsetof(struct my_struct, sp), MJS_STRUCT_FIELD_TYPE_STRUCT_PTR, my_struct2_descr},
  {"x", offsetof(struct my_struct, x), MJS_STRUCT_FIELD_TYPE_CUSTOM, custom_value_func},
  {NULL, 0, MJS_STRUCT_FIELD_TYPE_INVALID, NULL},
};

static const void *get_my_struct(void) {
  return s_ts;
}

static const struct mjs_c_struct_member *get_my_struct_descr(void) {
  return my_struct_descr;
};

const char *test_s2o(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);
  mjs_set_ffi_resolver(mjs, stub_dlsym);
  s_ts = NULL;
  ASSERT_EXEC_OK(mjs_exec(mjs, "let s = undefined, sd = undefined, o;", &res));
  {
    ASSERT_EXEC_OK(mjs_exec(mjs, "o = s2o(s, sd);", &res));
    ASSERT_TRUE(mjs_is_undefined(res));
    ASSERT_EXEC_OK(mjs_exec(mjs, "o = s2o(123, 456);", &res));
    ASSERT_TRUE(mjs_is_undefined(res));
  }
  {
    ASSERT_EXEC_OK(mjs_exec(mjs, "s = ffi('void *get_my_struct(void)')();", &res));
    ASSERT_EXEC_OK(mjs_exec(mjs, "o = s2o(s, sd);", &res));
    ASSERT_TRUE(mjs_is_undefined(res));
  }
  {
    ASSERT_EXEC_OK(mjs_exec(mjs, "sd = ffi('void *get_my_struct_descr(void)')();", &res));
    ASSERT_EXEC_OK(mjs_exec(mjs, "o = s2o(s, sd);", &res));
    ASSERT_TRUE(mjs_is_undefined(res));
  }
  {
    struct mg_str baz = mg_mk_str_n("bazaar", 3);
    struct my_struct ts = {
        17, "foo", 1.23, {"bar!", 3}, NULL, 4.56f, true,
        {-10, -20000, 130, 20000},
        NULL, 32,
    };
    s_ts = &ts;
    ASSERT_EXEC_OK(mjs_exec(mjs, "s = ffi('void *get_my_struct(void)')();", &res));
    ASSERT_EXEC_OK(mjs_exec(mjs, "o = s2o(s, sd);", &res));
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.a", &res));
    ASSERT_EQ(mjs_get_int(mjs, res), 17);
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.b", &res));
    ASSERT_STREQ(mjs_get_cstring(mjs, &res), "foo");
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.c", &res));
    ASSERT_EQ(mjs_get_double(mjs, res), 1.23);
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.d", &res));
    ASSERT_STREQ(mjs_get_cstring(mjs, &res), "bar");
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.e", &res));
    ASSERT_TRUE(mjs_is_null(res));
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.f", &res));
    ASSERT_EQ(mjs_get_double(mjs, res), 4.56f);
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.g", &res));
    ASSERT_EQ(mjs_get_bool(mjs, res), true);
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.s.i8", &res));
    ASSERT_EQ(mjs_get_int(mjs, res), -10);
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.s.i16", &res));
    ASSERT_EQ(mjs_get_int(mjs, res), -20000);
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.s.u8", &res));
    ASSERT_EQ(mjs_get_int(mjs, res), 130);
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.s.u16", &res));
    ASSERT_EQ(mjs_get_int(mjs, res), 20000);
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.sp", &res));
    ASSERT_TRUE(mjs_is_null(res));
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.x", &res));
    ASSERT_EQ(mjs_get_int(mjs, res), 42);

    ts.e = &baz;
    ts.sp = &ts.s;
    ASSERT_EXEC_OK(mjs_exec(mjs, "o = s2o(s, sd);", &res));
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.e", &res));
    ASSERT_STREQ(mjs_get_cstring(mjs, &res), "baz");
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.sp.i8", &res));
    ASSERT_EQ(mjs_get_int(mjs, res), -10);
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.sp.i16", &res));
    ASSERT_EQ(mjs_get_int(mjs, res), -20000);
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.sp.u8", &res));
    ASSERT_EQ(mjs_get_int(mjs, res), 130);
    ASSERT_EXEC_OK(mjs_exec(mjs, "o.sp.u16", &res));
    ASSERT_EQ(mjs_get_int(mjs, res), 20000);
  }

  mjs_disown(mjs, &res);
  return NULL;
}

const char *test_parser(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_own(mjs, &res);
  CHECK_NUMERIC("\f\v\r\n\t1", 1);
  ASSERT_EQ(mjs_exec(mjs, "\a1", &res), MJS_SYNTAX_ERROR);
  CHECK_NUMERIC("1,2,3", 3);
  CHECK_NUMERIC("let f = function(x){return x;}; f(1),f(2),f(3)", 3);
  ASSERT_EXEC_OK(mjs_exec(mjs, ";", &res));
  ASSERT(res == MJS_UNDEFINED);

  /* 51 []s is ok */
  ASSERT_EQ(mjs_exec(mjs,
        "let a = [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]];"
        "let b = [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]];"
        , &res), MJS_OK);

  /* 52 []s is not ok */
  ASSERT_EQ(mjs_exec(mjs,
        "let a = [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]];"
        "let b = [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]];"
        , &res), MJS_SYNTAX_ERROR);
  ASSERT_STREQ(mjs->error_msg, "parser stack overflow");

  {
    char *p = calloc(7000, 1);
    memset(p, '{', 7000-1);
    ASSERT_EQ(mjs_exec(mjs, p , &res), MJS_SYNTAX_ERROR);
    free(p);
  }

  mjs_disown(mjs, &res);
  return NULL;
}

void tests_setup(void) {
}

const char *tests_run(const char *filter) {
  RUN_TEST_MJS(test_parser);
  RUN_TEST_MJS(test_arithmetic);
  RUN_TEST_MJS(test_block);
  RUN_TEST_MJS(test_function);
  RUN_TEST_MJS(test_cfunction);
  RUN_TEST_MJS(test_if);
  RUN_TEST_MJS(test_comparison);
  RUN_TEST_MJS(test_logic);
  RUN_TEST_MJS(test_errors);
  RUN_TEST_MJS(test_this);
  RUN_TEST_MJS(test_while);
  RUN_TEST_MJS(test_for_loop);
  RUN_TEST_MJS(test_for_in_loop);
  RUN_TEST_MJS(test_primitives);
  RUN_TEST_MJS(test_objects);
  RUN_TEST_MJS(test_arrays);
  RUN_TEST_MJS(test_json);
  RUN_TEST_MJS(test_string);
  RUN_TEST_MJS(test_call_api);
  RUN_TEST_MJS(test_long_jump);
  RUN_TEST_MJS(test_foreign_str);
  RUN_TEST_MJS(test_foreign_ptr);
  RUN_TEST_MJS(test_backtrace);
  RUN_TEST(test_load);

  /* FFI */
  RUN_TEST(test_func1);
  RUN_TEST(test_func2);
  RUN_TEST(test_func3);
  RUN_TEST(test_func4);
  RUN_TEST(test_func5);
  RUN_TEST(test_func6);

  RUN_TEST_MJS(test_parse_ffi_signature);
  RUN_TEST_MJS(test_call_ffi);
  RUN_TEST_MJS(test_call_ffi_cb_vu);
  RUN_TEST_MJS(test_call_ffi_cb_viu);
  RUN_TEST_MJS(test_call_ffi_cb_vui);
  RUN_TEST_MJS(test_call_ffi_cb_vui_unused_userdata);
  RUN_TEST_MJS(test_call_ffi_cb_iiui);
  RUN_TEST_MJS(test_call_ffi_cb_err);

  RUN_TEST_MJS(test_dataview);

  RUN_TEST_MJS(test_lib_math);
  RUN_TEST(test_exec);

  RUN_TEST_MJS(test_s2o);

  return NULL;
}

void tests_teardown(void) {
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */
