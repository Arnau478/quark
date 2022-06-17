[bits 32]

global i686_idt_load
i686_idt_load:
    ; New call frame
    push ebp
    mov ebp, esp

    ; Load IDT
    mov eax, [ebp + 8]
    lidt [eax]

    ; Restore call frame
    mov esp, ebp
    pop ebp
    ret
