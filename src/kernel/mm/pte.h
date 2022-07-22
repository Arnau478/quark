#pragma once

#include <stdint.h>
#include "pmm.h"

enum PTE_PAGE_FLAGS{
    PTE_PRESENT = 0x0001,
    PTE_WRITABLE = 0x0002,
    PTE_USER = 0x0004,
    PTE_WRITETHROUGH = 0x0008,
    PTE_NOT_CACHEABLE = 0x0010,
    PTE_ACCESSED = 0x0020,
    PTE_DIRTY = 0x0040,
    PTE_PAT = 0x0080,
    PTE_CPU_GLOBAL = 0x0100,
    PTE_LV4_GLOBAL = 0x0200,
    PTE_FRAME = 0x7FFFF000
};

typedef uint32_t pt_entry_t;

void pt_entry_add_attr(pt_entry_t *entry, uint32_t attr);
void pt_entry_del_attr(pt_entry_t *entry, uint32_t attr);
void pt_entry_set_frame(pt_entry_t *entry, phys_addr frame);
phys_addr pt_entry_get_frame(pt_entry_t entry);
bool pt_entry_is_present(pt_entry_t entry);
bool pt_entry_is_writable(pt_entry_t entry);
