#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/types.h>

#include "common/cs_dbg.h"
#include "common/test_util.h"
#include "mjs/src/ffi/ffi.h"

int testfunc1(int a, int b, int c, int d) {
  printf("called testfunc1 with a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
  return a + b + c + d;
}

static const char *test_func1() {
  struct ffi_arg res;
  struct ffi_arg args[4];

  res.size = 4;
  res.is_float = 0;
  res.v.i = 0;
  ffi_set_int32(&args[0], 1);
  ffi_set_int32(&args[1], 2);
  ffi_set_int32(&args[2], 3);
  ffi_set_int32(&args[3], 4);

  ffi_call((ffi_fn_t) testfunc1, 4, &res, args);

  ASSERT_EQ(res.v.i, 10);

  return NULL;
}

int testfunc2(int a, double b) {
  printf("called testfunc2 with a=%d, b=%lg\n", a, b);
  return a + b;
}

static const char *test_func2() {
  struct ffi_arg res;
  struct ffi_arg args[2];
  res.size = 4;
  res.is_float = 0;
  ffi_set_int32(&args[0], 1);
  ffi_set_double(&args[1], 2);

  ffi_call((ffi_fn_t) testfunc2, 2, &res, args);

  ASSERT_EQ(res.v.i, 3);

  return NULL;
}

int testfunc3(double a, double b) {
  printf("called testfunc3 with a=%lg, b=%lg\n", a, b);
  return a + b;
}

static const char *test_func3() {
  struct ffi_arg res;
  struct ffi_arg args[2];
  res.size = 4;
  res.is_float = 0;
  ffi_set_double(&args[0], 1);
  ffi_set_double(&args[1], 2);

  ffi_call((ffi_fn_t) testfunc3, 2, &res, args);

  ASSERT_EQ(res.v.i, 3);

  return NULL;
}

double testfunc4(int a, int b, int c, int d) {
  printf("called testfunc4 with a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
  return a + b + c + d;
}

static const char *test_func4() {
  struct ffi_arg res;
  struct ffi_arg args[4];

  res.size = 8;
  res.is_float = 1;
  res.v.d = 0;
  ffi_set_int32(&args[0], 1);
  ffi_set_int32(&args[1], 2);
  ffi_set_int32(&args[2], 3);
  ffi_set_int32(&args[3], 4);

  ffi_call((ffi_fn_t) testfunc4, 4, &res, args);

  ASSERT_EQ(res.v.d, 10);

  return NULL;
}

double testfunc5(int a, double b) {
  printf("called testfunc1 with a=%d, b=%lg\n", a, b);
  return a + b;
}

static const char *test_func5() {
  struct ffi_arg res;
  struct ffi_arg args[2];
  res.size = 8;
  res.is_float = 1;
  ffi_set_int32(&args[0], 1);
  ffi_set_double(&args[1], 2);

  ffi_call((ffi_fn_t) testfunc5, 2, &res, args);

  ASSERT_EQ(res.v.d, 3);

  return NULL;
}

double testfunc6(double a, double b) {
  printf("called testfunc6 with a=%lg, b=%lg\n", a, b);
  return a + b;
}

static const char *test_func6() {
  struct ffi_arg res;
  struct ffi_arg args[2];
  res.size = 8;
  res.is_float = 1;
  ffi_set_double(&args[0], 1);
  ffi_set_double(&args[1], 2);

  ffi_call((ffi_fn_t) testfunc6, 2, &res, args);

  ASSERT_EQ(res.v.d, 3);

  return NULL;
}

static const char *run_all_tests(const char *filter, double *total_elapsed) {
  RUN_TEST(test_func1);
  RUN_TEST(test_func2);
  RUN_TEST(test_func3);
  RUN_TEST(test_func4);
  RUN_TEST(test_func5);
  RUN_TEST(test_func6);
  return NULL;
}

int main(int argc, char *argv[]) {
  const char *filter = argc > 1 ? argv[1] : "";
  double total_elapsed = 0.0;
  const char *fail_msg;

  fail_msg = run_all_tests(filter, &total_elapsed);
  printf("%s, run %d in %.3fs\n", fail_msg ? "FAIL" : "PASS", num_tests,
         total_elapsed);
  return fail_msg == NULL ? 0 : 1;
}
