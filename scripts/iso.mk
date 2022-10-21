.PHONY: iso
iso:
	@mkdir -p build/iso/boot/grub
	@cp build/kernel.bin build/iso/boot/kernel.bin
	@cp config/grub.cfg build/iso/boot/grub/grub.cfg
	@cp build/initrd.tar build/iso/boot/initrd.tar
	@grub-mkrescue -o build/quark.iso build/iso
