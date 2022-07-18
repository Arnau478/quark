#include <stdint.h>
#include "pmm.h"
#include "../lib/memory.h"

static uint32_t g_pmm_memory_size = 0;
static uint32_t g_pmm_used_blocks = 0;
static uint32_t g_pmm_max_blocks = 0;
static uint32_t *g_pmm_memory_map = 0;

static inline void pmm_map_set(int bit){
    g_pmm_memory_map[bit / 32] |= (1 << (bit % 32));
}

static inline void pmm_map_unset(int bit){
    g_pmm_memory_map[bit / 32] &= ~(1 << (bit % 32));
}

static inline bool pmm_map_get(int bit){
    return g_pmm_memory_map[bit / 32] & (1 << (bit % 32));
}

int pmm_map_first_free(){
    for(uint32_t i = 0; i < pmm_get_block_count() / 32; i++){
        if(g_pmm_memory_map[i] != 0xffffffff){
            for(int j = 0; j < 32; j++){
                if(!(g_pmm_memory_map[i] & (1 << j))){
                    return i*4*8+j;
                }
            }
        }
    }
    return -1;
}

int pmm_map_first_free_s(size_t size){
    if(size == 0) return -1;
    if(size == 1) return pmm_map_first_free();

    for(uint32_t i = 0; i < pmm_get_block_count() / 32; i++){
        if(g_pmm_memory_map[i] != 0xffffffff){
            for(int j = 0; j < 32; j++){
                int bit = 1 << j;
                if(!(g_pmm_memory_map[i] & bit)){
                    int start_bit = i*32;
                    start_bit+=bit;

                    uint32_t free = 0;
                    for(uint32_t count = 0; count <= size; count++){
                        if(!pmm_map_get(start_bit+count)) free++;
                        if(free == size) return i*4*8+j;
                    }
                }
            }
        }
    }
    return -1;
}

void pmm_initialize(size_t mem_size, phys_addr bitmap){
    g_pmm_memory_size = mem_size;
    g_pmm_memory_map = (uint32_t *)bitmap;
    g_pmm_max_blocks = (pmm_get_memory_size()*1024) / PMM_BLOCK_SIZE;
    g_pmm_used_blocks = g_pmm_max_blocks;

    // FIXME
    memset(g_pmm_memory_map, 0xFF, pmm_get_block_count() / PMM_BLOCKS_PER_BYTE);
}

void pmm_init_region(phys_addr base, size_t size){
    int align = base / PMM_BLOCK_SIZE;
    int blocks = size / PMM_BLOCK_SIZE;

    for(; blocks >= 0; blocks--){
        pmm_map_unset(align++);
        g_pmm_used_blocks--;
    }

    pmm_map_set(0); // First block always set
}

void pmm_deinit_region(phys_addr base, size_t size){
    int align = base / PMM_BLOCK_SIZE;
    int blocks = size / PMM_BLOCK_SIZE;

    for(; blocks >= 0; blocks--){
        pmm_map_set(align++);
        g_pmm_used_blocks++;
    }

    pmm_map_set(0); // First block always set
}

void *pmm_alloc_block(){
    if(pmm_get_free_block_count() <= 0) return 0; // Out of memory

    int frame = pmm_map_first_free();
    if(frame == -1) return 0; // Out of memory

    pmm_map_set(frame);

    phys_addr addr = frame * PMM_BLOCK_SIZE;
    g_pmm_used_blocks++;
    
    return (void *)addr;
}

void pmm_free_block(void *p){
    phys_addr addr = (phys_addr)p;
    int frame = addr / PMM_BLOCK_SIZE;

    pmm_map_unset(frame);

    g_pmm_used_blocks--;
}

void *pmm_alloc_blocks(size_t size){
    if(pmm_get_free_block_count() <= size) return 0; // Out of memory

    int frame = pmm_map_first_free_s(size);
    if(frame == -1) return 0; // Out of memory

    for(uint32_t i = 0; i < size; i++) pmm_map_set(frame+i);

    phys_addr addr = frame * PMM_BLOCK_SIZE;
    g_pmm_used_blocks += size;
    
    return (void *)addr;
}

void pmm_free_blocks(void *p, size_t size){
    phys_addr addr = (phys_addr)p;
    int frame = addr / PMM_BLOCK_SIZE;

    for(uint32_t i = 0; i < size; i++) pmm_map_unset(frame+i);

    g_pmm_used_blocks -= size;
}

size_t pmm_get_memory_size(){
    return g_pmm_memory_size;
}

uint32_t pmm_get_block_count(){
    return g_pmm_max_blocks;
}

uint32_t pmm_get_used_block_count(){
    return g_pmm_used_blocks;
}

uint32_t pmm_get_free_block_count(){
    return g_pmm_max_blocks - g_pmm_used_blocks;
}
