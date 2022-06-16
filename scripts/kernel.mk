.PHONY: kernel
kernel: $(BUILD_DIR)/kernel.bin

HEADERS_C = $(shell find src/kernel -type f -name "*.h")
SOURCES_C = $(shell find src/kernel -type f -name "*.c")
OBJECTS_C = $(patsubst src/kernel/%.c, $(BUILD_DIR)/kernel/c/%.obj, $(SOURCES_C))
HEADERS_ASM = $(shell find src/kernel -type f -name "*.inc")
SOURCES_ASM = $(shell find src/kernel -type f -name "*.asm")
OBJECTS_ASM = $(patsubst src/kernel/%.asm, $(BUILD_DIR)/kernel/asm/%.obj, $(SOURCES_ASM))

$(BUILD_DIR)/kernel.bin: $(OBJECTS_ASM) $(OBJECTS_C)
	@$(TARGET_LD) $(TARGET_LINKFLAGS) -T scripts/kernel.ld -nostdlib -Wl,-Map=$(BUILD_DIR)/kernel.map -o $@ $^ $(TARGET_LIBS) -lgcc
	@echo -e $(ARROW) "Created $(basename $@)"

$(BUILD_DIR)/kernel/c/%.obj: src/kernel/%.c $(HEADERS_C)
	@mkdir -p $(@D)
	@$(TARGET_CC) $(TARGET_CFLAGS) -ffreestanding -nostdlib -c -o $@ $<
	@echo -e $(ARROW) "Compiled $<"

$(BUILD_DIR)/kernel/asm/%.obj: src/kernel/%.asm $(HEADERS_ASM)
	@mkdir -p $(@D)
	@$(TARGET_ASM) $(TARGET_ASMFLAGS) -f elf -o $@ $<
	@echo -e $(ARROW) "Assembled $<"
