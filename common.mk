GO_PACKAGES = $(shell go list cesanta.com/cloud/... | grep -v vendor) \
             cesanta.com/be/... \
             cesanta.com/clubby/... \
             cesanta.com/common/... \
             cesanta.com/fw/... \
             cesanta.com/mos/... \
             cesanta.com/ourci/... \
             cesanta.com/projects/breez/...

FORMAT_FILES ?= '*.[ch]'
REPO_ABS_PATH := $(shell cd $(REPO_ROOT) && pwd)

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
    -v $(REPO_ABS_PATH):$(REPO_ABS_PATH) \
    $(DOCKER_USER_ARG) \
    docker.cesanta.com/bob \
    /usr/bin/clang-format-3.6
endif

format:
	@echo "Formatting $$(basename $(CURDIR))"
	@test -d "$(REPO_ROOT)" && true || { echo "Define REPO_ROOT Makefile variable, REPO_ROOT/common.mk wants it." ; false ; }
	@git --git-dir $(REPO_ABS_PATH)/.git --work-tree $(REPO_ROOT) \
		ls-files --full-name $(FORMAT_FILES) | \
		xargs -IFILE echo $(REPO_ABS_PATH)/FILE | \
		xargs -t $(CLANG_FORMAT) -i
