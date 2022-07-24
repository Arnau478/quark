#include "pte.h"

void pt_entry_add_attr(pt_entry_t *entry, uint32_t attr){
    *entry |= attr;
}

void pt_entry_del_attr(pt_entry_t *entry, uint32_t attr){
    *entry &= ~attr;
}

void pt_entry_set_frame(pt_entry_t *entry, phys_addr frame){
    *entry = (*entry & ~PTE_FRAME) | frame;
}

phys_addr pt_entry_get_frame(pt_entry_t entry){
    return entry & PTE_FRAME;
}

bool pt_entry_is_present(pt_entry_t entry){
    return entry & PTE_PRESENT;
}

bool pt_entry_is_writable(pt_entry_t entry){
    return entry & PTE_WRITABLE;
}
