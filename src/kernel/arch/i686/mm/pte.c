#include "pte.h"

void i686_pt_entry_add_attr(i686_pt_entry_t *entry, uint32_t attr){
    *entry |= attr;
}

void i686_pt_entry_del_attr(i686_pt_entry_t *entry, uint32_t attr){
    *entry &= ~attr;
}

void i686_pt_entry_set_frame(i686_pt_entry_t *entry, i686_phys_addr frame){
    *entry = (*entry & ~i686_PTE_FRAME) | frame;
}

i686_phys_addr i686_pt_entry_get_frame(i686_pt_entry_t entry){
    return entry & i686_PTE_FRAME;
}

bool i686_pt_entry_is_present(i686_pt_entry_t entry){
    return entry & i686_PTE_PRESENT;
}

bool i686_pt_entry_is_writable(i686_pt_entry_t entry){
    return entry & i686_PTE_WRITABLE;
}
