/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#include "mjs/src/mjs_core.h"
#include "mjs/src/mjs_exec.h"
#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_primitive.h"
#include "mjs/src/mjs_string.h"
#include "mjs/src/mjs_util.h"
#include "mjs/src/ffi/ffi.h"

/*
 * on linux this is enabled only if __USE_GNU is defined, but we cannot set it
 * because dlfcn could have been included already.
 */
#ifndef RTLD_DEFAULT
#define RTLD_DEFAULT NULL
#endif

typedef void(cb_fn_t)(void);

/*
 * Data of the two related arguments: callback function pointer and the
 * userdata for it
 */
struct cbdata {
  /* JS callback function */
  mjs_val_t func;
  /* JS userdata */
  mjs_val_t userdata;

  /* C function signature source */
  const char *signature;
  size_t signature_len;
  /*
   * Descriptor of the C callback function signature.
   */
  ffi_sig_t sig;
  /* index of the function pointer param */
  int8_t func_idx;
  /* index of the userdata param */
  int8_t userdata_idx;
};

void mjs_set_ffi_resolver(struct mjs *mjs, mjs_ffi_resolver_t *dlsym) {
  mjs->dlsym = dlsym;
}

static cval_type_t parse_cval_type(struct mjs *mjs, const char *s,
                                   const char *e) {
  while (e > s && e[-1] == ' ') e--; /* Trim trailing spaces */
  if (strncmp(s, "void", e - s) == 0) {
    return CVAL_TYPE_NONE;
  } else if (strncmp(s, "userdata", e - s) == 0) {
    return CVAL_TYPE_USERDATA;
  } else if (strncmp(s, "int", e - s) == 0) {
    return CVAL_TYPE_INT;
  } else if (strncmp(s, "double", e - s) == 0) {
    return CVAL_TYPE_DOUBLE;
  } else if (strncmp(s, "char*", 5) == 0 || strncmp(s, "char *", 6) == 0) {
    return CVAL_TYPE_CHAR_PTR;
  } else if (strncmp(s, "void*", 5) == 0 || strncmp(s, "void *", 6) == 0) {
    return CVAL_TYPE_VOID_PTR;
  } else {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "failed to parse val type \"%.*s\"",
                       (e - s), s);
    return CVAL_TYPE_INVALID;
  }
}

static int parse_cb_signature(struct mjs *mjs, const char *s, const char *e,
                              ffi_sig_t *sig) {
  int ret = 1;
  int vtidx = 0;
  const char *cur = s;
  cval_type_t val_type = CVAL_TYPE_INVALID;
  const char *tmp_e = NULL;

  mjs_ffi_sig_init(sig);

  /* Parse return value type */
  tmp_e = strchr(cur, '(');
  if (tmp_e == NULL) {
    ret = 0;
    goto clean;
  }
  val_type = parse_cval_type(mjs, cur, tmp_e);
  if (val_type == CVAL_TYPE_INVALID) {
    ret = 0;
    goto clean;
  }
  mjs_ffi_sig_set_val_type(sig, vtidx++, val_type);

  /* Advance cur to the beginning of the arg list */
  tmp_e = strchr(tmp_e, ')');
  if (tmp_e == NULL) {
    ret = 0;
    goto clean;
  }
  tmp_e = strchr(tmp_e, '(');
  if (tmp_e == NULL) {
    ret = 0;
    goto clean;
  }
  cur = tmp_e + 1;

  /* Parse all args */
  while (*tmp_e && *tmp_e != ')') {
    tmp_e = cur;

    /* Advance tmp_e until the next arg separator */
    while (*tmp_e && *tmp_e != ',' && *tmp_e != ')') tmp_e++;

    /* Parse current arg */
    val_type = parse_cval_type(mjs, cur, tmp_e);
    if (val_type == CVAL_TYPE_INVALID) {
      /* parse_cval_type() has already set error message */
      ret = 0;
      goto clean;
    }
    if (!mjs_ffi_sig_set_val_type(sig, vtidx++, val_type)) {
      mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "too many callback args");
      ret = 0;
      goto clean;
    }

    if (*tmp_e == ',') {
      /* Advance cur to the next argument */
      cur = tmp_e + 1;
      while (*cur == ' ') cur++;
    } else {
      /* No more arguments */
      break;
    }
  }

  sig->stat = mjs_ffi_sig_stat_get(mjs, sig);
  if (!sig->stat.is_valid) {
    ret = 0;
    goto clean;
  }

clean:
  if (!ret) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "bad callback signature: \"%.*s\"",
                       e - s, s);
  }
  return ret;
}

/* C callbacks implementation {{{ */

/* An argument or a return value for C callback impl */
union ffi_cb_data_val {
  void *p;
  uintptr_t w;
  double d;
};

struct ffi_cb_data {
  union ffi_cb_data_val args[MJS_CB_ARGS_MAX_CNT];
};

static union ffi_cb_data_val ffi_cb_impl_generic(void *param,
                                                 struct ffi_cb_data *data) {
  struct ffi_cb_args *cbargs = (struct ffi_cb_args *) param;
  mjs_val_t res = MJS_UNDEFINED;
  union ffi_cb_data_val ret;
  int i;
  memset(&ret, 0, sizeof(ret));
  mjs_own(cbargs->mjs, &res);

  /* There must be at least one argument: a userdata */
  assert(cbargs->sig.stat.args_cnt > 0);

  /* Create JS arguments */
  mjs_val_t *args = calloc(1, sizeof(mjs_val_t) * cbargs->sig.stat.args_cnt);
  for (i = 0; i < cbargs->sig.stat.args_cnt; i++) {
    cval_type_t val_type =
        cbargs->sig.val_types[i + 1 /* first val_type is return value type */];
    switch (val_type) {
      case CVAL_TYPE_USERDATA:
        args[i] = cbargs->userdata;
        break;
      case CVAL_TYPE_INT:
        args[i] = mjs_mk_number(cbargs->mjs, data->args[i].w);
        break;
      case CVAL_TYPE_CHAR_PTR: {
        const char *s = (char *) data->args[i].w;
        if (s == NULL) s = "";
        args[i] = mjs_mk_string(cbargs->mjs, s, ~0, 1);
        break;
      }
      case CVAL_TYPE_VOID_PTR:
        args[i] = mjs_mk_foreign(cbargs->mjs, (void *) data->args[i].w);
        break;
      case CVAL_TYPE_DOUBLE:
        args[i] = mjs_mk_number(cbargs->mjs, data->args[i].d);
        break;
      default:
        /* should never be here */
        LOG(LL_ERROR, ("unexpected val type for arg #%d: %d\n", i, val_type));
        abort();
    }
  }

  /* Call JS function */
  LOG(LL_VERBOSE_DEBUG, ("calling JS callback void-void %d from C",
                         mjs_get_int(cbargs->mjs, cbargs->func)));
  mjs_err_t err = mjs_apply(cbargs->mjs, &res, cbargs->func, MJS_UNDEFINED,
                            cbargs->sig.stat.args_cnt, args);
  if (err != MJS_OK) {
    /*
     * There's not much we can do about the error here; let's at least print it
     */
    fprintf(stderr, "MJS callback error: %s\n", mjs_strerror(cbargs->mjs, err));

    goto clean;
  }

  /* Get return value, if needed */
  switch (cbargs->sig.val_types[0]) {
    case CVAL_TYPE_NONE:
      /* do nothing */
      break;
    case CVAL_TYPE_INT:
      ret.w = mjs_get_int(cbargs->mjs, res);
      break;
    case CVAL_TYPE_VOID_PTR:
      ret.p = mjs_get_ptr(cbargs->mjs, res);
      break;
    case CVAL_TYPE_DOUBLE:
      ret.d = mjs_get_double(cbargs->mjs, res);
      break;
    default:
      /* should never be here */
      LOG(LL_ERROR,
          ("unexpected return val type %d\n", cbargs->sig.val_types[0]));
      abort();
  }

clean:
  free(args);
  mjs_disown(cbargs->mjs, &res);
  return ret;
}

static void ffi_init_cb_data_wwww(struct ffi_cb_data *data, uintptr_t w0,
                                  uintptr_t w1, uintptr_t w2, uintptr_t w3,
                                  uintptr_t w4, uintptr_t w5) {
  memset(data, 0, sizeof(*data));
  data->args[0].w = w0;
  data->args[1].w = w1;
  data->args[2].w = w2;
  data->args[3].w = w3;
  data->args[4].w = w4;
  data->args[5].w = w5;
}

static uintptr_t ffi_cb_impl_wpwwwww(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w0, &data).w;
}

static uintptr_t ffi_cb_impl_wwpwwww(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w1, &data).w;
}

static uintptr_t ffi_cb_impl_wwwpwww(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w2, &data).w;
}

static uintptr_t ffi_cb_impl_wwwwpww(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w3, &data).w;
}

static uintptr_t ffi_cb_impl_wwwwwpw(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w4, &data).w;
}

static uintptr_t ffi_cb_impl_wwwwwwp(uintptr_t w0, uintptr_t w1, uintptr_t w2,
                                     uintptr_t w3, uintptr_t w4, uintptr_t w5) {
  struct ffi_cb_data data;
  ffi_init_cb_data_wwww(&data, w0, w1, w2, w3, w4, w5);
  return ffi_cb_impl_generic((void *) w5, &data).w;
}
/* }}} */

static struct ffi_cb_args **ffi_get_matching(struct ffi_cb_args **plist,
                                             mjs_val_t func,
                                             mjs_val_t userdata) {
  for (; *plist != NULL; plist = &((*plist)->next)) {
    if ((*plist)->func == func && (*plist)->userdata == userdata) {
      break;
    }
  }
  return plist;
}

static cb_fn_t *get_cb_impl_by_signature(const ffi_sig_t *sig) {
  if (sig->stat.is_valid) {
    if (sig->stat.args_cnt <= MJS_CB_ARGS_MAX_CNT) {
      if (mjs_ffi_is_regular_word_or_void(sig->val_types[0])) {
        /* Return type is a word or void */
        if (sig->stat.args_double_cnt == 0) {
          /* No double arguments */
          switch (sig->stat.userdata_idx) {
            case 1:
              return (cb_fn_t *) ffi_cb_impl_wpwwwww;
            case 2:
              return (cb_fn_t *) ffi_cb_impl_wwpwwww;
            case 3:
              return (cb_fn_t *) ffi_cb_impl_wwwpwww;
            case 4:
              return (cb_fn_t *) ffi_cb_impl_wwwwpww;
            case 5:
              return (cb_fn_t *) ffi_cb_impl_wwwwwpw;
            case 6:
              return (cb_fn_t *) ffi_cb_impl_wwwwwwp;
            default:
              /* should never be here */
              abort();
          }
        }
      }
    } else {
      /* Too many arguments for the built-in callback impls */
      /* TODO(dfrank): add support for custom app-dependent resolver */
    }
  }

  return NULL;
}

MJS_PRIVATE mjs_err_t mjs_ffi_call(struct mjs *mjs) {
  mjs_return(mjs, mjs_arg(mjs, 0));
  return MJS_OK;
}

MJS_PRIVATE mjs_err_t mjs_ffi_call2(struct mjs *mjs) {
  mjs_err_t ret = MJS_OK;
  mjs_val_t sig = *vptr(&mjs->stack, mjs_getretvalpos(mjs));
  const char *s = mjs_get_cstring(mjs, &sig);
  const char *n, *e, *a = NULL;
  ffi_fn_t fn;
  int i, nargs;
  struct ffi_arg res;
  struct ffi_arg args[FFI_MAX_ARGS_CNT];
  struct cbdata cbdata;
  cval_type_t rtype;

  /* TODO(dfrank): support multiple callbacks */
  mjs_val_t resv = mjs_mk_undefined();
  mjs_val_t argvs[FFI_MAX_ARGS_CNT];

  memset(&cbdata, 0, sizeof(cbdata));
  cbdata.func_idx = -1;
  cbdata.userdata_idx = -1;

  for (n = s; *n && *n >= 'a' && *n <= 'z';) n++; /* Skip type name */
  while (*n == ' ' || *n == '*') n++;             /* Skip to function name */
  for (e = n; *e && *e != '(';) e++;              /* Skip function name */
  if (*e == '(') a = e + 1;

  rtype = parse_cval_type(mjs, s, n);
  if (rtype == CVAL_TYPE_INVALID) {
    ret = MJS_TYPE_ERROR;
    mjs_prepend_errorf(mjs, ret, "wrong ffi return type");
    goto clean;
  }

  res.size = rtype == CVAL_TYPE_DOUBLE ? 8 : 4;
  res.is_float = rtype == CVAL_TYPE_DOUBLE;
  res.v.i = 0;

  nargs =
      mjs_stack_size(&mjs->stack) - mjs_get_int(mjs, vtop(&mjs->call_stack));
  for (i = 0; i < nargs; i++) {
    const char *ae; /* pointer to the one-past-end character */
    int level = 0;  /* nested parens level */
    int is_fp = 0;  /* set to 1 is current arg is a callback function ptr */
    mjs_val_t arg = mjs_arg(mjs, i);
    if (a == NULL) {
      ret = MJS_TYPE_ERROR;
      mjs_prepend_errorf(mjs, ret, "got %d actuals", nargs);
      goto clean;
    }
    while (*a == ' ') a++;
    ae = a;
    while (*ae && (level > 0 || (*ae != ',' && *ae != ')'))) {
      switch (*ae) {
        case '(':
          level++;
          /*
           * only function pointer params can have parens, so, set the flag
           * that it's going to be a function pointer
           */
          is_fp = 1;
          break;
        case ')':
          level--;
          break;
      }
      ae++;
    }

    if (is_fp) {
      /*
       * Current argument is a callback function pointer: remember the given JS
       * function and the argument index
       */
      cbdata.func = arg;
      cbdata.func_idx = i;
      cbdata.signature = a;
      cbdata.signature_len = (size_t)(ae - a);
      if (!parse_cb_signature(mjs, a, ae, &cbdata.sig)) {
        ret = MJS_TYPE_ERROR;
        goto clean;
      }
    } else {
      /* Some non-function argument */
      cval_type_t ctype = parse_cval_type(mjs, a, ae);
      switch (ctype) {
        case CVAL_TYPE_NONE:
          /*
           * Void argument: in any case, it's an error, because if C function
           * takes no arguments, then the FFI-ed JS function should be called
           * without any arguments, and thus we'll not face "void" here.
           */
          ret = MJS_TYPE_ERROR;
          if (i == 0) {
            /* FFI signature is correct, but invocation is wrong */
            mjs_prepend_errorf(mjs, ret, "ffi-ed function takes no arguments");
          } else {
            /*
             * FFI signature is wrong: we can't have "void" as a non-first
             * "argument"
             */
            mjs_prepend_errorf(mjs, ret, "bad ffi arg #%d type: \"void\"", i);
          }

          goto clean;
        case CVAL_TYPE_USERDATA:
          /* Userdata for the callback */
          if (cbdata.userdata_idx != -1) {
            ret = MJS_TYPE_ERROR;
            mjs_prepend_errorf(mjs, ret,
                               "two or more userdata args: #%d and %d",
                               cbdata.userdata_idx, i);

            goto clean;
          }
          cbdata.userdata = arg;
          cbdata.userdata_idx = i;
          break;
        case CVAL_TYPE_INT:
          ffi_set_int32(&args[i], mjs_get_int(mjs, arg));
          break;
        case CVAL_TYPE_DOUBLE:
          ffi_set_double(&args[i], mjs_get_double(mjs, arg));
          break;
        case CVAL_TYPE_CHAR_PTR: {
          size_t s;
          if (!mjs_is_string(arg)) {
            ret = MJS_TYPE_ERROR;
            mjs_prepend_errorf(
                mjs, ret,
                "actual arg #%d is not a string (the type idx is: %s)", i,
                mjs_typeof(arg));
            goto clean;
          }
          argvs[i] = arg;
          ffi_set_ptr(&args[i], (void *) mjs_get_string(mjs, &argvs[i], &s));
        } break;
        case CVAL_TYPE_VOID_PTR:
          if (!mjs_is_foreign(arg) && !mjs_is_string(arg)) {
            ret = MJS_TYPE_ERROR;
            mjs_prepend_errorf(mjs, ret, "actual arg #%d is not a ptr", i);
            goto clean;
          }
          if (mjs_is_string(arg)) {
            size_t n;
            ffi_set_ptr(&args[i], (void *) mjs_get_string(mjs, &arg, &n));
          } else {
            ffi_set_ptr(&args[i], (void *) mjs_get_ptr(mjs, arg));
          }
          break;
        case CVAL_TYPE_INVALID:
          /* parse_cval_type() has already set a more detailed error */
          ret = MJS_TYPE_ERROR;
          mjs_prepend_errorf(mjs, ret, "wrong arg type");
          goto clean;
        default:
          abort();
          break;
      }
    }

    a = ae + 1;
    if (*a == '\0') a = NULL;
  }

  if (mjs->dlsym == NULL) {
    ret = MJS_TYPE_ERROR;
    mjs_prepend_errorf(mjs, ret,
                       "resolver is not set, call mjs_set_ffi_resolver");
    goto clean;
  }

  {
    char buf[100];
    snprintf(buf, sizeof(buf), "%.*s", (int) (e - n), n);
    fn = (ffi_fn_t) mjs->dlsym(RTLD_DEFAULT, buf);
    if (fn == NULL) {
      ret = MJS_TYPE_ERROR;
      mjs_prepend_errorf(mjs, ret, "dlsym('%s') failed", buf);
      goto clean;
    }
  }

  if (cbdata.userdata_idx >= 0 && cbdata.func_idx >= 0) {
    struct ffi_cb_args *cbargs = NULL;
    struct ffi_cb_args **pitem = NULL;

    /* the function takes a callback */

    /* Get C callback implementation by the given signature */
    cb_fn_t *cb_fn = get_cb_impl_by_signature(&cbdata.sig);
    if (cb_fn == NULL) {
      ret = MJS_TYPE_ERROR;
      mjs_prepend_errorf(mjs, ret,
                         "the callback signature '%.*s' is valid, but there's "
                         "no existing callback implementation for it",
                         cbdata.signature_len, cbdata.signature);
      goto clean;
    }

    /*
     * Get cbargs: either reuse the existing one (if the matching item exists),
     * or create a new one.
     */
    pitem = ffi_get_matching(&mjs->ffi_cb_args, cbdata.func, cbdata.userdata);
    if (*pitem == NULL) {
      /* No matching cbargs item; we need to add a new one */
      cbargs = calloc(1, sizeof(*cbargs));
      cbargs->mjs = mjs;
      cbargs->func = cbdata.func;
      cbargs->userdata = cbdata.userdata;
      memcpy(&cbargs->sig, &cbdata.sig, sizeof(cbargs->sig));

      /* Establish a link to the newly allocated item */
      *pitem = cbargs;
    } else {
      /* Found matching item: reuse it */
      cbargs = *pitem;
    }

    ffi_set_ptr(&args[cbdata.func_idx], cb_fn);
    ffi_set_ptr(&args[cbdata.userdata_idx], cbargs);
  } else if (!(cbdata.userdata_idx == -1 && cbdata.func_idx == -1)) {
    /*
     * incomplete signature: it contains either the function pointer or
     * userdata. It should contain both or none.
     */
    ret = MJS_TYPE_ERROR;
    mjs_prepend_errorf(mjs, ret, "need both function and userdata");
    goto clean;
  }

  ffi_call(fn, nargs, &res, args);

  switch (rtype) {
    case CVAL_TYPE_CHAR_PTR: {
      const char *s = (const char *) (uintptr_t) res.v.i;
      resv = mjs_mk_string(mjs, s, ~0, 1);
      break;
    }
    case CVAL_TYPE_VOID_PTR:
      resv = mjs_mk_foreign(mjs, (void *) (uintptr_t) res.v.i);
      break;
    case CVAL_TYPE_INT:
      resv = mjs_mk_number(mjs, (int) res.v.i);
      break;
    case CVAL_TYPE_DOUBLE:
      resv = mjs_mk_number(mjs, res.v.d);
      break;
    default:
      resv = mjs_mk_undefined();
      break;
  }
clean:
  /*
   * If there was some error, prepend an error message with the subject
   * signature
   */
  if (ret != MJS_OK) {
    mjs_prepend_errorf(mjs, ret, "failed to call FFI signature \"%s\"", s);
  }
  mjs_return(mjs, resv);
  return ret;
}

/*
 * TODO(dfrank): make it return boolean (when booleans are supported), instead
 * of a number
 */
MJS_PRIVATE void mjs_ffi_cb_free(struct mjs *mjs) {
  mjs_val_t ret = mjs_mk_number(mjs, 0);
  mjs_val_t func = mjs_arg(mjs, 0);
  mjs_val_t userdata = mjs_arg(mjs, 1);

  if (mjs_is_function(func)) {
    struct ffi_cb_args **pitem =
        ffi_get_matching(&mjs->ffi_cb_args, func, userdata);
    if (*pitem != NULL) {
      /* Found matching item: remove it from the linked list, and free */
      struct ffi_cb_args *cbargs = *pitem;
      *pitem = cbargs->next;
      free(cbargs);
      ret = mjs_mk_number(mjs, 1);
    }
  } else {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "missing argument 'func'");
  }

  mjs_return(mjs, ret);
}

void mjs_ffi_args_free_list(struct mjs *mjs) {
  ffi_cb_args_t *next = mjs->ffi_cb_args;

  while (next != NULL) {
    ffi_cb_args_t *cur = next;
    next = next->next;
    free(cur);
  }
}

MJS_PRIVATE void mjs_ffi_sig_init(ffi_sig_t *sig) {
  memset(sig->val_types, CVAL_TYPE_NONE, MJS_CB_SIGNATURE_MAX_SIZE);
}

MJS_PRIVATE int mjs_ffi_sig_set_val_type(ffi_sig_t *sig, int idx,
                                         cval_type_t type) {
  if (idx < MJS_CB_SIGNATURE_MAX_SIZE) {
    sig->val_types[idx] = type;
    return 1;
  } else {
    /* Index is too large */
    return 0;
  }
}

MJS_PRIVATE struct ffi_sig_stat mjs_ffi_sig_stat_get(struct mjs *mjs,
                                                     const ffi_sig_t *sig) {
  struct ffi_sig_stat ret;
  int i;

  memset(&ret, 0, sizeof(ret));
  ret.is_valid = 1;

  /* Make sure return type is fine */
  if (sig->val_types[0] != CVAL_TYPE_NONE &&
      sig->val_types[0] != CVAL_TYPE_INT &&
      sig->val_types[0] != CVAL_TYPE_DOUBLE) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "wrong return value type");
    ret.is_valid = 0;
    goto clean;
  }

  /* Handle argument types */
  for (i = 1; i < MJS_CB_SIGNATURE_MAX_SIZE; i++) {
    cval_type_t type = sig->val_types[i];
    switch (type) {
      case CVAL_TYPE_USERDATA:
        if (ret.userdata_idx != 0) {
          /* There must be exactly one userdata arg, but we have more */
          mjs_prepend_errorf(mjs, MJS_TYPE_ERROR,
                             "more than one userdata arg: #%d and #%d",
                             (ret.userdata_idx - 1), (i - 1));
          ret.is_valid = 0;
          goto clean;
        }
        ret.userdata_idx = i;
        break;
      case CVAL_TYPE_INT:
      case CVAL_TYPE_VOID_PTR:
      case CVAL_TYPE_CHAR_PTR:
        /* Do nothing */
        break;
      case CVAL_TYPE_DOUBLE:
        ret.args_double_cnt++;
        break;
      case CVAL_TYPE_NONE:
        /* No more arguments */
        goto args_over;
      default:
        ret.is_valid = 0;
        goto clean;
    }

    ret.args_cnt++;
  }
args_over:

  if (ret.userdata_idx == 0) {
    /* No userdata arg */
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "no userdata arg");
    ret.is_valid = 0;
    goto clean;
  }

clean:
  return ret;
}

MJS_PRIVATE int mjs_ffi_is_regular_word(cval_type_t type) {
  switch (type) {
    case CVAL_TYPE_INT:
      return 1;
    default:
      return 0;
  }
}

MJS_PRIVATE int mjs_ffi_is_regular_word_or_void(cval_type_t type) {
  return (type == CVAL_TYPE_NONE || mjs_ffi_is_regular_word(type));
}

#ifdef _WIN32
void *dlsym(void *handle, const char *name) {
  return GetProcAddress(GetModuleHandle(NULL), name);
}
#elif !defined(__unix__) && !defined(__APPLE__)
void *dlsym(void *handle, const char *name) {
  (void) handle;
  (void) name;
  return NULL;
}
#endif
