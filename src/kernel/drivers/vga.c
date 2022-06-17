#include "vga.h"
#include "../arch/i686/io.h"

static uint8_t current_color = VGA_COLOR_DEFAULT;

void vga_set_char(int x, int y, char c){
    VGA_MEMORY[(x+y*VGA_WIDTH)*2] = c;
}

void vga_set_color(int x, int y, uint8_t color){
    VGA_MEMORY[(x+y*VGA_WIDTH)*2+1] = color;
}

void vga_set_cursor(int offset){
    i686_outb(VGA_PORT_CTRL, 14);
    i686_outb(VGA_PORT_DATA, (uint8_t)(offset >> 8));
    i686_outb(VGA_PORT_CTRL, 15);
    i686_outb(VGA_PORT_DATA, (uint8_t)(offset & 0xff));
}

int vga_get_cursor(){
    i686_outb(VGA_PORT_CTRL, 14);
    int offset = i686_inb(VGA_PORT_DATA) << 8; // High byte
    i686_outb(VGA_PORT_CTRL, 15);
    offset += i686_inb(VGA_PORT_DATA); // Low byte
    return offset;
}

static int get_offset_y(int offset){
    return offset / VGA_WIDTH;
}

static int get_offset_x(int offset){
    return (offset - (get_offset_y(offset)*VGA_WIDTH));
}

int vga_print_char(char c, int x, int y){
    if(x >= VGA_WIDTH || y >= VGA_HEIGHT){ // Incorrect coords
        VGA_MEMORY[2*VGA_WIDTH*VGA_HEIGHT-2] = 'E';
        VGA_MEMORY[2*VGA_WIDTH*VGA_HEIGHT-1] = VGA_COLOR_BG_RED || VGA_COLOR_FG_BLACK;
        return y*VGA_WIDTH+x;
    }

    int offset;
    if(x >= 0 && y >= 0) offset = y*VGA_WIDTH+x;
    else offset = vga_get_cursor();

    if(c == '\n'){
        y = get_offset_y(offset);
        offset = (y+1)*VGA_WIDTH;
    }
    else if(c == '\b'){
        VGA_MEMORY[offset*2] = ' ';
        VGA_MEMORY[offset*2+1] = current_color;
    }
    else{
        VGA_MEMORY[offset*2] = c;
        VGA_MEMORY[offset*2+1] = current_color;
        offset++;
    }

    // TODO: Scroll
    
    vga_set_cursor(offset);
    return offset;
}

void vga_print_string_at(char *str, int x, int y){
    int offset;
    if(x >= 0 && y >= 0){
        offset = y*VGA_WIDTH+x;
    }
    else{
        offset = vga_get_cursor();
        x = get_offset_x(offset);
        y = get_offset_y(offset);
    }

    while(*str){
        if(*str == '\x1b'){
            str++;
            if(*str != '[') continue;
            str++;
            int ansi_col = 0;
            while(*str >= '0' && *str <= '9'){
                ansi_col *= 10;
                ansi_col += *str - '0';
                str++;
            }
            if(*str != 'm') continue;
            str++;
            if(ansi_col == 0) current_color = VGA_COLOR_DEFAULT;
            else if(ansi_col >= 30 && ansi_col <= 37){
                switch (ansi_col)
                {
                    case 30: current_color = (current_color & 0xf0) | VGA_COLOR_FG_BLACK; break;
                    case 31: current_color = (current_color & 0xf0) | VGA_COLOR_FG_RED; break;
                    case 32: current_color = (current_color & 0xf0) | VGA_COLOR_FG_GREEN; break;
                    case 33: current_color = (current_color & 0xf0) | VGA_COLOR_FG_ORANGE; break;
                    case 34: current_color = (current_color & 0xf0) | VGA_COLOR_FG_BLUE; break;
                    case 35: current_color = (current_color & 0xf0) | VGA_COLOR_FG_PINK; break;
                    case 36: current_color = (current_color & 0xf0) | VGA_COLOR_FG_CYAN; break;
                    case 37: current_color = (current_color & 0xf0) | VGA_COLOR_FG_WHITE; break;
                }
            }
        }
        else{
            offset = vga_print_char(*(str++), x, y);
            x = get_offset_x(offset);
            y = get_offset_y(offset);
        }
    }
}

void vga_print_string(char *str){
    vga_print_string_at(str, -1, -1);
}
