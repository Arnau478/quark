.PHONY: run
run: quark run-qemu

.PHONY: run-qemu
run-qemu:
	@echo -e $(ARROW) "Running on qemu..."
	@qemu-system-i386 -kernel $(BUILD_DIR)/kernel.bin
	@echo -e $(ARROW) "Finished run"