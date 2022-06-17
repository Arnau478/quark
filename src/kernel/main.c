#include <stdint.h>
#include "drivers/vga.h"

void __attribute__((cdecl)) kmain(uint64_t magic, uint64_t addr){
    print_string("Hello world!\n:D");
    for(;;); // Halt here 
}
