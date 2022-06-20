#include <stdarg.h>
#include <stdbool.h>
#include "stdio.h"
#include "../drivers/vga.h"

static char g_HexChars[] = "0123456789abcdef";

void puts(char *str){
    vga_print_string(str);
}

void putc(char c){
    char str[2];
    str[0] = c;
    str[1] = '\0';
    vga_print_string(str);
}

static void printf_unsigned(unsigned long long num, int radix){
    char buffer[32];
    int pos = 0;

    // Convert to ASCII
    do{
        unsigned long long rem = num % radix;
        num /= radix;
        buffer[pos++] = g_HexChars[rem];
    } while(num > 0);

    while(--pos >= 0) putc(buffer[pos]); // Note reverse order
}

static void printf_signed(unsigned long long num, int radix){
    if(num < 0){
        putc('-');
        printf_unsigned(-num, radix);
    }
    else printf_unsigned(num, radix);
}

void printf(char *fmt, ...){
    // Variadic function arguments
    va_list args;
    va_start(args, fmt);

    while(*fmt){
        if(*fmt == '%'){
            bool number = false;
            bool sign = false;
            int radix = 10;

            fmt++;
            switch(*fmt){
                case '%':
                    putc('%');
                    break;
                case 'c':
                    putc((char)va_arg(args, int));
                    break;
                case 's':
                    puts(va_arg(args, char *));
                    break;
                case 'd':
                case 'i':
                    number = true;
                    radix = 10;
                    sign = true;
                    break;
                case 'u':
                    number = true;
                    radix = 10;
                    sign = false;
                    break;
                case 'X':
                case 'x':
                case 'p':
                    number = true;
                    radix = 16;
                    sign = false;
                    break;
                case 'o':
                    number = true;
                    radix = 8;
                    sign = false;
                    break;
                default: break;
            }

            // TODO: Implement length modifiers
            if(number){
                if(sign){
                    printf_signed(va_arg(args, int), radix);
                }
                else{
                    printf_unsigned(va_arg(args, unsigned int), radix);
                }
            }

            fmt++;
        }
        else putc(*(fmt++));
    }
}

void clear_screen(){
    vga_fill_screen(' ', VGA_COLOR_BG_BLACK | VGA_COLOR_FG_WHITE);
    vga_set_cursor(0);
}
