global i686_vmm_flush_tlb_entry
i686_vmm_flush_tlb_entry:
    [bits 32]
    cli
    invlpg [esp + 4]
    sti

    ret
