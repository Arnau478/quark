.PHONY: iso
iso:
	@mkdir -p build/iso/boot/grub
	@cp build/kernel.bin build/iso/boot/kernel.bin
	@cp config/grub.cfg build/iso/boot/grub/grub.cfg
	@grub-mkrescue -o build/quark.iso build/iso
