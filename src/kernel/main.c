#include <stdint.h>
#include "lib/stdio.h"
#include "hal/hal.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"

void __attribute__((cdecl)) kmain(uint64_t magic, uint64_t addr){
    hal_initialize();
    timer_initialize();
    keyboard_initialize();
    
    clear_screen();
    for(;;);
}
