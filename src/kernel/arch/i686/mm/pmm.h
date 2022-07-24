#pragma once

#include <stdbool.h>
#include <stddef.h>

#define i686_PMM_BLOCKS_PER_BYTE 8
#define i686_PMM_BLOCK_SIZE 4096
#define i686_PMM_BLOCK_ALIGN PMM_BLOCK_SIZE

typedef uint32_t i686_phys_addr;

int i686_pmm_map_first_free();
int i686_pmm_map_first_free_s(size_t size);
void i686_pmm_initialize(size_t mem_size, i686_phys_addr bitmap);
void i686_pmm_init_region(i686_phys_addr base, size_t size);
void i686_pmm_deinit_region(i686_phys_addr base, size_t size);
void *i686_pmm_alloc_block();
void i686_pmm_free_block(void *p);
void *i686_pmm_alloc_blocks(size_t size);
void i686_pmm_free_blocks(void *p, size_t size);
size_t i686_pmm_get_memory_size();
uint32_t i686_pmm_get_block_count();
uint32_t i686_pmm_get_used_block_count();
uint32_t i686_pmm_get_free_block_count();
void __attribute__((cdecl)) i686_pmm_paging_enable(bool enabled);
bool __attribute__((cdecl)) i686_pmm_is_paging();
void __attribute__((cdecl)) i686_pmm_load_pdbr(i686_phys_addr addr);
i686_phys_addr __attribute__((cdecl)) i686_pmm_get_pdbr();
