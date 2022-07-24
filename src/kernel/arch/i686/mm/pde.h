#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "pmm.h"

enum i686_PDE_PAGE_FLAGS{
    i686_PDE_PRESENT = 0x0001,
    i686_PDE_WRITABLE = 0x0002,
    i686_PDE_USER = 0x0004,
    i686_PDE_WRITETHROUGH = 0x0008,
    i686_PDE_CACHE_DISABLED = 0x0010,
    i686_PDE_ACCESSED = 0x0020,
    i686_PDE_DIRTY = 0x0040,
    i686_PDE_4MB = 0x0080,
    i686_PDE_CPU_GLOBAL = 0x0100,
    i686_PDE_LV4_GLOBAL = 0x0200,
    i686_PDE_FRAME = 0x7FFFF000,
};

typedef uint32_t i686_pd_entry_t;

void i686_pd_entry_add_attr(i686_pd_entry_t *entry, uint32_t attr);
void i686_pd_entry_del_attr(i686_pd_entry_t *entry, uint32_t attr);
void i686_pd_entry_set_frame(i686_pd_entry_t *entry, i686_phys_addr frame);
i686_phys_addr i686_pd_entry_get_frame(i686_pd_entry_t entry);
bool i686_pd_entry_is_present(i686_pd_entry_t entry);
bool i686_pd_entry_is_user(i686_pd_entry_t entry);
bool i686_pd_entry_is_4mb(i686_pd_entry_t entry);
bool i686_pd_entry_is_writable(i686_pd_entry_t entry);
