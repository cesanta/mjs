COMMON_SOURCES = \
          common/cs_dbg.c \
          common/cs_file.c \
          common/cs_varint.c \
          common/mbuf.c \
          common/mg_str.c \
          common/str_util.c \
          frozen/frozen.c

MJS_SOURCES = \
          ffi/ffi.c \
          mjs_array.c \
          mjs_bcode.c \
          mjs_builtin.c \
          mjs_conversion.c \
          mjs_core.c \
          mjs_dataview.c \
          mjs_exec.c \
          mjs_ffi.c \
          mjs_gc.c \
          mjs_json.c \
          mjs_main.c \
          mjs_object.c \
          mjs_parser.c \
          mjs_primitive.c \
          mjs_string.c \
          mjs_tok.c \
          mjs_util.c

MJS_PUBLIC_HEADERS = \
          mjs_array_public.h \
          mjs_core_public.h \
          mjs_exec_public.h \
          mjs_ffi_public.h \
          mjs_gc_public.h \
          mjs_object_public.h \
          mjs_primitive_public.h \
          mjs_string_public.h \
          mjs_util_public.h

HEADERS = common/mbuf.h \
          common/cs_dbg.h \
          common/cs_file.h \
          common/cs_time.h \
          common/cs_varint.h \
          common/str_util.h \
          common/mg_mem.h \
          common/platform.h \
          frozen/frozen.h \
          ffi/ffi.h \
          mjs_array.h \
          mjs_bcode.h \
          mjs_builtin.h \
          mjs_conversion.h \
          mjs_core.h \
          mjs_dataview.h \
          mjs_exec.h \
          mjs_features.h \
          mjs_ffi.h \
          mjs_gc.h \
          mjs_internal.h \
          mjs_json.h \
          mjs_license.h \
          mjs_mm.h \
          mjs_object.h \
          mjs_parser.h \
          mjs_primitive.h \
          mjs_string.h \
          mjs_tok.h \
          mjs_util.h
