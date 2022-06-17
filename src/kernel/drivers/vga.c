#include "vga.h"
#include "../arch/i686/io.h"

void set_char(int x, int y, char c){
    VGA_MEMORY[(x+y*VGA_WIDTH)*2] = c;
}

void set_color(int x, int y, uint8_t color){
    VGA_MEMORY[(x+y*VGA_WIDTH)*2+1] = color;
}

void set_cursor(int offset){
    i686_outb(VGA_PORT_CTRL, 14);
    i686_outb(VGA_PORT_DATA, (uint8_t)(offset >> 8));
    i686_outb(VGA_PORT_CTRL, 15);
    i686_outb(VGA_PORT_DATA, (uint8_t)(offset & 0xff));
}

int get_cursor(){
    i686_outb(VGA_PORT_CTRL, 14);
    int offset = i686_inb(VGA_PORT_DATA) << 8; // High byte
    i686_outb(VGA_PORT_CTRL, 15);
    offset += i686_inb(VGA_PORT_DATA); // Low byte
    return offset;
}
