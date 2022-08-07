#pragma once

#include <stdarg.h>

void puts(char *str);
void putc(char c);
void serial_putc(char c);
void vprintf(char *fmt, va_list args);
void printf(char *fmt, ...);
void serial_vprintf(char *fmt, va_list args);
void serial_printf(char *fmt, ...);
void clear_screen();
