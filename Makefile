include scripts/toolchain.mk

BUILD_DIR?=build/

quark: build-dir $(BUILD_DIR)/quark

.PHONY: build-dir
build-dir:
	@mkdir -p $(BUILD_DIR)
