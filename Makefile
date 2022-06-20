.PHONY: quark
quark: build-dir kernel iso

include config/.conf
include scripts/toolchain.mk
include scripts/kernel.mk
include scripts/run.mk
include scripts/iso.mk

.PHONY: build-dir
build-dir:
	@mkdir -p $(BUILD_DIR)
	@echo -e $(ARROW) "Created build directory"

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)/**
