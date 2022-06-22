.PHONY: run
run: quark run-qemu

.PHONY: run-qemu
run-qemu:
	@echo -e $(ARROW) "Running on qemu..."
	@qemu-system-i386 $(BUILD_DIR)/quark.iso -serial stdio
	@echo -e $(ARROW) "Finished run"
