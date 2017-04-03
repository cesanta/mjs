/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#include "mjs/src/mjs_bcode.h"
#include "mjs/src/mjs_core.h"
#include "mjs/src/mjs_internal.h"
#include "mjs/src/mjs_parser.h"
#include "mjs/src/mjs_string.h"
#include "mjs/src/mjs_tok.h"
#include "mjs/src/mjs_varint.h"

#ifndef MAX_TOKS_IN_EXPR
#define MAX_TOKS_IN_EXPR 40
#endif

#define FAIL_ERR(p, code)                                                  \
  do {                                                                     \
    p->mjs->error = code;                                                  \
    LOG(LL_DEBUG, ("ERROR line %d, [%.*s...]", __LINE__, 10, p->tok.ptr)); \
    return code;                                                           \
  } while (0)

#define pnext1(p)                            \
  do {                                       \
    LOG(LL_DEBUG, ("  PNEXT %d", __LINE__)); \
    pnext(p);                                \
  } while (0)

#define SYNTAX_ERROR(p) FAIL_ERR(p, MJS_SYNTAX_ERROR)
#undef EXPECT
#define EXPECT(p, t)       \
  if ((p)->tok.tok != (t)) \
    SYNTAX_ERROR(p);       \
  else                     \
    pnext1(p);

static mjs_err_t parse_statement(struct pstate *p);
static mjs_err_t parse_expr(struct pstate *p);

static int ptest(struct pstate *p) {
  struct pstate saved = *p;
  int tok = pnext(p);
  *p = saved;
  return tok;
}

static int s_unary_ops[] = {TOK_NOT, TOK_TILDA, TOK_PLUS_PLUS, TOK_MINUS_MINUS,
                            TOK_KEYWORD_TYPEOF, TOK_MINUS, TOK_PLUS, TOK_EOF};
static int s_comparison_ops[] = {TOK_LT, TOK_LE, TOK_GT, TOK_GE, TOK_EOF};
static int s_postfix_ops[] = {TOK_PLUS_PLUS, TOK_MINUS_MINUS, TOK_EOF};
static int s_equality_ops[] = {TOK_EQ, TOK_NE, TOK_EQ_EQ, TOK_NE_NE, TOK_EOF};
static int s_assign_ops[] = {
    TOK_ASSIGN,         TOK_PLUS_ASSIGN, TOK_MINUS_ASSIGN,  TOK_MUL_ASSIGN,
    TOK_DIV_ASSIGN,     TOK_REM_ASSIGN,  TOK_LSHIFT_ASSIGN, TOK_RSHIFT_ASSIGN,
    TOK_URSHIFT_ASSIGN, TOK_AND_ASSIGN,  TOK_XOR_ASSIGN,    TOK_OR_ASSIGN,
    TOK_EOF};

static int findtok(int *toks, int tok) {
  int i = 0;
  while (tok != toks[i] && toks[i] != TOK_EOF) i++;
  return toks[i];
}

static void emit_op(struct pstate *pstate, int tok) {
  assert(tok >= 0 && tok <= 255);
  emit_byte(pstate, OP_EXPR);
  emit_byte(pstate, tok);
}

// Intentionally left as macro rather than a function, to let the
// compiler to inline calls and mimimize runtime stack usage.
#define PARSE_LTR_BINOP(p, f1, f2, ops, prev_op)      \
  do {                                                \
    mjs_err_t res = MJS_OK;                           \
    if ((res = f1(p, TOK_EOF)) != MJS_OK) return res; \
    if (prev_op != TOK_EOF) emit_op(p, prev_op);      \
    if (findtok(ops, p->tok.tok) != TOK_EOF) {        \
      int op = p->tok.tok;                            \
      pnext1(p);                                      \
      if ((res = f2(p, op)) != MJS_OK) return res;    \
    }                                                 \
    return res;                                       \
  } while (0)

#define PARSE_RTL_BINOP(p, f1, f2, ops, prev_op)        \
  do {                                                  \
    mjs_err_t res = MJS_OK;                             \
    (void) prev_op;                                     \
    if ((res = f1(p, TOK_EOF)) != MJS_OK) return res;   \
    if (findtok(ops, p->tok.tok) != TOK_EOF) {          \
      int op = p->tok.tok;                              \
      pnext1(p);                                        \
      if ((res = f2(p, TOK_EOF)) != MJS_OK) return res; \
      emit_op(p, op);                                   \
    }                                                   \
    return res;                                         \
  } while (0)

static mjs_err_t parse_statement_list(struct pstate *p, int et) {
  mjs_err_t res = MJS_OK;
  int drop = 0;
  pnext1(p);
  while (res == MJS_OK && p->tok.tok != TOK_EOF && p->tok.tok != et) {
    if (drop) emit_byte(p, OP_DROP);
    res = parse_statement(p);
    drop = 1;
    while (p->tok.tok == TOK_SEMICOLON) pnext1(p);
  }
  return res;
}

static mjs_err_t parse_block(struct pstate *p, int mkscope) {
  mjs_err_t res = MJS_OK;
  LOG(LL_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  if (mkscope) emit_byte(p, OP_NEW_SCOPE);
  res = parse_statement_list(p, TOK_CLOSE_CURLY);
  EXPECT(p, TOK_CLOSE_CURLY);
  if (mkscope) emit_byte(p, OP_DEL_SCOPE);
  return res;
}

static mjs_err_t parse_function(struct pstate *p) {
  struct mbuf *bcode = &p->mjs->bcode;
  size_t prologue, off;
  int arg_no = 0;
  int name_provided = 0;
  mjs_err_t res = MJS_OK;

  EXPECT(p, TOK_KEYWORD_FUNCTION);

  if (p->tok.tok == TOK_IDENT) {
    /* Function name was provided */
    struct tok tmp = p->tok;
    name_provided = 1;
    emit_byte(p, OP_PUSH_STR);
    emit_str(p, tmp.ptr, tmp.len);
    emit_byte(p, OP_PUSH_SCOPE);
    emit_byte(p, OP_CREATE);
    emit_byte(p, OP_PUSH_STR);
    emit_str(p, tmp.ptr, tmp.len);
    emit_byte(p, OP_FIND_SCOPE);
    pnext1(p);
  }

  off = mjs_bcode_size(bcode);

  emit_byte(p, OP_JMP);
  emit_byte(p, 0);

  prologue = mjs_bcode_size(bcode);

  EXPECT(p, TOK_OPEN_PAREN);
  emit_byte(p, OP_NEW_SCOPE);
  // Emit names of function arguments
  while (p->tok.tok != TOK_CLOSE_PAREN) {
    if (p->tok.tok != TOK_IDENT) SYNTAX_ERROR(p);
    emit_byte(p, OP_SET_ARG);
    emit_int(p, arg_no);
    arg_no++;
    emit_str(p, p->tok.ptr, p->tok.len);
    if (ptest(p) == TOK_COMMA) pnext1(p);
    pnext1(p);
  }
  EXPECT(p, TOK_CLOSE_PAREN);
  if ((res = parse_block(p, 0)) != MJS_OK) return res;
  emit_byte(p, OP_RETURN);
  mjs_bcode_mutate_byte(p->mjs, off + 1, mjs_bcode_size(bcode) - off);
  emit_byte(p, OP_PUSH_FUNC);
  emit_int(p, prologue);
  if (name_provided) {
    emit_op(p, TOK_ASSIGN);
  }

  return res;
}

static mjs_err_t parse_object_literal(struct pstate *p) {
  mjs_err_t res = MJS_OK;
  EXPECT(p, TOK_OPEN_CURLY);
  emit_byte(p, OP_PUSH_OBJ);
  while (p->tok.tok != TOK_CLOSE_CURLY) {
    if (p->tok.tok != TOK_IDENT && p->tok.tok != TOK_STR) SYNTAX_ERROR(p);
    emit_byte(p, OP_DUP);
    emit_byte(p, OP_PUSH_STR);
    emit_str(p, p->tok.ptr, p->tok.len);
    emit_byte(p, OP_SWAP);
    pnext1(p);
    EXPECT(p, TOK_COLON);
    if ((res = parse_expr(p)) != MJS_OK) return res;
    emit_op(p, TOK_ASSIGN);
    emit_byte(p, OP_DROP);
    if (p->tok.tok == TOK_COMMA) pnext1(p);
  }
  return res;
}

static mjs_err_t parse_array_literal(struct pstate *p) {
  mjs_err_t res = MJS_OK;
  EXPECT(p, TOK_OPEN_BRACKET);
  emit_byte(p, OP_PUSH_ARRAY);
  while (p->tok.tok != TOK_CLOSE_BRACKET) {
    emit_byte(p, OP_DUP);
    if ((res = parse_expr(p)) != MJS_OK) return res;
    emit_byte(p, OP_APPEND);
    if (p->tok.tok == TOK_COMMA) pnext1(p);
  }
  return res;
}

static enum mjs_err parse_literal(struct pstate *p, const struct tok *t) {
  struct mbuf *bcode = &p->mjs->bcode;
  enum mjs_err res = MJS_OK;
  int tok = t->tok;
  LOG(LL_DEBUG, ("[%.*s] %p", p->tok.len, p->tok.ptr, &t));
  switch (t->tok) {
    case TOK_KEYWORD_FALSE:
      emit_byte(p, OP_PUSH_FALSE);
      break;
    case TOK_KEYWORD_TRUE:
      emit_byte(p, OP_PUSH_TRUE);
      break;
    case TOK_KEYWORD_UNDEFINED:
      emit_byte(p, OP_PUSH_UNDEF);
      break;
    case TOK_KEYWORD_NULL:
      emit_byte(p, OP_PUSH_NULL);
      break;
    case TOK_IDENT: {
      int prev_tok = p->prev_tok;
      int next_tok = ptest(p);
      emit_byte(p, OP_PUSH_STR);
      emit_str(p, t->ptr, t->len);
      emit_byte(p, prev_tok == TOK_DOT ? OP_SWAP : OP_FIND_SCOPE);
      if (!findtok(s_assign_ops, next_tok) &&
          !findtok(s_postfix_ops, next_tok) &&
          !findtok(s_postfix_ops, prev_tok)) {
        if (prev_tok == TOK_DOT) emit_byte(p, OP_SET_THIS);
        emit_byte(p, OP_GET);
      }
      break;
    }
    case TOK_NUM: {
      double iv, d = strtod(t->ptr, NULL);
      unsigned long uv = strtoul(t->ptr + 2, NULL, 16);
      if (t->ptr[0] == '0' && t->ptr[1] == 'x') d = uv;
      if (modf(d, &iv) == 0) {
        emit_byte(p, OP_PUSH_INT);
        emit_int(p, (int64_t) d);
      } else {
        emit_byte(p, OP_PUSH_DBL);
        emit_str(p, t->ptr, t->len);
      }
      break;
    }
    case TOK_STR:
      emit_byte(p, OP_PUSH_STR);
      embed_string(bcode, bcode->len, t->ptr, t->len, EMBSTR_UNESCAPE);
      break;
    case TOK_OPEN_BRACKET:
      res = parse_array_literal(p);
      break;
    case TOK_OPEN_CURLY:
      res = parse_object_literal(p);
      break;
    case TOK_OPEN_PAREN:
      pnext1(p);
      res = parse_expr(p);
      break;
    case TOK_KEYWORD_FUNCTION:
      res = parse_function(p);
      break;
    case TOK_KEYWORD_THIS:
      emit_byte(p, OP_PUSH_THIS);
      break;
    default:
      SYNTAX_ERROR(p);
  }
  if (tok != TOK_KEYWORD_FUNCTION) pnext1(p);
  return res;
}

static mjs_err_t parse_call_dot_mem(struct pstate *p, int prev_op) {
  int ops[] = {TOK_DOT, TOK_OPEN_PAREN, TOK_OPEN_BRACKET, TOK_EOF};
  mjs_err_t res = MJS_OK;
  if ((res = parse_literal(p, &p->tok)) != MJS_OK) return res;
  while (findtok(ops, p->tok.tok) != TOK_EOF) {
    if (p->tok.tok == TOK_OPEN_BRACKET) {
      EXPECT(p, TOK_OPEN_BRACKET);
      if ((res = parse_expr(p)) != MJS_OK) return res;
      emit_byte(p, OP_SWAP);
      emit_byte(p, OP_SET_THIS);
      emit_byte(p, OP_GET);
      EXPECT(p, TOK_CLOSE_BRACKET);
    } else if (p->tok.tok == TOK_OPEN_PAREN) {
      EXPECT(p, TOK_OPEN_PAREN);
      emit_byte(p, OP_ARGS);
      while (p->tok.tok != TOK_CLOSE_PAREN) {
        if ((res = parse_expr(p)) != MJS_OK) return res;
        if (p->tok.tok == TOK_COMMA) pnext1(p);
      }
      emit_byte(p, OP_CALL);
      EXPECT(p, TOK_CLOSE_PAREN);
    } else if (p->tok.tok == TOK_DOT) {
      EXPECT(p, TOK_DOT);
      if ((res = parse_call_dot_mem(p, TOK_DOT)) != MJS_OK) return res;
    }
  }
  (void) prev_op;
  return res;
}

static mjs_err_t parse_postfix(struct pstate *p, int prev_op) {
  mjs_err_t res = MJS_OK;
  if ((res = parse_call_dot_mem(p, prev_op)) != MJS_OK) return res;
  if (p->tok.tok == TOK_PLUS_PLUS || p->tok.tok == TOK_MINUS_MINUS) {
    int op = p->tok.tok == TOK_PLUS_PLUS ? TOK_POSTFIX_PLUS : TOK_POSTFIX_MINUS;
    emit_op(p, op);
    pnext1(p);
  }
  return res;
}

static mjs_err_t parse_unary(struct pstate *p, int prev_op) {
  mjs_err_t res = MJS_OK;
  int op = TOK_EOF;
  if (findtok(s_unary_ops, p->tok.tok) != TOK_EOF) {
    op = p->tok.tok;
    pnext1(p);
  }
  if ((res = parse_postfix(p, prev_op)) != MJS_OK) return res;
  if (op != TOK_EOF) {
    if (op == TOK_MINUS) op = TOK_UNARY_MINUS;
    if (op == TOK_PLUS) op = TOK_UNARY_PLUS;
    emit_op(p, op);
  }
  return res;
}

static mjs_err_t parse_mul_div_rem(struct pstate *p, int prev_op) {
  int ops[] = {TOK_MUL, TOK_DIV, TOK_REM, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_unary, parse_mul_div_rem, ops, prev_op);
}

static mjs_err_t parse_plus_minus(struct pstate *p, int prev_op) {
  int ops[] = {TOK_PLUS, TOK_MINUS, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_mul_div_rem, parse_plus_minus, ops, prev_op);
}

static mjs_err_t parse_shifts(struct pstate *p, int prev_op) {
  int ops[] = {TOK_LSHIFT, TOK_RSHIFT, TOK_URSHIFT, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_plus_minus, parse_shifts, ops, prev_op);
}

static mjs_err_t parse_comparison(struct pstate *p, int prev_op) {
  PARSE_LTR_BINOP(p, parse_shifts, parse_comparison, s_comparison_ops, prev_op);
}

static mjs_err_t parse_equality(struct pstate *p, int prev_op) {
  PARSE_LTR_BINOP(p, parse_comparison, parse_equality, s_equality_ops, prev_op);
}

static mjs_err_t parse_bitwise_and(struct pstate *p, int prev_op) {
  int ops[] = {TOK_AND, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_equality, parse_bitwise_and, ops, prev_op);
}

static mjs_err_t parse_bitwise_xor(struct pstate *p, int prev_op) {
  int ops[] = {TOK_XOR, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_bitwise_and, parse_bitwise_xor, ops, prev_op);
}

static mjs_err_t parse_bitwise_or(struct pstate *p, int prev_op) {
  int ops[] = {TOK_OR, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_bitwise_xor, parse_bitwise_or, ops, prev_op);
}

static mjs_err_t parse_logical_and(struct pstate *p, int prev_op) {
  int ops[] = {TOK_LOGICAL_AND, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_bitwise_or, parse_logical_and, ops, prev_op);
}

static mjs_err_t parse_logical_or(struct pstate *p, int prev_op) {
  int ops[] = {TOK_LOGICAL_OR, TOK_EOF};
  PARSE_LTR_BINOP(p, parse_logical_and, parse_logical_or, ops, prev_op);
}

static mjs_err_t parse_ternary(struct pstate *p, int prev_op) {
  struct mbuf *bcode = &p->mjs->bcode;
  mjs_err_t res = MJS_OK;
  if ((res = parse_logical_or(p, TOK_EOF)) != MJS_OK) return res;
  if (prev_op != TOK_EOF) emit_op(p, prev_op);
  if (p->tok.tok == TOK_QUESTION) {
    size_t off1, off2, off3;
    EXPECT(p, TOK_QUESTION);

    off1 = mjs_bcode_size(bcode);
    emit_byte(p, OP_JMP_FALSE);
    emit_byte(p, 0);

    if ((res = parse_ternary(p, TOK_EOF)) != MJS_OK) return res;

    emit_byte(p, OP_JMP);
    emit_byte(p, 0);
    off2 = mjs_bcode_size(bcode);

    emit_byte(p, OP_DROP);
    if (off2 - off1 >= 255) FAIL_ERR(p, MJS_INTERNAL_ERROR);
    mjs_bcode_mutate_byte(p->mjs, off1 + 1, off2 - off1);

    EXPECT(p, TOK_COLON);
    if ((res = parse_ternary(p, TOK_EOF)) != MJS_OK) return res;

    off3 = mjs_bcode_size(bcode);
    if (off3 - off2 >= 255) FAIL_ERR(p, MJS_INTERNAL_ERROR);
    mjs_bcode_mutate_byte(p->mjs, off2 - 1,
                          off3 - off2 + JUMP_INSTRUCTION_SIZE);
  }
  return res;
}

static mjs_err_t parse_assignment(struct pstate *p, int prev_op) {
  PARSE_RTL_BINOP(p, parse_ternary, parse_assignment, s_assign_ops, prev_op);
}

static mjs_err_t parse_expr(struct pstate *p) {
  return parse_assignment(p, TOK_EOF);
}

static mjs_err_t parse_let(struct pstate *p) {
  mjs_err_t res = MJS_OK;
  LOG(LL_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  EXPECT(p, TOK_KEYWORD_LET);
  for (;;) {
    struct tok tmp = p->tok;
    EXPECT(p, TOK_IDENT);

    emit_byte(p, OP_PUSH_STR);
    emit_str(p, tmp.ptr, tmp.len);
    emit_byte(p, OP_PUSH_SCOPE);
    emit_byte(p, OP_CREATE);

    if (p->tok.tok == TOK_ASSIGN) {
      pnext1(p);
      emit_byte(p, OP_PUSH_STR);
      emit_str(p, tmp.ptr, tmp.len);
      emit_byte(p, OP_FIND_SCOPE);
      if ((res = parse_expr(p)) != MJS_OK) return res;
      emit_op(p, TOK_ASSIGN);
    } else {
      emit_byte(p, OP_PUSH_UNDEF);
    }
    if (p->tok.tok == TOK_COMMA) {
      emit_byte(p, OP_DROP);
      pnext1(p);
    }
    if (p->tok.tok == TOK_SEMICOLON || p->tok.tok == TOK_EOF) break;
  }
  return res;
}

static mjs_err_t parse_block_or_stmt(struct pstate *p, int cs) {
  if (ptest(p) == TOK_OPEN_CURLY) {
    return parse_block(p, cs);
  } else {
    return parse_statement(p);
  }
}

static mjs_err_t parse_for_in(struct pstate *p) {
  mjs_err_t res = MJS_OK;
  size_t off_iter, off_done;
  struct mbuf *bcode = &p->mjs->bcode;

  emit_byte(p, OP_NEW_SCOPE);

  /* Put iterator variable name to the stack */
  if (p->tok.tok == TOK_KEYWORD_LET) {
    EXPECT(p, TOK_KEYWORD_LET);
    emit_byte(p, OP_PUSH_STR);
    emit_str(p, p->tok.ptr, p->tok.len);
    emit_byte(p, OP_PUSH_SCOPE);
    emit_byte(p, OP_CREATE);
  }
  emit_byte(p, OP_PUSH_STR);
  emit_str(p, p->tok.ptr, p->tok.len);

  /* Put object to the stack */
  EXPECT(p, TOK_IDENT);
  EXPECT(p, TOK_KEYWORD_IN);
  parse_expr(p);
  EXPECT(p, TOK_CLOSE_PAREN);

  emit_byte(p, OP_PUSH_UNDEF); /* Push iterator */

  off_iter = mjs_bcode_size(bcode);

  /* Before parsing condition statement, push break/continue offsets  */
  emit_byte(p, OP_LOOP);
  emit_byte(p, 0); /* Fill out OP_BREAK address later  */
  emit_byte(p, 3); /* Point OP_CONTINUE to the next instruction */

  emit_byte(p, OP_FOR_IN_NEXT);
  emit_byte(p, OP_DUP);
  emit_byte(p, OP_JMP_FALSE);
  emit_byte(p, 0);

  // Parse loop body
  if (p->tok.tok == TOK_OPEN_CURLY) {
    if ((res = parse_statement_list(p, TOK_CLOSE_CURLY)) != MJS_OK) return res;
    pnext1(p);
  } else {
    if ((res = parse_statement(p)) != MJS_OK) return res;
  }
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_CONTINUE);

  off_done = mjs_bcode_size(bcode);

  mjs_bcode_mutate_byte(p->mjs, off_iter + 1, off_done - off_iter + 1);
  mjs_bcode_mutate_byte(p->mjs, off_iter + 6, off_done - off_iter - 5);
  emit_byte(p, OP_BREAK);
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_DEL_SCOPE);

  return res;
}

static int check_for_in(struct pstate *p) {
  struct pstate saved = *p;
  int forin = 0;
  if (p->tok.tok == TOK_KEYWORD_LET) pnext1(p);
  if (p->tok.tok == TOK_IDENT) {
    pnext1(p);
    if (p->tok.tok == TOK_KEYWORD_IN) forin = 1;
  }
  *p = saved;
  return forin;
}

static mjs_err_t parse_for(struct pstate *p) {
  size_t off_cond, off_post, off_body, off_done;
  struct mbuf *bcode = &p->mjs->bcode;
  mjs_err_t res = MJS_OK;

  LOG(LL_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  EXPECT(p, TOK_KEYWORD_FOR);
  EXPECT(p, TOK_OPEN_PAREN);

  /* Look forward - is it for..in ? */
  if (check_for_in(p)) return parse_for_in(p);

  /* Parse pre-condition */
  emit_byte(p, OP_NEW_SCOPE);
  if (p->tok.tok == TOK_KEYWORD_LET) {
    if ((res = parse_let(p)) != MJS_OK) return res;
  } else {
    if ((res = parse_expr(p)) != MJS_OK) return res;
  }
  EXPECT(p, TOK_SEMICOLON);

  /* Before parsing condition statement, push break/continue offsets  */
  emit_byte(p, OP_LOOP);
  emit_byte(p, 0);
  emit_byte(p, 0);

  // parse condition statement
  off_cond = mjs_bcode_size(bcode);
  if ((res = parse_expr(p)) != MJS_OK) return res;
  EXPECT(p, TOK_SEMICOLON);

  // Exit the loop if false
  off_post = mjs_bcode_size(bcode);
  emit_byte(p, OP_JMP_FALSE);
  emit_byte(p, 0);

  // Jump to the loop body
  emit_byte(p, OP_JMP);
  emit_byte(p, 0);

  // Parse post-condition statement
  if ((res = parse_expr(p)) != MJS_OK) return res;
  EXPECT(p, TOK_CLOSE_PAREN);
  emit_byte(p, OP_DROP);

  // Post-condition statement done. Jump to the condition statement.
  off_body = mjs_bcode_size(bcode);
  emit_byte(p, OP_JMP_BACK);
  emit_byte(p, off_body - off_cond);

  // Parse loop body
  if (p->tok.tok == TOK_OPEN_CURLY) {
    if ((res = parse_statement_list(p, TOK_CLOSE_CURLY)) != MJS_OK) return res;
    pnext1(p);
  } else {
    if ((res = parse_statement(p)) != MJS_OK) return res;
  }
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_CONTINUE);

  off_done = mjs_bcode_size(bcode);
  mjs_bcode_mutate_byte(p->mjs, off_cond - 2, off_done - off_cond + 5);
  mjs_bcode_mutate_byte(p->mjs, off_cond - 1, off_post + 7 - off_cond);
  mjs_bcode_mutate_byte(p->mjs, off_post + 1, off_done - off_post);
  mjs_bcode_mutate_byte(p->mjs, off_post + 3, off_body - off_post);

  emit_byte(p, OP_DROP); /* remove JMP_FALSE value left by cond stmt */
  emit_byte(p, OP_BREAK);
  emit_byte(p, OP_DEL_SCOPE);

  return res;
}

static mjs_err_t parse_while(struct pstate *p) {
  size_t off_cond, off_body, off_done;
  mjs_err_t res = MJS_OK;

  EXPECT(p, TOK_KEYWORD_WHILE);
  EXPECT(p, TOK_OPEN_PAREN);

  emit_byte(p, OP_NEW_SCOPE);
  emit_byte(p, OP_LOOP);
  emit_byte(p, 0); /* Fill out OP_BREAK address later  */
  emit_byte(p, 3); /* Point OP_CONTINUE to the next instruction */

  // parse condition statement
  off_cond = mjs_bcode_size(&p->mjs->bcode);
  if ((res = parse_expr(p)) != MJS_OK) return res;
  EXPECT(p, TOK_CLOSE_PAREN);

  // Exit the loop if false
  off_body = mjs_bcode_size(&p->mjs->bcode);
  emit_byte(p, OP_JMP_FALSE);
  emit_byte(p, 0);

  // Parse loop body
  if (p->tok.tok == TOK_OPEN_CURLY) {
    if ((res = parse_statement_list(p, TOK_CLOSE_CURLY)) != MJS_OK) return res;
    pnext1(p);
  } else {
    if ((res = parse_statement(p)) != MJS_OK) return res;
  }
  emit_byte(p, OP_DROP);
  emit_byte(p, OP_CONTINUE);

  off_done = mjs_bcode_size(&p->mjs->bcode);
  mjs_bcode_mutate_byte(p->mjs, off_cond - 2, off_done - off_cond + 4);
  mjs_bcode_mutate_byte(p->mjs, off_body + 1, off_done - off_body);
  emit_byte(p, OP_BREAK);
  emit_byte(p, OP_DEL_SCOPE);
  return res;
}

static mjs_err_t parse_if(struct pstate *p) {
  size_t off_if, off_endif;
  mjs_err_t res = MJS_OK;
  LOG(LL_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  EXPECT(p, TOK_KEYWORD_IF);
  EXPECT(p, TOK_OPEN_PAREN);
  if ((res = parse_expr(p)) != MJS_OK) return res;

  off_if = mjs_bcode_size(&p->mjs->bcode);
  emit_byte(p, OP_JMP_FALSE);
  emit_byte(p, 0);

  EXPECT(p, TOK_CLOSE_PAREN);
  if ((res = parse_block_or_stmt(p, 1)) != MJS_OK) return res;

  if (p->tok.tok == TOK_KEYWORD_ELSE) {
    /*
     * Else clause is present, so, if the condition is not true, the jump
     * target (off_endif) should be not the current offset, but the offset
     * after jump-over-else opcode
     */
    size_t off_else, off_endelse;
    pnext1(p);
    off_else = mjs_bcode_size(&p->mjs->bcode);
    emit_byte(p, OP_JMP);
    emit_byte(p, 0);
    off_endif = mjs_bcode_size(&p->mjs->bcode);

    emit_byte(p, OP_DROP);
    if ((res = parse_block_or_stmt(p, 1)) != MJS_OK) return res;
    off_endelse = mjs_bcode_size(&p->mjs->bcode);
    if (off_endelse - off_else >= 255) FAIL_ERR(p, MJS_INTERNAL_ERROR);
    mjs_bcode_mutate_byte(p->mjs, off_else + 1 /*OP_JMP*/,
                          off_endelse - off_else);
  } else {
    /* Else clause is not present, so, current offset is a jump target
     * (off_endif) */
    off_endif = mjs_bcode_size(&p->mjs->bcode);
  }

  if (off_endif - off_if >= 255) FAIL_ERR(p, MJS_INTERNAL_ERROR);
  mjs_bcode_mutate_byte(p->mjs, off_if + 1 /*OP_JMP_FALSE*/,
                        off_endif - off_if);

  return res;
}

static mjs_err_t parse_return(struct pstate *p) {
  EXPECT(p, TOK_KEYWORD_RETURN);
  parse_expr(p);
  emit_byte(p, OP_SETRETVAL);
  emit_byte(p, OP_RETURN);
  return MJS_OK;
}

static mjs_err_t parse_statement(struct pstate *p) {
  LOG(LL_DEBUG, ("[%.*s]", 10, p->tok.ptr));
  switch (p->tok.tok) {
    case TOK_KEYWORD_LET:
      return parse_let(p);
    case TOK_OPEN_CURLY:
      return parse_block(p, 1);
    case TOK_KEYWORD_RETURN:
      return parse_return(p);
    case TOK_KEYWORD_FOR:
      return parse_for(p);
    case TOK_KEYWORD_WHILE:
      return parse_while(p);
    case TOK_KEYWORD_BREAK:
      emit_byte(p, OP_PUSH_UNDEF);
      emit_byte(p, OP_BREAK);
      pnext1(p);
      return MJS_OK;
    case TOK_KEYWORD_CONTINUE:
      emit_byte(p, OP_CONTINUE);
      pnext1(p);
      return MJS_OK;
    case TOK_KEYWORD_IF:
      return parse_if(p);
    case TOK_KEYWORD_CASE:
    case TOK_KEYWORD_CATCH:
    case TOK_KEYWORD_DELETE:
    case TOK_KEYWORD_DO:
    case TOK_KEYWORD_INSTANCEOF:
    case TOK_KEYWORD_NEW:
    case TOK_KEYWORD_SWITCH:
    case TOK_KEYWORD_THROW:
    case TOK_KEYWORD_TRY:
    case TOK_KEYWORD_VAR:
    case TOK_KEYWORD_VOID:
    case TOK_KEYWORD_WITH:
      mjs_set_errorf(p->mjs, MJS_SYNTAX_ERROR, "[%.*s] is not implemented",
                     p->tok.len, p->tok.ptr);
      return MJS_SYNTAX_ERROR;
    default:
      return parse_expr(p);
  }
}

MJS_PRIVATE mjs_err_t
mjs_parse(const char *path, const char *buf, struct mjs *mjs) {
  mjs_err_t res = MJS_OK;
  struct pstate p;
  pinit(path, buf, &p);
  p.mjs = mjs;
  emit_byte(&p, OP_BCODE_HEADER);

  /* Remember starting bcode position, and reserve the room for bcode header */
  size_t start_idx = p.mjs->bcode.len;
  mbuf_append(&p.mjs->bcode, NULL,
              sizeof(mjs_header_item_t) * MJS_HDR_ITEMS_CNT);

  /* Append NULL-terminated filename */
  mbuf_append(&p.mjs->bcode, path, strlen(path) + 1 /* null-terminate */);

  mjs_header_item_t bcode_offset = p.mjs->bcode.len - start_idx;
  memcpy(p.mjs->bcode.buf + start_idx +
             sizeof(mjs_header_item_t) * MJS_HDR_ITEM_BCODE_OFFSET,
         &bcode_offset, sizeof(mjs_header_item_t));

  p.start_bcode_idx = p.mjs->bcode.len;

  res = parse_statement_list(&p, TOK_EOF);
  emit_byte(&p, OP_EXIT);

  /* remember map offset */
  mjs_header_item_t map_offset = p.mjs->bcode.len - start_idx;
  memcpy(p.mjs->bcode.buf + start_idx +
             sizeof(mjs_header_item_t) * MJS_HDR_ITEM_MAP_OFFSET,
         &map_offset, sizeof(mjs_header_item_t));

  /* put map length varint */
  int map_len = p.offset_lineno_map.len;
  size_t llen = varint_llen(map_len);
  mbuf_resize(&p.mjs->bcode, p.mjs->bcode.size + llen);
  varint_encode(map_len, (uint8_t *) p.mjs->bcode.buf + p.mjs->bcode.len);
  p.mjs->bcode.len += llen;

  /* put the map itself */
  mbuf_append(&p.mjs->bcode, p.offset_lineno_map.buf, p.offset_lineno_map.len);

  mjs_header_item_t total_size = p.mjs->bcode.len - start_idx;
  memcpy(p.mjs->bcode.buf + start_idx +
             sizeof(mjs_header_item_t) * MJS_HDR_ITEM_TOTAL_SIZE,
         &total_size, sizeof(mjs_header_item_t));

  mbuf_free(&p.offset_lineno_map);

  return res;
}
