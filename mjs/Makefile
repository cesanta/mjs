REPO_ROOT_PATH = ..
SRCPATH = src
VPATH = $(REPO_ROOT_PATH)/common $(REPO_ROOT_PATH)/frozen src
BUILD_DIR = build

CLANG = clang
ifneq ("$(wildcard /usr/bin/clang-3.6)","")
	CLANG:=/usr/bin/clang-3.6
endif

include $(SRCPATH)/mjs_sources.mk

TOP_SOURCES = $(addprefix $(SRCPATH)/, $(SOURCES))
TOP_HEADERS = $(addprefix $(SRCPATH)/, $(HEADERS))
TOP_SOURCES_DIRS = $(sort $(dir $(TOP_SOURCES)))
TOP_HEADERS_DIRS = $(sort $(dir $(TOP_HEADERS)))

MFLAGS += -I. -I$(REPO_ROOT_PATH) -Isrc
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

TESTUTIL_FILES = $(REPO_ROOT_PATH)/common/cs_dirent.c \
                 $(REPO_ROOT_PATH)/common/cs_time.c \
                 $(REPO_ROOT_PATH)/common/test_util.c

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

$(BUILD_DIR)/unit_test: tests/unit_test.c mjs.c $(TESTUTIL_FILES) $(BUILD_DIR)
	$(CLANG) -W -Wall -I. -I$(REPO_ROOT_PATH) -g3 -O0 $(COMMON_CFLAGS) $(TEST_CFLAGS) $< $(TESTUTIL_FILES) -o $@

test: $(BUILD_DIR)/unit_test $(PROG)
	$(BUILD_DIR)/unit_test

clean:
	rm -rf $(BUILD_DIR) *.obj mjs.c mjs.h

REPO_ABS_PATH := $(shell cd $(REPO_ROOT_PATH) && pwd)
CLANG_FORMAT := docker run --workdir $(REPO_ABS_PATH) --rm -v $(REPO_ABS_PATH):$(REPO_ABS_PATH) docker.cesanta.com/bob /usr/bin/clang-format-3.6 -i
format:
	@git --git-dir $(REPO_ABS_PATH)/.git --work-tree .. ls-files --full-name '*.[ch]' | xargs -t $(CLANG_FORMAT)

print_sources:
	@echo $(TOP_SOURCES) $(TOP_HEADERS)

print_source_dirs:
	@echo $(TOP_SOURCES_DIRS) $(TOP_HEADERS_DIRS)

###################################  Windows targets for wine, with MSVC6

$(PROG).exe: $(BUILD_DIR) $(TOP_HEADERS) mjs.c
	wine cl $(MFLAGS) mjs.c -O1 -MD /Fe$@

$(BUILD_DIR)/unit_test.exe: tests/unit_test.c mjs.c $(TESTUTIL_FILES) $(BUILD_DIR)
	wine cl -I. -I$(REPO_ROOT_PATH) $< $(TESTUTIL_FILES) -o $@

wtest: $(BUILD_DIR)/unit_test.exe
	wine $(BUILD_DIR)/unit_test.exe
