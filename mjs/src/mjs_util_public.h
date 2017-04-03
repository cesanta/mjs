/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_UTIL_PUBLIC_H_
#define MJS_UTIL_PUBLIC_H_

#include "mjs/src/mjs_core_public.h"
#include <stdio.h>

const char *mjs_typeof(mjs_val_t v);

void mjs_fprintf(mjs_val_t v, struct mjs *mjs, FILE *fp);

#if MJS_ENABLE_DEBUG

void mjs_disasm(const uint8_t *code, size_t len, FILE *fp);
void mjs_dump(struct mjs *mjs, int do_disasm, FILE *fp);

#endif

#endif /* MJS_UTIL_PUBLIC_H_ */
