#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "pte.h"
#include "pde.h"

typedef uint32_t virt_addr;

#define PAGES_PER_TABLE 1024
#define PAGES_PER_DIR 1024

#define PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3FF)
#define PAGE_TABLE_INDEX(x) (((x) >> 12) & 0x3FF)
#define PAGE_GET_PHYS_ADDR(x) (*(x) & ~0xFFF)

#define PTABLE_ADDR_SPACE_SIZE 0x400000
#define DTABLE_ADDR_SPACE_SIZE 0x100000000

#define PAGE_SIZE 4096

typedef struct{
    pt_entry_t entries[PAGES_PER_TABLE];
} vmm_page_table_t;

typedef struct{
    pd_entry_t entries[PAGES_PER_DIR];
} vmm_page_directory_t;

bool vmm_alloc_page(pt_entry_t *entry);
void vmm_free_page(pt_entry_t *entry);
void vmm_map_page(void *phys, void *virt);
void vmm_initialize();
