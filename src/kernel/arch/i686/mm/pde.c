#include "pde.h"

void i686_pd_entry_add_attr(i686_pd_entry_t *entry, uint32_t attr){
    *entry |= attr;
}

void i686_pd_entry_del_attr(i686_pd_entry_t *entry, uint32_t attr){
    *entry &= ~attr;
}

void i686_pd_entry_set_frame(i686_pd_entry_t *entry, i686_phys_addr frame){
    *entry = (*entry & ~i686_PDE_FRAME) | frame;
}

i686_phys_addr i686_pd_entry_get_frame(i686_pd_entry_t entry){
    return entry & i686_PDE_FRAME;
}

bool i686_pd_entry_is_present(i686_pd_entry_t entry){
    return entry & i686_PDE_PRESENT;
}

bool i686_pd_entry_is_user(i686_pd_entry_t entry){
    return entry & i686_PDE_USER;
}

bool i686_pd_entry_is_4mb(i686_pd_entry_t entry){
    return entry & i686_PDE_4MB;
}

bool i686_pd_entry_is_writable(i686_pd_entry_t entry){
    return entry & i686_PDE_WRITABLE;
}
