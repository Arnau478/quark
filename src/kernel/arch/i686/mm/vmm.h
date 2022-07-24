#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "pte.h"
#include "pde.h"

typedef uint32_t i686_virt_addr;

#define i686_PAGES_PER_TABLE 1024
#define i686_PAGES_PER_DIR 1024

#define i686_PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3FF)
#define i686_PAGE_TABLE_INDEX(x) (((x) >> 12) & 0x3FF)
#define i686_PAGE_GET_PHYS_ADDR(x) (*(x) & ~0xFFF)

#define i686_PTABLE_ADDR_SPACE_SIZE 0x400000
#define i686_DTABLE_ADDR_SPACE_SIZE 0x100000000

#define i686_PAGE_SIZE 4096

typedef struct{
    i686_pt_entry_t entries[i686_PAGES_PER_TABLE];
} i686_vmm_page_table_t;

typedef struct{
    i686_pd_entry_t entries[i686_PAGES_PER_DIR];
} i686_vmm_page_directory_t;

bool i686_vmm_alloc_page(i686_pt_entry_t *entry);
void i686_vmm_free_page(i686_pt_entry_t *entry);
void i686_vmm_map_page(void *phys, void *virt);
void i686_vmm_initialize();
