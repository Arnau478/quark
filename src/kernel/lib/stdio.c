#include <stdarg.h>
#include <stdbool.h>
#include "stdio.h"
#include "../drivers/vga.h"
#include "../drivers/uart.h"

typedef void (*print_callable_fn_t)(char);

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

void serial_putc(char c){
    uart_write(COM1, c); // TODO: Add an option to decide what COM to use
}

static void printf_unsigned(print_callable_fn_t out_fn, unsigned long long num, int radix){
    char buffer[32];
    int pos = 0;

    // Convert to ASCII
    do{
        unsigned long long rem = num % radix;
        num /= radix;
        buffer[pos++] = g_HexChars[rem];
    } while(num > 0);

    while(--pos >= 0) out_fn(buffer[pos]); // Note reverse order
}

static void printf_signed(print_callable_fn_t out_fn, unsigned long long num, int radix){
    if(num < 0){
        out_fn('-');
        printf_unsigned(out_fn, -num, radix);
    }
    else printf_unsigned(out_fn, num, radix);
}

// printf() template
static void _vprintf(print_callable_fn_t out_fn, char *fmt, va_list args){
    // Variadic function arguments

    while(*fmt){
        if(*fmt == '%'){
            bool number = false;
            bool sign = false;
            int radix = 10;

            fmt++;
            switch(*fmt){
                case '%':
                    out_fn('%');
                    break;
                case 'c':
                    out_fn((char)va_arg(args, int));
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
                    printf_signed(out_fn, va_arg(args, int), radix);
                }
                else{
                    printf_unsigned(out_fn, va_arg(args, unsigned int), radix);
                }
            }

            fmt++;
        }
        else out_fn(*(fmt++));
    }
}

void vprintf(char *fmt, va_list args){
    _vprintf(putc, fmt, args);
}

void printf(char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    _vprintf(putc, fmt, args);
}

void serial_vprintf(char *fmt, va_list args){
    _vprintf(serial_putc, fmt, args);
}

void serial_printf(char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    _vprintf(serial_putc, fmt, args);
}

void clear_screen(){
    vga_fill_screen(' ', VGA_COLOR_BG_BLACK | VGA_COLOR_FG_WHITE);
    vga_set_cursor(0);
}
