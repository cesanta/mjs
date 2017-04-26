/*
 * Copyright (c) 2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef MJS_OBJECT_PUBLIC_H_
#define MJS_OBJECT_PUBLIC_H_

#include "mjs/src/mjs_core_public.h"
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*
 * Returns true if the given value is an object or array.
 */
int mjs_is_object(mjs_val_t v);

/* Make an empty object */
mjs_val_t mjs_mk_object(struct mjs *mjs);

/*
 * Lookup property `name` in object `obj`. If `obj` holds no such property,
 * an `undefined` value is returned.
 *
 * If `name_len` is ~0, `name` is assumed to be NUL-terminated and
 * `strlen(name)` is used.
 */
mjs_val_t mjs_get(struct mjs *mjs, mjs_val_t obj, const char *name,
                  size_t name_len);

/*
 * Like mjs_get but with a JS string.
 */
mjs_val_t mjs_get_v(struct mjs *mjs, mjs_val_t obj, mjs_val_t name);

/*
 * Like mjs_get_v but lookup the prototype chain.
 */
mjs_val_t mjs_get_v_proto(struct mjs *mjs, mjs_val_t obj, mjs_val_t key);

/*
 * Set object property. Behaves just like JavaScript assignment.
 */
mjs_err_t mjs_set(struct mjs *mjs, mjs_val_t obj, const char *name, size_t len,
                  mjs_val_t val);

/*
 * Like mjs_set but the name is already a JS string.
 */
mjs_err_t mjs_set_v(struct mjs *mjs, mjs_val_t obj, mjs_val_t name,
                    mjs_val_t val);

/*
 * Delete own property `name` of the object `obj`. Does not follow the
 * prototype chain.
 *
 * If `name_len` is ~0, `name` is assumed to be NUL-terminated and
 * `strlen(name)` is used.
 *
 * Returns 0 on success, -1 on error.
 */
int mjs_del(struct mjs *mjs, mjs_val_t obj, const char *name, size_t len);

/*
 * Iterate over `obj` properties.
 * First call should set `iterator` to MJS_UNDEFINED.
 * Return object's key (a string), or MJS_UNDEFINED when no more keys left.
 * Do not mutate the object during iteration.
 *
 * Example:
 *   mjs_val_t key, iter = MJS_UNDEFINED;
 *   while ((key = mjs_next(mjs, obj, &iter)) != MJS_UNDEFINED) {
 *     // Do something with the obj/key ...
 *   }
 */
mjs_val_t mjs_next(struct mjs *mjs, mjs_val_t obj, mjs_val_t *iterator);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* MJS_OBJECT_PUBLIC_H_ */
