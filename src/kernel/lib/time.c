#include <stdint.h>
#include "time.h"
#include "../hal/hal.h"

void sleep(int ms){
    uint32_t ticks = ms + hal_get_tick_count();
    while(ticks > hal_get_tick_count());
}
