/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

#ifdef MJS_MAIN

// #include <dlfcn.h>

#include "mjs/src/mjs_core.h"
#include "mjs/src/mjs_exec.h"
#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_primitive.h"
#include "mjs/src/mjs_util.h"

int main(int argc, char *argv[]) {
  struct mjs *mjs = mjs_create();
  mjs_val_t res = MJS_UNDEFINED;
  mjs_err_t err = MJS_OK;
  int i;

  for (i = 1; i < argc && argv[i][0] == '-'; i++) {
    if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
      cs_log_set_level(atoi(argv[++i]));
    } else if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
      err = mjs_exec(mjs, argv[++i], &res);
    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printf("mJS (c) Cesanta, built: " __DATE__ "\n");
      printf("Usage:\n  ");
      printf("%s [-l debug_level] [-e expression] js_file ...\n", argv[0]);
      return EXIT_SUCCESS;
    } else {
      fprintf(stderr, "Unknown flag: [%s]\n", argv[i]);
      return EXIT_FAILURE;
    }
  }
  for (; i < argc; i++) {
    err = mjs_exec_file(mjs, argv[i], 1, &res);
  }

  if (err == MJS_OK) {
    mjs_fprintf(res, mjs, stdout);
    putchar('\n');
  } else {
    mjs_print_error(mjs, stdout, NULL, 1 /* print_stack_trace */);
  }
  mjs_destroy(mjs);

  return EXIT_SUCCESS;
}
#endif
