.PHONY: initrd
initrd:
	@tar -cf $(BUILD_DIR)/initrd.tar -C src/initrd .
