/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#include "mjs/src/mjs_core.h"
#include "common/str_util.h"
#include "mjs/src/mjs_bcode.h"
#include "mjs/src/mjs_builtin.h"
#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_license.h"
#include "mjs/src/mjs_object.h"
#include "mjs/src/mjs_primitive.h"
#include "mjs/src/mjs_varint.h"

#ifndef MJS_DEFAULT_OBJECT_ARENA_SIZE
#define MJS_DEFAULT_OBJECT_ARENA_SIZE 20
#endif
#ifndef MJS_DEFAULT_PROPERTY_ARENA_SIZE
#define MJS_DEFAULT_PROPERTY_ARENA_SIZE 20
#endif

void mjs_destroy(struct mjs *mjs) {
  mbuf_free(&mjs->bcode);
  mbuf_free(&mjs->stack);
  mbuf_free(&mjs->call_stack);
  mbuf_free(&mjs->owned_strings);
  mbuf_free(&mjs->foreign_strings);
  mbuf_free(&mjs->owned_values);
  mbuf_free(&mjs->scopes);
  mbuf_free(&mjs->loop_addresses);
  mbuf_free(&mjs->json_visited_stack);
  free(mjs->error_msg);
  mjs_ffi_args_free_list(mjs);
  gc_arena_destroy(mjs, &mjs->object_arena);
  gc_arena_destroy(mjs, &mjs->property_arena);
  free(mjs);
}

struct mjs *mjs_create(void) {
  struct mjs *mjs = calloc(1, sizeof(*mjs));
  mbuf_init(&mjs->stack, 0);
  mbuf_init(&mjs->call_stack, 0);
  mbuf_init(&mjs->owned_strings, 0);
  mbuf_init(&mjs->foreign_strings, 0);
  mbuf_init(&mjs->bcode, 0);
  mbuf_init(&mjs->owned_values, 0);
  mbuf_init(&mjs->scopes, 0);
  mbuf_init(&mjs->loop_addresses, 0);
  mbuf_init(&mjs->json_visited_stack, 0);

  /*
   * The compacting GC exploits the null terminator of the previous string as a
   * marker.
   */
  {
    char z = 0;
    mbuf_append(&mjs->owned_strings, &z, 1);
  }

  gc_arena_init(&mjs->object_arena, sizeof(struct mjs_object),
                MJS_DEFAULT_OBJECT_ARENA_SIZE, 10);
  gc_arena_init(&mjs->property_arena, sizeof(struct mjs_property),
                MJS_DEFAULT_PROPERTY_ARENA_SIZE, 10);

  mjs_val_t global_object = mjs_mk_object(mjs);
  mjs_init_builtin(mjs, global_object);
  mjs_set_ffi_resolver(mjs, dlsym);
  push_mjs_val(&mjs->scopes, global_object);
  mjs->vals.this_obj = MJS_UNDEFINED;
  mjs->vals.dataview_proto = MJS_UNDEFINED;

  return mjs;
}

mjs_err_t mjs_set_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  free(mjs->error_msg);
  mjs->error_msg = NULL;
  mjs->error = err;
  if (fmt != NULL) {
    mg_avprintf(&mjs->error_msg, 0, fmt, ap);
  }
  va_end(ap);
  return err;
}

mjs_err_t mjs_prepend_errorf(struct mjs *mjs, mjs_err_t err, const char *fmt,
                             ...) {
  va_list ap;
  va_start(ap, fmt);
  char *old_error_msg = mjs->error_msg;
  char *new_error_msg = NULL;
  mjs->error_msg = NULL;
  /* set error if only it wasn't already set to some error */
  if (mjs->error == MJS_OK) {
    mjs->error = err;
  }
  mg_avprintf(&new_error_msg, 0, fmt, ap);
  va_end(ap);

  if (old_error_msg != NULL) {
    mg_asprintf(&mjs->error_msg, 0, "%s: %s", new_error_msg, old_error_msg);
    free(new_error_msg);
    free(old_error_msg);
  } else {
    mjs->error_msg = new_error_msg;
  }
  return err;
}

const char *mjs_strerror(struct mjs *mjs, enum mjs_err err) {
  const char *err_names[] = {
      "NO_ERROR",        "SYNTAX_ERROR",    "REFERENCE_ERROR",
      "TYPE_ERROR",      "OUT_OF_MEMORY",   "INTERNAL_ERROR",
      "NOT_IMPLEMENTED", "FILE_OPEN_ERROR", "BAD_ARGUMENTS"};
  return mjs->error_msg == NULL || mjs->error_msg[0] == '\0' ? err_names[err]
                                                             : mjs->error_msg;
}

MJS_PRIVATE size_t mjs_get_func_addr(mjs_val_t v) {
  return v & ~MJS_TAG_MASK;
}

MJS_PRIVATE enum mjs_type mjs_get_type(struct mjs *mjs, mjs_val_t v) {
  int tag;
  (void) mjs;
  if (mjs_is_number(v)) {
    return MJS_TYPE_NUMBER;
  }
  tag = (v & MJS_TAG_MASK) >> 48;
  switch (tag) {
    case MJS_TAG_FOREIGN >> 48:
      return MJS_TYPE_FOREIGN;
    case MJS_TAG_UNDEFINED >> 48:
      return MJS_TYPE_UNDEFINED;
    case MJS_TAG_OBJECT >> 48:
      return MJS_TYPE_OBJECT_GENERIC;
    case MJS_TAG_ARRAY >> 48:
      return MJS_TYPE_OBJECT_ARRAY;
    case MJS_TAG_STRING_I >> 48:
    case MJS_TAG_STRING_O >> 48:
    case MJS_TAG_STRING_F >> 48:
    case MJS_TAG_STRING_D >> 48:
    case MJS_TAG_STRING_5 >> 48:
      return MJS_TYPE_STRING;
    case MJS_TAG_BOOLEAN >> 48:
      return MJS_TYPE_BOOLEAN;
    case MJS_TAG_NULL >> 48:
      return MJS_TYPE_NULL;
    default:
      abort();
      return MJS_TYPE_UNDEFINED;
  }
}

mjs_val_t mjs_get_global(struct mjs *mjs) {
  return *vptr(&mjs->scopes, 0);
}

MJS_PRIVATE int mjs_get_bcode_header_offset(struct mjs *mjs, size_t offset) {
  int32_t total_size, ret = -1, cur_idx = 0;

  while ((size_t) cur_idx < mjs->bcode.len) {
    assert(mjs->bcode.buf[cur_idx] == OP_BCODE_HEADER);
    cur_idx++;
    memcpy(&total_size, mjs->bcode.buf + cur_idx, sizeof(total_size));
    if (offset < (size_t) cur_idx + total_size) {
      ret = cur_idx;
      break;
    }
    cur_idx += total_size;
  }

  return ret;
}

MJS_PRIVATE const char *mjs_get_bcode_filename_by_offset(struct mjs *mjs,
                                                         int offset) {
  const char *ret = NULL;
  int header_idx = mjs_get_bcode_header_offset(mjs, offset);
  if (header_idx >= 0) {
    ret = mjs->bcode.buf + header_idx +
          sizeof(mjs_header_item_t) * MJS_HDR_ITEMS_CNT;
  }
  return ret;
}

MJS_PRIVATE int mjs_get_lineno_by_offset(struct mjs *mjs, int offset) {
  int ret = 1;
  int header_idx = mjs_get_bcode_header_offset(mjs, offset);
  if (header_idx >= 0) {
    mjs_header_item_t map_offset;
    memcpy(&map_offset, mjs->bcode.buf + header_idx +
                            sizeof(mjs_header_item_t) * MJS_HDR_ITEM_MAP_OFFSET,
           sizeof(map_offset));

    mjs_header_item_t bcode_offset;
    memcpy(&bcode_offset,
           mjs->bcode.buf + header_idx +
               sizeof(mjs_header_item_t) * MJS_HDR_ITEM_BCODE_OFFSET,
           sizeof(bcode_offset));

    offset -= (header_idx + bcode_offset);

    /* get pointer to the length of the map followed by the map itself */
    uint8_t *p = (uint8_t *) mjs->bcode.buf + header_idx + map_offset;

    int llen, map_len = varint_decode(p, &llen);
    p += llen;
    uint8_t *pe = p + map_len;

    int prev_line_no = 1;
    while (p < pe) {
      int llen;
      int cur_offset = varint_decode(p, &llen);
      p += llen;
      int line_no = varint_decode(p, &llen);
      p += llen;

      if (cur_offset >= offset) {
        ret = prev_line_no;
        break;
      }
      prev_line_no = line_no;
    }
  }
  return ret;
}

static void mjs_print_stack_trace_line(struct mjs *mjs, size_t offset) {
  const char *filename = mjs_get_bcode_filename_by_offset(mjs, offset);
  int line_no = mjs_get_lineno_by_offset(mjs, offset);
  if (filename == NULL) {
    fprintf(stderr, "ERROR: wrong bcode offset %d\n", (int) offset);
    filename = "<unknown-filename>";
  }
  fprintf(stderr, "  at %s:%d\n", filename, line_no);
}

MJS_PRIVATE void mjs_print_stack_trace(struct mjs *mjs, size_t offset) {
  mjs_print_stack_trace_line(mjs, offset);
  while (mjs->call_stack.len >= sizeof(mjs_val_t) * 3) {
    /* pop retval_stack_idx */
    mjs_pop_val(&mjs->call_stack);
    /* pop scope_index */
    mjs_pop_val(&mjs->call_stack);
    /* pop return_address and set current offset to it */
    offset = mjs_get_int(mjs, mjs_pop_val(&mjs->call_stack));
    mjs_print_stack_trace_line(mjs, offset);
  }
}

void mjs_own(struct mjs *mjs, mjs_val_t *v) {
  mbuf_append(&mjs->owned_values, &v, sizeof(v));
}

int mjs_disown(struct mjs *mjs, mjs_val_t *v) {
  mjs_val_t **vp = (mjs_val_t **) (mjs->owned_values.buf +
                                   mjs->owned_values.len - sizeof(v));

  for (; (char *) vp >= mjs->owned_values.buf; vp--) {
    if (*vp == v) {
      *vp = *(mjs_val_t **) (mjs->owned_values.buf + mjs->owned_values.len -
                             sizeof(v));
      mjs->owned_values.len -= sizeof(v);
      return 1;
    }
  }

  return 0;
}

/*
 * Returns position in the data stack at which the called function is located,
 * and which should be later replaced with the returned value.
 */
MJS_PRIVATE int mjs_getretvalpos(struct mjs *mjs) {
  int pos;
  mjs_val_t *ppos = vptr(&mjs->call_stack, -1);
  // LOG(LL_INFO, ("ppos: %p %d", ppos, mjs_stack_size(&mjs->call_stack)));
  assert(ppos != NULL && mjs_is_number(*ppos));
  pos = mjs_get_int(mjs, *ppos) - 1;
  assert(pos < (int) mjs_stack_size(&mjs->stack));
  return pos;
}

MJS_PRIVATE int mjs_nargs(struct mjs *mjs) {
  int top = mjs_stack_size(&mjs->stack);
  int pos = mjs_getretvalpos(mjs) + 1;
  // LOG(LL_INFO, ("top: %d pos: %d", top, pos));
  return pos > 0 && pos < top ? top - pos : 0;
}

MJS_PRIVATE mjs_val_t mjs_arg(struct mjs *mjs, int arg_index) {
  mjs_val_t res = MJS_UNDEFINED;
  int top = mjs_stack_size(&mjs->stack);
  int pos = mjs_getretvalpos(mjs) + 1;
  // LOG(LL_INFO, ("idx %d pos: %d", arg_index, pos));
  if (pos > 0 && pos + arg_index < top) {
    res = *vptr(&mjs->stack, pos + arg_index);
  }
  return res;
}

MJS_PRIVATE void mjs_return(struct mjs *mjs, mjs_val_t v) {
  int pos = mjs_getretvalpos(mjs);
  // LOG(LL_INFO, ("pos: %d", pos));
  mjs->stack.len = sizeof(mjs_val_t) * pos;
  mjs_push(mjs, v);
}

MJS_PRIVATE mjs_val_t vtop(struct mbuf *m) {
  size_t size = mjs_stack_size(m);
  return size > 0 ? *vptr(m, size - 1) : MJS_UNDEFINED;
}

MJS_PRIVATE size_t mjs_stack_size(const struct mbuf *m) {
  return m->len / sizeof(mjs_val_t);
}

MJS_PRIVATE mjs_val_t *vptr(struct mbuf *m, int idx) {
  int size = mjs_stack_size(m);
  if (idx < 0) idx = size + idx;
  return idx >= 0 && idx < size ? &((mjs_val_t *) m->buf)[idx] : NULL;
}

MJS_PRIVATE mjs_val_t mjs_pop(struct mjs *mjs) {
  if (mjs->stack.len == 0) {
    mjs_set_errorf(mjs, MJS_INTERNAL_ERROR, "stack underflow");
    return MJS_UNDEFINED;
  } else {
    return mjs_pop_val(&mjs->stack);
  }
}

MJS_PRIVATE void push_mjs_val(struct mbuf *m, mjs_val_t v) {
  mbuf_append(m, &v, sizeof(v));
}

MJS_PRIVATE mjs_val_t mjs_pop_val(struct mbuf *m) {
  mjs_val_t v = MJS_UNDEFINED;
  assert(m->len >= sizeof(v));
  if (m->len >= sizeof(v)) {
    memcpy(&v, m->buf + m->len - sizeof(v), sizeof(v));
    m->len -= sizeof(v);
  }
  return v;
}

MJS_PRIVATE void mjs_push(struct mjs *mjs, mjs_val_t v) {
  push_mjs_val(&mjs->stack, v);
}
