GO_PACKAGES = cesanta.com/common/... \
             cesanta.com/ourci/... \
             cesanta.com/projects/breez/...

FORMAT_FILES ?= '*.[ch]'
REPO_ABS_PATH := $(shell cd $(REPO_ROOT) && pwd)

# Additional filter shell command for files to format; it could be for example
# "grep -v foobar", or even "grep -v foo | grep -v bar" (without quotes).
FORMAT_FILES_FILTER_CMD ?=
ifneq ("$(FORMAT_FILES_FILTER_CMD)","")
	FORMAT_FILES_FILTER_CMD += |
endif

CLANG = clang
ifneq ("$(wildcard /usr/bin/clang-3.6)","")
  CLANG:=/usr/bin/clang-3.6
endif

# installable with: `brew install llvm36 --with-clang`
ifneq ("$(wildcard /usr/local/bin/clang-format-3.6)","")
  CLANG_FORMAT = /usr/local/bin/clang-format-3.6
else ifneq ("$(wildcard /usr/bin/clang-format-3.6)","")
  CLANG_FORMAT = /usr/bin/clang-format-3.6
else
  CLANG_FORMAT = docker run --rm \
    --user $(shell id -u):$(shell id -g) \
    -v $(REPO_ABS_PATH):$(REPO_ABS_PATH) \
    -w $(REPO_ABS_PATH) \
    $(DOCKER_USER_ARG) \
    docker.cesanta.com/bob \
    /usr/bin/clang-format-3.6
endif

format:
	@echo "Formatting $$(basename $(CURDIR)) $(REPO_ROOT)"
	@test -d "$(REPO_ROOT)" && true || { echo "Define REPO_ROOT Makefile variable, REPO_ROOT/common.mk wants it." ; false ; }
	@git --git-dir $(REPO_ABS_PATH)/.git --work-tree $(REPO_ROOT) \
		ls-files --full-name $(FORMAT_FILES) | \
		$(FORMAT_FILES_FILTER_CMD) \
		xargs -IFILE echo $(REPO_ABS_PATH)/FILE | \
		xargs -t $(CLANG_FORMAT) -i
