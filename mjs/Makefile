REPO_ROOT = ..
SRCPATH = src
VPATH = $(REPO_ROOT)/common $(REPO_ROOT)/frozen src
BUILD_DIR = build

include $(SRCPATH)/mjs_sources.mk

TOP_SOURCES = $(addprefix $(SRCPATH)/, $(SOURCES))
TOP_HEADERS = $(addprefix $(SRCPATH)/, $(HEADERS))
TOP_SOURCES_DIRS = $(sort $(dir $(TOP_SOURCES)))
TOP_HEADERS_DIRS = $(sort $(dir $(TOP_HEADERS)))

MFLAGS += -I. -I$(REPO_ROOT) -Isrc
MFLAGS += -DMJS_MAIN -DMJS_EXPOSE_PRIVATE -DCS_ENABLE_STDIO -DMJS_ENABLE_DEBUG
CFLAGS += -W -Wall -g -O0
CFLAGS += $(MFLAGS) $(CFLAGS_EXTRA)
COMMON_CFLAGS =
TEST_CFLAGS = -DMJS_AGGRESSIVE_GC -fsanitize=address

VERBOSE ?=
ifeq ($(VERBOSE),1)
Q :=
else
Q := @
endif

ifeq ($(OS),Windows_NT)
  UNAME_S := Windows
else
  UNAME_S := $(shell uname -s)
endif

ifeq ($(UNAME_S),Linux)
  COMMON_CFLAGS += -Wl,--no-as-needed -ldl
  TEST_CFLAGS += -fsanitize=leak
endif

PROG = $(BUILD_DIR)/mjs

all: $(PROG)

TESTUTIL_FILES = $(REPO_ROOT)/common/cs_dirent.c \
                 $(REPO_ROOT)/common/cs_time.c \
                 $(REPO_ROOT)/common/test_util.c

mjs.c: $(TOP_SOURCES) mjs.h Makefile
	@printf "AMALGAMATING\tmjs.c\n"
	$(Q) (cd .. && tools/amalgam.py \
	  --autoinc --exportable-headers -I mjs --prefix MJS \
    --public-header mjs.h --ignore mjs/mjs.h \
    --first mjs/src/license.h,mjs/src/internal.h,common/platform.h,common/platforms/platform_windows.h,common/platforms/platform_unix.h,common/platforms/platform_esp_lwip.h $(TOP_SOURCES)) > $@

mjs.h: $(TOP_HEADERS) $(TOP_SOURCES) Makefile
	@printf "AMALGAMATING\tmjs.h\n"
	$(Q) (cd .. && tools/amalgam.py \
	  --autoinc --exportable-headers -I mjs --prefix MJS \
    --ignore mjs/mjs.h \
    --first mjs/src/license.h,common/platform.h $(filter %_public.h,$(TOP_HEADERS))) > $@

CFLAGS += $(COMMON_CFLAGS)

# NOTE: we compile straight from sources, not from the single amalgamated file,
# in order to make sure that all sources include the right headers
$(PROG): $(TOP_SOURCES) $(TOP_HEADERS) $(BUILD_DIR)
	$(CLANG) $(CFLAGS) $(CPPFLAGS) $(TOP_SOURCES) -o $(PROG)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c $(TOP_HEADERS)
	$(CLANG) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# On Windows and Mac, run container as root since volume sharing on those OSes
# doesn't play nice with unprivileged user.
#
# On other OSes, run it as the current user.
DOCKER_USER_ARG =
ifneq ($(OS),Windows_NT)
UNAME_S := $(shell uname -s)
ifneq ($(UNAME_S),Darwin)
DOCKER_USER_ARG = --user $$(id -u):$$(id -u)
endif
endif

COMMON_TEST_FLAGS = -W -Wall -I. -I$(REPO_ROOT) -g3 -O0 $(COMMON_CFLAGS) $(TEST_CFLAGS) $< $(TESTUTIL_FILES)

test: $(BUILD_DIR)/unit_test $(PROG)
	$(BUILD_DIR)/unit_test

# test_full TODO(dfrank): refactor {{{
$(BUILD_DIR)/unit_test: tests/unit_test.c mjs.c $(TESTUTIL_FILES) $(BUILD_DIR)
	$(CLANG) $(COMMON_TEST_FLAGS) -o $@

$(BUILD_DIR)/unit_test_init0: tests/unit_test.c mjs.c $(TESTUTIL_FILES) $(BUILD_DIR)
	$(CLANG) $(COMMON_TEST_FLAGS) -DMJS_INIT_OFFSET_SIZE=0 -o $@

$(BUILD_DIR)/unit_test_init4: tests/unit_test.c mjs.c $(TESTUTIL_FILES) $(BUILD_DIR)
	$(CLANG) $(COMMON_TEST_FLAGS) -DMJS_INIT_OFFSET_SIZE=4 -o $@

test_full: $(PROG) \
    $(BUILD_DIR)/unit_test \
    $(BUILD_DIR)/unit_test_init0 \
    $(BUILD_DIR)/unit_test_init4
	$(BUILD_DIR)/unit_test
	$(BUILD_DIR)/unit_test_init0
	$(BUILD_DIR)/unit_test_init4
# }}}

clean:
	rm -rf $(BUILD_DIR) *.obj mjs.c mjs.h

print_sources:
	@echo $(TOP_SOURCES) $(TOP_HEADERS)

print_source_dirs:
	@echo $(TOP_SOURCES_DIRS) $(TOP_HEADERS_DIRS)

###################################  Windows targets for wine, with MSVC6

$(PROG).exe: $(BUILD_DIR) $(TOP_HEADERS) mjs.c
	wine cl $(MFLAGS) mjs.c -O1 -MD /Fe$@

$(BUILD_DIR)/unit_test.exe: tests/unit_test.c mjs.c $(TESTUTIL_FILES) $(BUILD_DIR)
	wine cl -I. -I$(REPO_ROOT) $< $(TESTUTIL_FILES) -o $@

wtest: $(BUILD_DIR)/unit_test.exe
	wine $(BUILD_DIR)/unit_test.exe

include $(REPO_ROOT)/common.mk
