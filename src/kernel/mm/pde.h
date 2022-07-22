#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "pmm.h"

enum PDE_PAGE_FLAGS{
    PDE_PRESENT = 0x0001,
    PDE_WRITABLE = 0x0002,
    PDE_USER = 0x0004,
    PDE_WRITETHROUGH = 0x0008,
    PDE_CACHE_DISABLED = 0x0010,
    PDE_ACCESSED = 0x0020,
    PDE_DIRTY = 0x0040,
    PDE_4MB = 0x0080,
    PDE_CPU_GLOBAL = 0x0100,
    PDE_LV4_GLOBAL = 0x0200,
    PDE_FRAME = 0x7FFFF000,
};

typedef uint32_t pd_entry_t;

void pd_entry_add_attr(pd_entry_t *entry, uint32_t attr);
void pd_entry_del_attr(pd_entry_t *entry, uint32_t attr);
void pd_entry_set_frame(pd_entry_t *entry, phys_addr frame);
phys_addr pd_entry_get_frame(pd_entry_t entry);
bool pd_entry_is_present(pd_entry_t entry);
bool pd_entry_is_user(pd_entry_t entry);
bool pd_entry_is_4mb(pd_entry_t entry);
bool pd_entry_is_writable(pd_entry_t entry);
