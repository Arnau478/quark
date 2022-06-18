[bits 32]

global i686_gdt_load
i686_gdt_load:
    ; New call frame
    push ebp
    mov ebp, esp

    ; Load GDT
    mov eax, [ebp + 8]
    lgdt [eax]

    ; Reload code segment
    mov eax, [ebp + 12]
    push eax
    push .reload_cs
    retf

.reload_cs:
    ; Reload data segments
    mov ax, [ebp + 16]
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Restore old call frame
    mov esp, ebp
    pop ebp
    ret
