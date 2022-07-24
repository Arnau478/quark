#pragma once

#include <stdint.h>
#include "pmm.h"

enum i686_PTE_PAGE_FLAGS{
    i686_PTE_PRESENT = 0x0001,
    i686_PTE_WRITABLE = 0x0002,
    i686_PTE_USER = 0x0004,
    i686_PTE_WRITETHROUGH = 0x0008,
    i686_PTE_NOT_CACHEABLE = 0x0010,
    i686_PTE_ACCESSED = 0x0020,
    i686_PTE_DIRTY = 0x0040,
    i686_PTE_PAT = 0x0080,
    i686_PTE_CPU_GLOBAL = 0x0100,
    i686_PTE_LV4_GLOBAL = 0x0200,
    i686_PTE_FRAME = 0x7FFFF000
};

typedef uint32_t i686_pt_entry_t;

void i686_pt_entry_add_attr(i686_pt_entry_t *entry, uint32_t attr);
void i686_pt_entry_del_attr(i686_pt_entry_t *entry, uint32_t attr);
void i686_pt_entry_set_frame(i686_pt_entry_t *entry, i686_phys_addr frame);
i686_phys_addr i686_pt_entry_get_frame(i686_pt_entry_t entry);
bool i686_pt_entry_is_present(i686_pt_entry_t entry);
bool i686_pt_entry_is_writable(i686_pt_entry_t entry);
