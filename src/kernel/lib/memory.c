#include "memory.h"

void memset(void *s, uint8_t c, size_t n){
    uint8_t *p = s;
    while(n--) *(p++) = c;
}

void memcpy(void *dest, void *src, size_t n){
    while(n--) ((uint8_t *)dest)[n] = ((uint8_t *)src)[n];
}
