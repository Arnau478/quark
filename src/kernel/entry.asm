[bits 32]
extern kmain
extern i686_outw
global _start

_start:
    mov esp, _sys_stack
    jmp call_kmain

; Multiboot header
align 4
mboot:
    ; Some macros
    MULTIBOOT_PAGE_ALIGN equ 1<<0
    MULTIBOOT_MEMORY_INFO equ 1<<1
    MULTIBOOT_HEADER_MAGIC equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
    MULTIBOOT_CHECKSUM equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

    ; The actual header
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM

call_kmain:
    ; Enable interrupts
    sti
    ; Call kernel
    push ebx ; pointer to multiboot info
    call kmain
    ; If on qemu, shutdown
    push 0x2000
    push 0x604
    call i686_outw
    ; Halt
    jmp $

section .bss
    resb 8192 ; For the stack
_sys_stack:
