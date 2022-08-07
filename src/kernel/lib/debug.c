#include "debug.h"
#include "stdio.h"

void debug_printf(char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    debug_vprintf(fmt, args);
}

void debug_vprintf(char *fmt, va_list args){
    serial_printf("\x1b[34m");
    serial_vprintf(fmt, args);
    serial_printf("\x1b[0m");
}
