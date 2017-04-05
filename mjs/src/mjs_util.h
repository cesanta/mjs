/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_UTIL_H_
#define MJS_UTIL_H_

#include "mjs/src/mjs_util_public.h"

MJS_PRIVATE const char *opcodetostr(uint8_t opcode);
MJS_PRIVATE size_t mjs_disasm_single(const uint8_t *code, size_t i, FILE *fp);

#endif /* MJS_UTIL_H_ */
