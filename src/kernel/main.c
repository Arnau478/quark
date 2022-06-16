#include <stdint.h>
#include "arch/i686/io.h"

void __attribute__((cdecl)) kmain(uint64_t magic, uint64_t addr){
    char *mem = (char *)0xB8000; // Screen memory address (when on text mode)
    for(int i = 0; 1; i++) mem[i] = 88; // Fill screen with Blue 'X' characters over pink background 
}
