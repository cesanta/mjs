/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#include "mjs/src/mjs_core.h"
#include "mjs/src/mjs_dataview.h"
#include "mjs/src/mjs_exec.h"
#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_json.h"
#include "mjs/src/mjs_object.h"
#include "mjs/src/mjs_primitive.h"
#include "mjs/src/mjs_string.h"
#include "mjs/src/mjs_util.h"

static void mjs_print(struct mjs *mjs) {
  size_t i, num_args = mjs_nargs(mjs);
  for (i = 0; i < num_args; i++) {
    mjs_fprintf(mjs_arg(mjs, i), mjs, stdout);
    putchar(' ');
  }
  putchar('\n');
  mjs_return(mjs, MJS_UNDEFINED);
}

static void mjs_load(struct mjs *mjs) {
  mjs_val_t res = MJS_UNDEFINED;
  mjs_val_t arg0 = mjs_arg(mjs, 0);
  mjs_val_t arg1 = mjs_arg(mjs, 1);

  if (mjs_is_string(arg0)) {
    const char *path = mjs_get_cstring(mjs, &arg0);
    mjs_val_t *bottom = vptr(&mjs->scopes, 0), global = *bottom;
    mjs_own(mjs, &global);
    if (mjs_is_object(arg1)) *bottom = arg1;
    mjs_err_t ret = mjs_exec_file(mjs, path, &res);
    if (ret != MJS_OK) {
      /*
       * arg0 and path might be invalidated by executing a file, so refresh
       * them
       */
      arg0 = mjs_arg(mjs, 0);
      path = mjs_get_cstring(mjs, &arg0);
      mjs_set_errorf(mjs, ret, "failed to read file \"%s\"", path);
      goto clean;
    }
    if (mjs_is_object(arg1)) *bottom = global;

  clean:
    mjs_disown(mjs, &global);
  }
  mjs_return(mjs, res);
}

static void mjs_get_mjs(struct mjs *mjs) {
  mjs_return(mjs, mjs_mk_foreign(mjs, mjs));
}

void mjs_init_builtin(struct mjs *mjs, mjs_val_t obj) {
  mjs_val_t v;

  mjs_set(mjs, obj, "global", ~0, obj);

  mjs_set(mjs, obj, "load", ~0, mjs_mk_foreign(mjs, mjs_load));
  mjs_set(mjs, obj, "print", ~0, mjs_mk_foreign(mjs, mjs_print));
  mjs_set(mjs, obj, "ffi", ~0, mjs_mk_foreign(mjs, mjs_ffi_call));
  mjs_set(mjs, obj, "ffi_cb_free", ~0, mjs_mk_foreign(mjs, mjs_ffi_cb_free));
  mjs_set(mjs, obj, "fstr", ~0, mjs_mk_foreign(mjs, mjs_fstr));
  mjs_set(mjs, obj, "getMJS", ~0, mjs_mk_foreign(mjs, mjs_get_mjs));
  mjs_set(mjs, obj, "die", ~0, mjs_mk_foreign(mjs, mjs_die));

  /*
   * Populate JSON.parse() and JSON.stringify()
   */
  v = mjs_mk_object(mjs);
  mjs_set(mjs, v, "stringify", ~0, mjs_mk_foreign(mjs, mjs_op_json_stringify));
  mjs_set(mjs, v, "parse", ~0, mjs_mk_foreign(mjs, mjs_op_json_parse));
  mjs_set(mjs, obj, "JSON", ~0, v);

  /*
   * Populate Object.create()
   */
  v = mjs_mk_object(mjs);
  mjs_set(mjs, v, "create", ~0, mjs_mk_foreign(mjs, mjs_op_create_object));
  mjs_set(mjs, obj, "Object", ~0, v);
}
