/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_PARSER_H
#define MJS_PARSER_H

#include "mjs/src/mjs_internal.h"

MJS_PRIVATE mjs_err_t
mjs_parse(const char *path, const char *buf, struct mjs *);

#endif /* MJS_PARSER_H */
