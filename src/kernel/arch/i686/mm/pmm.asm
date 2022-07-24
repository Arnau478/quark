global i686_pmm_paging_enable
i686_pmm_paging_enable:
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

global i686_pmm_is_paging
i686_pmm_is_paging:
    [bits 32]
    mov eax, cr0
    and eax, 0x80000000
    ret

global i686_pmm_load_pdbr
i686_pmm_load_pdbr:
    [bits 32]
    mov eax, [esp + 4]
    mov cr3, eax
    ret

global i686_pmm_get_pdbr
i686_pmm_get_pdbr:
    [bits 32]
    mov eax, cr3
    ret
