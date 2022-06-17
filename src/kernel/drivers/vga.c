#include "vga.h"

void set_char(int x, int y, char c){
    VGA_MEMORY[(x+y*VGA_WIDTH)*2] = c;
}

void set_color(int x, int y, uint8_t color){
    VGA_MEMORY[(x+y*VGA_WIDTH)*2+1] = color;
}
