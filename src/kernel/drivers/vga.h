#pragma once

#include <stdint.h>

#define VGA_MEMORY ((char *)0xB8000)

#define VGA_COLOR_DEFAULT (VGA_COLOR_BG_BLACK | VGA_COLOR_FG_WHITE)

#define VGA_COLOR_FG_BLACK 0x00
#define VGA_COLOR_FG_BLUE 0x01
#define VGA_COLOR_FG_GREEN 0x02
#define VGA_COLOR_FG_CYAN 0x03
#define VGA_COLOR_FG_RED 0x04
#define VGA_COLOR_FG_PINK 0x05
#define VGA_COLOR_FG_ORANGE 0x06
#define VGA_COLOR_FG_WHITE 0x07
#define VGA_COLOR_FG_LIGHT_BLACK 0x08
#define VGA_COLOR_FG_LIGHT_BLUE 0x09
#define VGA_COLOR_FG_LIGHT_GREEN 0x0A
#define VGA_COLOR_FG_LIGHT_CYAN 0x0B
#define VGA_COLOR_FG_LIGHT_RED 0x0C
#define VGA_COLOR_FG_LIGHT_PINK 0x0D
#define VGA_COLOR_FG_LIGHT_ORANGE 0x0E
#define VGA_COLOR_FG_LIGHT_WHITE 0x0F

#define VGA_COLOR_BG_BLACK 0x00
#define VGA_COLOR_BG_BLUE 0x10
#define VGA_COLOR_BG_GREEN 0x20
#define VGA_COLOR_BG_CYAN 0x30
#define VGA_COLOR_BG_RED 0x40
#define VGA_COLOR_BG_PINK 0x50
#define VGA_COLOR_BG_ORANGE 0x60
#define VGA_COLOR_BG_WHITE 0x70
#define VGA_COLOR_BG_LIGHT_BLACK 0x80
#define VGA_COLOR_BG_LIGHT_BLUE 0x90
#define VGA_COLOR_BG_LIGHT_GREEN 0xA0
#define VGA_COLOR_BG_LIGHT_CYAN 0xB0
#define VGA_COLOR_BG_LIGHT_RED 0xC0
#define VGA_COLOR_BG_LIGHT_PINK 0xD0
#define VGA_COLOR_BG_LIGHT_ORANGE 0xE0
#define VGA_COLOR_BG_LIGHT_WHITE 0xF0

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_PORT_CTRL 0x3D4
#define VGA_PORT_DATA 0x3D5

void vga_set_char(int x, int y, char c);
void vga_set_color(int x, int y, uint8_t color);
void vga_set_cursor(int offset);
int vga_get_cursor();
int vga_print_char(char c, int x, int y);
void vga_print_string_at(char *str, int x, int y);
void vga_print_string(char *str);
void vga_fill_screen(char c, uint8_t color);
