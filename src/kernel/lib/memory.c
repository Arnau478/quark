#include <stdbool.h>
#include <stdint.h>
#include "memory.h"

static void *g_free_memory = ALLOC_START;

void *kmalloc(size_t size){
    void *ptr = g_free_memory;
    g_free_memory += size;
    return ptr;
}

void *kcalloc(size_t count, size_t size){
    void *ptr = g_free_memory;
    size *= count;
    g_free_memory += size;
    for(int i = 0; i < size; i++){
        ((uint8_t *)ptr)[i] = 0;
    }
    return ptr;
}