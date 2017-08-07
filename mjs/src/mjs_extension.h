#ifndef __MJS_EXTENSION_H__
#define __MJS_EXTENSION_H__

/*
 * mjs extension, reef extensions for mjs
 */
__BEGIN_DECLS

#define MAKE_TAG(s, t) \
  ((uint64_t)(s) << 63 | (uint64_t) 0x7ff0 << 48 | (uint64_t)(t) << 48)

#define MJS_TAG_UNDEFINED MAKE_TAG(1, 3)

struct mjs_property {
  struct mjs_property *next; /* Linkage in struct mjs_object::properties */
  mjs_val_t name;            /* Property name (a string) */
  mjs_val_t value;           /* Property value */
};

mjs_err_t mjs_json_parse(struct mjs *mjs, const char *str, size_t len, mjs_val_t *res);
mjs_err_t mjs_json_stringify(struct mjs *mjs, mjs_val_t v, char *buf, size_t size, char **res);

void mjs_init_local(struct mjs *jsm, mjs_val_t o);

__END_DECLS
#endif
