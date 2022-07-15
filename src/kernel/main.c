#include <stdint.h>
#include "lib/stdio.h"
#include "hal/hal.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"
#include "drivers/serial.h"
#include "fs/vfs.h"

void __attribute__((cdecl)) kmain(uint64_t magic, uint64_t addr){
    // Clear screen
    clear_screen();

    // Initialize chip-specific hardware
    hal_initialize();

    // Initialize drivers
    timer_initialize();
    keyboard_initialize();
    
    // Initialize FS
    vfs_initialize();
    
    for(;;);
}
