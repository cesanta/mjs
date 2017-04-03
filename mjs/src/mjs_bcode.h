/*
 * Copyright (c) 2017 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_BCODE_H_
#define MJS_BCODE_H_

#include "mjs/src/mjs_internal.h"

enum mjs_opcode {
  OP_NOP,          /* ( -- ) */
  OP_DROP,         /* ( a -- ) */
  OP_DUP,          /* ( a -- a a ) */
  OP_SWAP,         /* ( a b -- b a ) */
  OP_JMP,          /* ( -- ) */
  OP_JMP_BACK,     /* ( -- ) */
  OP_JMP_TRUE,     /* ( -- ) */
  OP_JMP_FALSE,    /* ( -- ) */
  OP_FIND_SCOPE,   /* ( a -- a b ) */
  OP_PUSH_SCOPE,   /* ( -- a ) */
  OP_PUSH_STR,     /* ( -- a ) */
  OP_PUSH_TRUE,    /* ( -- a ) */
  OP_PUSH_FALSE,   /* ( -- a ) */
  OP_PUSH_INT,     /* ( -- a ) */
  OP_PUSH_DBL,     /* ( -- a ) */
  OP_PUSH_NULL,    /* ( -- a ) */
  OP_PUSH_UNDEF,   /* ( -- a ) */
  OP_PUSH_OBJ,     /* ( -- a ) */
  OP_PUSH_ARRAY,   /* ( -- a ) */
  OP_PUSH_FUNC,    /* ( -- a ) */
  OP_PUSH_THIS,    /* ( -- a ) */
  OP_GET,          /* ( key obj  -- obj[key] ) */
  OP_CREATE,       /* ( key obj -- ) */
  OP_EXPR,         /* ( ... -- a ) */
  OP_APPEND,       /* ( a b -- ) */
  OP_SET_ARG,      /* ( a -- a ) */
  OP_NEW_SCOPE,    /* ( -- ) */
  OP_DEL_SCOPE,    /* ( -- ) */
  OP_CALL,         /* ( func param1 param2 ... num_params -- result ) */
  OP_RETURN,       /* ( -- ) */
  OP_LOOP,         /* ( -- ) Push break & continue addresses to loop_labels */
  OP_BREAK,        /* ( -- ) */
  OP_CONTINUE,     /* ( -- ) */
  OP_SETRETVAL,    /* ( a -- ) */
  OP_EXIT,         /* ( -- ) */
  OP_BCODE_HEADER, /* ( -- ) */
  OP_SET_THIS,     /* ( -- ) */
  OP_ARGS,         /* ( -- ) Mark the beginning of function call arguments */
  OP_FOR_IN_NEXT,  /* ( name obj iter_ptr -- name obj iter_ptr_next ) */
  OP_MAX
};

struct pstate;
struct mjs;

MJS_PRIVATE void emit_byte(struct pstate *pstate, uint8_t byte);
MJS_PRIVATE void emit_int(struct pstate *pstate, int64_t n);
MJS_PRIVATE void emit_str(struct pstate *pstate, const char *ptr, size_t len);
MJS_PRIVATE size_t mjs_bcode_size(const struct mbuf *mbuf);
MJS_PRIVATE void mjs_bcode_mutate_byte(struct mjs *mbuf, size_t offset,
                                       size_t byte);

#endif /* MJS_BCODE_H_ */
