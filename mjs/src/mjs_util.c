/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#include "common/cs_varint.h"

#include "mjs/src/mjs_array.h"
#include "mjs/src/mjs_bcode.h"
#include "mjs/src/mjs_core.h"
#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_object.h"
#include "mjs/src/mjs_primitive.h"
#include "mjs/src/mjs_string.h"
#include "mjs/src/mjs_util.h"
#include "mjs/src/mjs_tok.h"

const char *mjs_typeof(mjs_val_t v) {
  return mjs_stringify_type(mjs_get_type(v));
}

MJS_PRIVATE const char *mjs_stringify_type(enum mjs_type t) {
  switch (t) {
    case MJS_TYPE_NUMBER:
      return "number";
    case MJS_TYPE_BOOLEAN:
      return "boolean";
    case MJS_TYPE_STRING:
      return "string";
    case MJS_TYPE_OBJECT_ARRAY:
      return "array";
    case MJS_TYPE_OBJECT_GENERIC:
      return "object";
    case MJS_TYPE_FOREIGN:
      return "foreign_ptr";
    case MJS_TYPE_OBJECT_FUNCTION:
      return "function";
    case MJS_TYPE_NULL:
      return "null";
    case MJS_TYPE_UNDEFINED:
      return "undefined";
    default:
      return "???";
  }
}

void mjs_fprintf(mjs_val_t v, struct mjs *mjs, FILE *fp) {
  if (mjs_is_number(v)) {
    double iv, d = mjs_get_double(mjs, v);
    if (modf(d, &iv) == 0) {
      fprintf(fp, "%" INT64_FMT, (int64_t) d);
    } else {
      fprintf(fp, "%lg", mjs_get_double(mjs, v));
    }
  } else if (mjs_is_boolean(v)) {
    fprintf(fp, "%s", mjs_get_bool(mjs, v) ? "true" : "false");
  } else if (mjs_is_string(v)) {
    size_t size;
    const char *s = mjs_get_string(mjs, &v, &size);
    printf("%.*s", (int) size, s);
  } else if (mjs_is_array(v)) {
    fprintf(fp, "<array>");
  } else if (mjs_is_object(v)) {
    fprintf(fp, "<object>");
  } else if (mjs_is_foreign(v)) {
    fprintf(fp, "<foreign_ptr@%lx>", (unsigned long) mjs_get_ptr(mjs, v));
  } else if (mjs_is_function(v)) {
    fprintf(fp, "<function@%d>", (int) mjs_get_func_addr(v));
  } else if (mjs_is_null(v)) {
    fprintf(fp, "null");
  } else if (mjs_is_undefined(v)) {
    fprintf(fp, "undefined");
  } else {
    fprintf(fp, "(unknown value type %" INT64_FMT ") ", (int64_t) v);
  }
}

#if MJS_ENABLE_DEBUG

MJS_PRIVATE const char *opcodetostr(uint8_t opcode) {
  static const char *names[] = {
      "NOP",        "DROP",        "DUP",        "SWAP",       "JMP",
      "JMP_TRUE",   "JMP_FALSE",   "FIND_SCOPE", "PUSH_SCOPE", "PUSH_STR",
      "PUSH_TRUE",  "PUSH_FALSE",  "PUSH_INT",   "PUSH_DBL",   "PUSH_NULL",
      "PUSH_UNDEF", "PUSH_OBJ",    "PUSH_ARRAY", "PUSH_FUNC",  "PUSH_THIS",
      "GET",        "CREATE",      "EXPR",       "APPEND",     "SET_ARG",
      "NEW_SCOPE",  "DEL_SCOPE",   "CALL",       "RETURN",     "LOOP",
      "BREAK",      "CONTINUE",    "SETRETVAL",  "EXIT",       "BCODE_HDR",
      "ARGS",       "FOR_IN_NEXT",
  };
  const char *name = "UNKNOWN OPCODE";
  assert(ARRAY_SIZE(names) == OP_MAX);
  if (opcode < ARRAY_SIZE(names)) name = names[opcode];
  return name;
}

MJS_PRIVATE size_t mjs_disasm_single(const uint8_t *code, size_t i, FILE *fp) {
  size_t start_i = i;
  fprintf(fp, "\t%-3u %-8s", (unsigned) i, opcodetostr(code[i]));

  switch (code[i]) {
    case OP_PUSH_FUNC: {
      int llen, n = cs_varint_decode(&code[i + 1], &llen);
      fprintf(fp, " %04u", (unsigned) (i - n));
      i += llen;
      break;
    }
    case OP_PUSH_INT: {
      int llen;
      unsigned long n = cs_varint_decode(&code[i + 1], &llen);
      fprintf(fp, "\t%lu", n);
      i += llen;
      break;
    }
    case OP_SET_ARG: {
      int llen1, llen2, n, arg_no = cs_varint_decode(&code[i + 1], &llen1);
      n = cs_varint_decode(&code[i + llen1 + 1], &llen2);
      fprintf(fp, "\t[%.*s] %d", n, code + i + 1 + llen1 + llen2, arg_no);
      i += llen1 + llen2 + n;
      break;
    }
    case OP_PUSH_STR:
    case OP_PUSH_DBL: {
      int llen, n = cs_varint_decode(&code[i + 1], &llen);
      fprintf(fp, "\t[%.*s]", n, code + i + 1 + llen);
      i += llen + n;
      break;
    }
    case OP_JMP:
    case OP_JMP_TRUE:
    case OP_JMP_FALSE: {
      int llen, n = cs_varint_decode(&code[i + 1], &llen);
      fprintf(fp, "\t%u",
              (unsigned) i + n + llen +
                  1 /* becaue i will be incremented on the usual terms */);
      i += llen;
      break;
    }
    case OP_LOOP: {
      int l1, l2, n2, n1 = cs_varint_decode(&code[i + 1], &l1);
      n2 = cs_varint_decode(&code[i + l1 + 1], &l2);
      fprintf(fp, "\tB:%lu C:%lu (%d)",
              (unsigned long) i + 1 /* OP_LOOP */ + l1 + n1,
              (unsigned long) i + 1 /* OP_LOOP */ + l1 + l2 + n2, (int) i);
      i += l1 + l2;
      break;
    }
    case OP_EXPR: {
      int op = code[i + 1];
      const char *name = "???";
      /* clang-format off */
      switch (op) {
        case TOK_DOT:       name = "."; break;
        case TOK_MINUS:     name = "-"; break;
        case TOK_PLUS:      name = "+"; break;
        case TOK_MUL:       name = "*"; break;
        case TOK_DIV:       name = "/"; break;
        case TOK_REM:       name = "%"; break;
        case TOK_XOR:       name = "^"; break;
        case TOK_AND:       name = "&"; break;
        case TOK_OR:        name = "|"; break;
        case TOK_LSHIFT:    name = "<<"; break;
        case TOK_RSHIFT:    name = ">>"; break;
        case TOK_URSHIFT:   name = ">>>"; break;
        case TOK_UNARY_MINUS:   name = "- (unary)"; break;
        case TOK_UNARY_PLUS:    name = "+ (unary)"; break;
        case TOK_NOT:       name = "!"; break;
        case TOK_TILDA:     name = "~"; break;
        case TOK_EQ:        name = "=="; break;
        case TOK_NE:        name = "!="; break;
        case TOK_EQ_EQ:     name = "==="; break;
        case TOK_NE_NE:     name = "!=="; break;
        case TOK_LT:        name = "<"; break;
        case TOK_GT:        name = ">"; break;
        case TOK_LE:        name = "<="; break;
        case TOK_GE:        name = ">="; break;
        case TOK_ASSIGN:    name = "="; break;
        case TOK_POSTFIX_PLUS:  name = "++ (postfix)"; break;
        case TOK_POSTFIX_MINUS: name = "-- (postfix)"; break;
        case TOK_MINUS_MINUS:   name = "--"; break;
        case TOK_PLUS_PLUS:     name = "++"; break;
        case TOK_LOGICAL_AND:   name = "&&"; break;
        case TOK_LOGICAL_OR:    name = "||"; break;
        case TOK_KEYWORD_TYPEOF:  name = "typeof"; break;
        case TOK_PLUS_ASSIGN:     name = "+="; break;
        case TOK_MINUS_ASSIGN:    name = "-="; break;
        case TOK_MUL_ASSIGN:      name = "*="; break;
        case TOK_DIV_ASSIGN:      name = "/="; break;
        case TOK_REM_ASSIGN:      name = "%="; break;
        case TOK_XOR_ASSIGN:      name = "^="; break;
        case TOK_AND_ASSIGN:      name = "&="; break;
        case TOK_OR_ASSIGN:       name = "|="; break;
        case TOK_LSHIFT_ASSIGN:   name = "<<="; break;
        case TOK_RSHIFT_ASSIGN:   name = ">>="; break;
        case TOK_URSHIFT_ASSIGN:  name = ">>>="; break;
      }
      /* clang-format on */
      fprintf(fp, "\t%s", name);
      i++;
      break;
    }
    case OP_BCODE_HEADER: {
      size_t start = 0;
      mjs_header_item_t map_offset = 0, total_size = 0;
      start = i;
      memcpy(&total_size, &code[i + 1], sizeof(total_size));
      memcpy(&map_offset,
             &code[i + 1 + MJS_HDR_ITEM_MAP_OFFSET * sizeof(total_size)],
             sizeof(map_offset));
      i += sizeof(mjs_header_item_t) * MJS_HDR_ITEMS_CNT;
      fprintf(fp, "\t[%s] end:%lu map_offset: %lu", &code[i + 1],
              (unsigned long) start + total_size,
              (unsigned long) start + map_offset);
      i += strlen((char *) (code + i + 1)) + 1;
      break;
    }
  }

  fputc('\n', fp);
  return i - start_i;
}

void mjs_disasm(const uint8_t *code, size_t len, FILE *fp) {
  size_t i, start = 0;
  mjs_header_item_t map_offset = 0, total_size = 0;

  for (i = 0; i < len; i++) {
    size_t delta = mjs_disasm_single(code, i, fp);
    if (code[i] == OP_BCODE_HEADER) {
      start = i;
      memcpy(&total_size, &code[i + 1], sizeof(total_size));
      memcpy(&map_offset,
             &code[i + 1 + MJS_HDR_ITEM_MAP_OFFSET * sizeof(total_size)],
             sizeof(map_offset));
    }

    i += delta;

    if (map_offset > 0 && i == start + map_offset) {
      i = start + total_size - 1;
      continue;
    }
  }
}

static void mjs_dump_obj_stack(const char *name, const struct mbuf *m,
                               struct mjs *mjs, FILE *fp) {
  size_t i, n;
  n = mjs_stack_size(m);
  fprintf(fp, "  %12s (%d elems): ", name, (int) n);
  for (i = 0; i < n; i++) {
    fprintf(fp, " [");
    mjs_fprintf(((mjs_val_t *) m->buf)[i], mjs, fp);
    fprintf(fp, "]");
  }
  fprintf(fp, "\n");
}

void mjs_dump(struct mjs *mjs, int do_disasm, FILE *fp) {
  fprintf(fp, "------- MJS VM DUMP BEGIN\n");
  mjs_dump_obj_stack("DATA_STACK", &mjs->stack, mjs, fp);
  mjs_dump_obj_stack("CALL_STACK", &mjs->call_stack, mjs, fp);
  mjs_dump_obj_stack("SCOPES", &mjs->scopes, mjs, fp);
  mjs_dump_obj_stack("LOOP_OFFSETS", &mjs->loop_addresses, mjs, fp);
  if (do_disasm) {
    fprintf(fp, "  CODE:\n");
    mjs_disasm((uint8_t *) mjs->bcode.buf, mjs->bcode.len, fp);
  }
  fprintf(fp, "------- MJS VM DUMP END\n");
}

MJS_PRIVATE int mjs_check_arg(struct mjs *mjs, int arg_num,
                              const char *arg_name, enum mjs_type expected_type,
                              mjs_val_t *parg) {
  mjs_val_t arg = MJS_UNDEFINED;

  if (arg_num >= 0) {
    int nargs = mjs_nargs(mjs);
    if (nargs < arg_num + 1) {
      mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "missing argument %s", arg_name);
      return 0;
    }

    arg = mjs_arg(mjs, arg_num);
  } else {
    /* use `this` */
    arg = mjs->vals.this_obj;
  }

  enum mjs_type actual_type = mjs_get_type(arg);
  if (actual_type != expected_type) {
    mjs_prepend_errorf(mjs, MJS_TYPE_ERROR, "%s should be a %s, %s given",
                       arg_name, mjs_stringify_type(expected_type),
                       mjs_stringify_type(actual_type));
    return 0;
  }

  if (parg != NULL) {
    *parg = arg;
  }

  return 1;
}

MJS_PRIVATE int mjs_normalize_idx(int idx, int size) {
  if (idx < 0) {
    idx = size + idx;
    if (idx < 0) {
      idx = 0;
    }
  }
  if (idx > size) {
    idx = size;
  }
  return idx;
}

#endif
