/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_PRIMITIVE_H
#define MJS_PRIMITIVE_H

#include "mjs/src/mjs_primitive_public.h"
#include "mjs/src/mjs_internal.h"

MJS_PRIVATE mjs_val_t pointer_to_value(void *p);
MJS_PRIVATE void *get_ptr(mjs_val_t v);

#endif /* MJS_PRIMITIVE_H */
