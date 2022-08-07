#pragma once

#include <stdint.h>

#define COM1 (uint16_t)0x3F8
#define COM2 (uint16_t)0x2F8
#define COM3 (uint16_t)0x3E8
#define COM4 (uint16_t)0x2E8
#define COM5 (uint16_t)0x5F8
#define COM6 (uint16_t)0x4F8
#define COM7 (uint16_t)0x5E8
#define COM8 (uint16_t)0x4E8

void uart_set_baudrate(uint16_t port, uint16_t divisor);
void uart_initialize(uint16_t port, uint16_t baudrate_div);
char uart_read(uint16_t port);
void uart_write(uint16_t port, char c);
