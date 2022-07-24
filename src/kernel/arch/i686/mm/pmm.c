#include <stdint.h>
#include "pmm.h"
#include "../../../lib/memory.h"

static uint32_t g_pmm_memory_size = 0;
static uint32_t g_pmm_used_blocks = 0;
static uint32_t g_pmm_max_blocks = 0;
static uint32_t *g_pmm_memory_map = 0;

static inline void i686_pmm_map_set(int bit){
    g_pmm_memory_map[bit / 32] |= (1 << (bit % 32));
}

static inline void i686_pmm_map_unset(int bit){
    g_pmm_memory_map[bit / 32] &= ~(1 << (bit % 32));
}

static inline bool i686_pmm_map_get(int bit){
    return g_pmm_memory_map[bit / 32] & (1 << (bit % 32));
}

int i686_pmm_map_first_free(){
    for(uint32_t i = 0; i < i686_pmm_get_block_count() / 32; i++){
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

int i686_pmm_map_first_free_s(size_t size){
    if(size == 0) return -1;
    if(size == 1) return i686_pmm_map_first_free();

    for(uint32_t i = 0; i < i686_pmm_get_block_count() / 32; i++){
        if(g_pmm_memory_map[i] != 0xffffffff){
            for(int j = 0; j < 32; j++){
                int bit = 1 << j;
                if(!(g_pmm_memory_map[i] & bit)){
                    int start_bit = i*32;
                    start_bit+=bit;

                    uint32_t free = 0;
                    for(uint32_t count = 0; count <= size; count++){
                        if(!i686_pmm_map_get(start_bit+count)) free++;
                        if(free == size) return i*4*8+j;
                    }
                }
            }
        }
    }
    return -1;
}

void i686_pmm_initialize(size_t mem_size, i686_phys_addr bitmap){
    g_pmm_memory_size = mem_size;
    g_pmm_memory_map = (uint32_t *)bitmap;
    g_pmm_max_blocks = (i686_pmm_get_memory_size()*1024) / i686_PMM_BLOCK_SIZE;
    g_pmm_used_blocks = g_pmm_max_blocks;

    memset(g_pmm_memory_map, 0xFF, i686_pmm_get_block_count() / i686_PMM_BLOCKS_PER_BYTE);
}

void i686_pmm_init_region(i686_phys_addr base, size_t size){
    int align = base / i686_PMM_BLOCK_SIZE;
    int blocks = size / i686_PMM_BLOCK_SIZE;

    for(; blocks >= 0; blocks--){
        i686_pmm_map_unset(align++);
        g_pmm_used_blocks--;
    }

    i686_pmm_map_set(0); // First block always set
}

void i686_pmm_deinit_region(i686_phys_addr base, size_t size){
    int align = base / i686_PMM_BLOCK_SIZE;
    int blocks = size / i686_PMM_BLOCK_SIZE;

    for(; blocks >= 0; blocks--){
        i686_pmm_map_set(align++);
        g_pmm_used_blocks++;
    }

    i686_pmm_map_set(0); // First block always set
}

void *i686_pmm_alloc_block(){
    if(i686_pmm_get_free_block_count() <= 0) return 0; // Out of memory

    int frame = i686_pmm_map_first_free();
    if(frame == -1) return 0; // Out of memory

    i686_pmm_map_set(frame);

    i686_phys_addr addr = frame * i686_PMM_BLOCK_SIZE;
    g_pmm_used_blocks++;
    
    return (void *)addr;
}

void i686_pmm_free_block(void *p){
    i686_phys_addr addr = (i686_phys_addr)p;
    int frame = addr / i686_PMM_BLOCK_SIZE;

    i686_pmm_map_unset(frame);

    g_pmm_used_blocks--;
}

void *i686_pmm_alloc_blocks(size_t size){
    if(i686_pmm_get_free_block_count() <= size) return 0; // Out of memory

    int frame = i686_pmm_map_first_free_s(size);
    if(frame == -1) return 0; // Out of memory

    for(uint32_t i = 0; i < size; i++) i686_pmm_map_set(frame+i);

    i686_phys_addr addr = frame * i686_PMM_BLOCK_SIZE;
    g_pmm_used_blocks += size;
    
    return (void *)addr;
}

void i686_pmm_free_blocks(void *p, size_t size){
    i686_phys_addr addr = (i686_phys_addr)p;
    int frame = addr / i686_PMM_BLOCK_SIZE;

    for(uint32_t i = 0; i < size; i++) i686_pmm_map_unset(frame+i);

    g_pmm_used_blocks -= size;
}

size_t i686_pmm_get_memory_size(){
    return g_pmm_memory_size;
}

uint32_t i686_pmm_get_block_count(){
    return g_pmm_max_blocks;
}

uint32_t i686_pmm_get_used_block_count(){
    return g_pmm_used_blocks;
}

uint32_t i686_pmm_get_free_block_count(){
    return g_pmm_max_blocks - g_pmm_used_blocks;
}
