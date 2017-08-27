COMMON = ../../common
FROZEN = ../../frozen

SOURCES = $(COMMON)/cs_dbg.c \
          $(COMMON)/cs_file.c \
          $(COMMON)/cs_varint.c \
          $(COMMON)/mbuf.c \
          $(COMMON)/mg_str.c \
          $(COMMON)/str_util.c \
          $(FROZEN)/frozen.c \
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

HEADERS = $(COMMON)/mbuf.h \
          $(COMMON)/cs_dbg.h \
          $(COMMON)/cs_file.h \
          $(COMMON)/cs_time.h \
          $(COMMON)/cs_varint.h \
          $(COMMON)/str_util.h \
          $(COMMON)/mg_mem.h \
          $(COMMON)/platform.h \
          $(FROZEN)/frozen.h \
          ffi/ffi.h \
          mjs_array.h \
          mjs_array_public.h \
          mjs_bcode.h \
          mjs_builtin.h \
          mjs_conversion.h \
          mjs_core.h \
          mjs_core_public.h \
          mjs_dataview.h \
          mjs_exec.h \
          mjs_exec_public.h \
          mjs_features.h \
          mjs_ffi.h \
          mjs_ffi_public.h \
          mjs_gc.h \
          mjs_internal.h \
          mjs_json.h \
          mjs_license.h \
          mjs_mm.h \
          mjs_object.h \
          mjs_object_public.h \
          mjs_parser.h \
          mjs_primitive.h \
          mjs_primitive_public.h \
          mjs_string.h \
          mjs_string_public.h \
          mjs_tok.h \
          mjs_util.h \
          mjs_util_public.h
