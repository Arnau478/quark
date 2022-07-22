#include "pde.h"

void pd_entry_add_attr(pd_entry_t *entry, uint32_t attr){
    *entry |= attr;
}

void pd_entry_del_attr(pd_entry_t *entry, uint32_t attr){
    *entry &= ~attr;
}

void pd_entry_set_frame(pd_entry_t *entry, phys_addr frame){
    *entry &= ~PDE_FRAME;
    *entry |= frame << 12;
}

phys_addr pd_entry_get_frame(pd_entry_t entry){
    return entry >> 12;
}

bool pd_entry_is_present(pd_entry_t entry){
    return entry & PDE_PRESENT;
}

bool pd_entry_is_user(pd_entry_t entry){
    return entry & PDE_USER;
}

bool pd_entry_is_4mb(pd_entry_t entry){
    return entry & PDE_4MB;
}

bool pd_entry_is_writable(pd_entry_t entry){
    return entry & PDE_WRITABLE;
}
