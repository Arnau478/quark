#pragma once

#include <stdarg.h>

void debug_printf(char *fmt, ...);
void debug_vprintf(char *fmt, va_list args);
