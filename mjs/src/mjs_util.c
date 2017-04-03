/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#include "mjs/src/mjs_array.h"
#include "mjs/src/mjs_bcode.h"
#include "mjs/src/mjs_core.h"
#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_object.h"
#include "mjs/src/mjs_primitive.h"
#include "mjs/src/mjs_string.h"
#include "mjs/src/mjs_tok.h"
#include "mjs/src/mjs_varint.h"

const char *mjs_typeof(mjs_val_t v) {
  if (mjs_is_number(v)) {
    return "number";
  } else if (mjs_is_boolean(v)) {
    return "boolean";
  } else if (mjs_is_string(v)) {
    return "string";
  } else if (mjs_is_array(v)) {
    return "array";
  } else if (mjs_is_object(v)) {
    return "object";
  } else if (mjs_is_foreign(v)) {
    return "foreign_ptr";
  } else if (mjs_is_function(v)) {
    return "function";
  } else if (mjs_is_null(v)) {
    return "null";
  } else if (mjs_is_undefined(v)) {
    return "undefined";
  } else {
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
      "NOP",       "DROP",       "DUP",        "SWAP",        "JMP",
      "JMP_BACK",  "JMP_TRUE",   "JMP_FALSE",  "FIND_SCOPE",  "PUSH_SCOPE",
      "PUSH_STR",  "PUSH_TRUE",  "PUSH_FALSE", "PUSH_INT",    "PUSH_DBL",
      "PUSH_NULL", "PUSH_UNDEF", "PUSH_OBJ",   "PUSH_ARRAY",  "PUSH_FUNC",
      "PUSH_THIS", "GET",        "CREATE",     "EXPR",        "APPEND",
      "SET_ARG",   "NEW_SCOPE",  "DEL_SCOPE",  "CALL",        "RETURN",
      "LOOP_ADDR", "BREAK",      "CONTINUE",   "SETRETVAL",   "EXIT",
      "BCODE_HDR", "SET_THIS",   "ARGS",       "FOR_IN_NEXT",
  };
  const char *name = "UNKNOWN OPCODE";
  assert(ARRAY_SIZE(names) == OP_MAX);
  if (opcode < ARRAY_SIZE(names)) name = names[opcode];
  return name;
}

void mjs_disasm(const uint8_t *code, size_t len, FILE *fp) {
  size_t i, start = 0;
  mjs_header_item_t map_offset = 0, total_size = 0;

  for (i = 0; i < len; i++) {
    fprintf(fp, "\t%-3u %-8s", (unsigned) i, opcodetostr(code[i]));

    if (map_offset > 0 && i == start + map_offset) {
      i = start + total_size - 1;
      fputc('\n', fp);
      continue;
    }

    switch (code[i]) {
      case OP_PUSH_FUNC: {
        int llen, n = varint_decode(&code[i + 1], &llen);
        fprintf(fp, " %04u", (unsigned) n);
        i += llen;
        break;
      }
      case OP_PUSH_INT: {
        int llen;
        unsigned long n = varint_decode(&code[i + 1], &llen);
        fprintf(fp, "\t%lu", n);
        i += llen;
        break;
      }
      case OP_SET_ARG: {
        int llen1, llen2, n, arg_no = varint_decode(&code[i + 1], &llen1);
        n = varint_decode(&code[i + llen1 + 1], &llen2);
        fprintf(fp, "\t[%.*s] %d", n, code + i + 1 + llen1 + llen2, arg_no);
        i += llen1 + llen2 + n;
        break;
      }
      case OP_PUSH_STR:
      case OP_PUSH_DBL: {
        int llen, n = varint_decode(&code[i + 1], &llen);
        fprintf(fp, "\t[%.*s]", n, code + i + 1 + llen);
        i += llen + n;
        break;
      }
      case OP_JMP_BACK:
        fprintf(fp, "\t%04u", (unsigned) i - code[i + 1]);
        i++;
        break;
      case OP_JMP:
      case OP_JMP_TRUE:
      case OP_JMP_FALSE: {
        fprintf(fp, "\t%u", (unsigned) i + code[i + 1]);
        i++;
        break;
      }
      case OP_LOOP: {
        int l1, l2, n2, n1 = varint_decode(&code[i + 1], &l1);
        n2 = varint_decode(&code[i + l1 + 1], &l2);
        fprintf(fp, "\t%lu %lu", (unsigned long) i + n1,
                (unsigned long) i + n2);
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
#endif
