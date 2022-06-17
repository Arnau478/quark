#include <stdint.h>
#include "stdio.h"

void __attribute__((cdecl)) kmain(uint64_t magic, uint64_t addr){
    printf("Hello world!\n\x1b[32m:D\x1b[0m\n");
    for(;;); // Halt here 
}
