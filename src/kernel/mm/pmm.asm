global pmm_paging_enable
pmm_paging_enable:
    [bits 32]
    ; New call frame
    push ebp
    mov ebp, esp

    mov eax, cr0
    cmp byte [esp + 4], 0
    jg .enable
    jmp .disable
.enable:
    or eax, 0x80000000 ; Set bit 31
    jmp .done
.disable:
    and eax, 0x7FFFFFFF ; Clear bit 31
.done:
    mov cr0, eax

    ; Restore old call frame
    mov esp, ebp
    pop ebp
    ret

global pmm_is_paging
pmm_is_paging:
    [bits 32]
    mov eax, cr0
    and eax, 0x80000000
    ret

global pmm_load_pdbr
pmm_load_pdbr:
    [bits 32]
    mov eax, [esp + 4]
    mov cr3, eax
    ret

global pmm_get_pdbr
pmm_get_pdbr:
    [bits 32]
    mov eax, cr3
    ret
