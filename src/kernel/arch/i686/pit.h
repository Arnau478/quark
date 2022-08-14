#pragma once

#include <stdint.h>

void i686_pit_initialize();
uint32_t i686_pit_get_tick_count();
