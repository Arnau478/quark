global vmm_flush_tlb_entry
vmm_flush_tlb_entry:
    [bits 32]
    cli
    invlpg [esp + 4]
    sti

    ret
