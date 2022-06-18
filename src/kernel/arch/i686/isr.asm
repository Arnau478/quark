[bits 32]

extern i686_isr_handler

%macro ISR_NOERRORCODE 1

global i686_ISR%1
i686_ISR%1:
    push 0 ; No error code
    push %1 ; Interrupt number
    jmp isr_common

%endmacro

%macro ISR_ERRORCODE 1

global i686_ISR%1
i686_ISR%1:
    ; Error code pushed by the CPU
    push %1 ; Interrupt number
    jmp isr_common

%endmacro

%include "src/kernel/arch/i686/isrs_gen.inc"

isr_common:
    pusha

    ; Push ds
    xor eax, eax
    mov ax, ds
    push eax

    ; Ensure that we are on kernel mode
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Call C handler
    push esp
    call i686_isr_handler
    add esp, 4

    ; Restore old segment
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Return
    popa
    add esp, 8
    iret
