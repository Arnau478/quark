#pragma once

#include <stdbool.h>
#include <stddef.h>

#define PMM_BLOCKS_PER_BYTE 8
#define PMM_BLOCK_SIZE 4096
#define PMM_BLOCK_ALIGN PMM_BLOCK_SIZE

typedef uint32_t phys_addr;

int pmm_map_first_free();
int pmm_map_first_free_s(size_t size);
void pmm_initialize(size_t mem_size, phys_addr bitmap);
void pmm_init_region(phys_addr base, size_t size);
void pmm_deinit_region(phys_addr base, size_t size);
void *pmm_alloc_block();
void pmm_free_block(void *p);
void *pmm_alloc_blocks(size_t size);
void pmm_free_blocks(void *p, size_t size);
size_t pmm_get_memory_size();
uint32_t pmm_get_block_count();
uint32_t pmm_get_used_block_count();
uint32_t pmm_get_free_block_count();
void __attribute__((cdecl)) pmm_paging_enable(bool enabled);
bool __attribute__((cdecl)) pmm_is_paging();
void __attribute__((cdecl)) pmm_load_pdbr(phys_addr addr);
phys_addr __attribute__((cdecl)) pmm_get_pdbr();
