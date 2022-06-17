#include <stdint.h>
#include "drivers/vga.h"

void __attribute__((cdecl)) kmain(uint64_t magic, uint64_t addr){
    // Print a light cyan 'X' over green on the top left corner
    set_char(0, 0, 'X');
    set_color(0, 0, VGA_COLOR_BG_GREEN | VGA_COLOR_FG_LIGHT_CYAN);
    set_cursor(1);
    for(;;); // Halt here 
}
