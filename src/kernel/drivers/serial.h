#pragma once

#include <stdint.h>

#define COM1 (uint8_t)0x3F8
#define COM2 (uint8_t)0x2F8
#define COM3 (uint8_t)0x3E8
#define COM4 (uint8_t)0x2E8
#define COM5 (uint8_t)0x5F8
#define COM6 (uint8_t)0x4F8
#define COM7 (uint8_t)0x5E8
#define COM8 (uint8_t)0x4E8

int serial_initialize(uint8_t port);
char serial_read(uint8_t port);
void serial_write(uint8_t port, char c);
