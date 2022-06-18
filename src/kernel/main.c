#include <stdint.h>
#include "stdio.h"
#include "hal/hal.h"
#include "drivers/timer.h"

void __attribute__((cdecl)) kmain(uint64_t magic, uint64_t addr){
    hal_initialize();
    timer_initialize();
    
    puts("\x1b[33mWARNING\x1b[0m");
    printf(": amazing %s ahead!\n", "math");
    printf("%i+%i=%i\n", 1, 1, 2);
    for(;;);
}
