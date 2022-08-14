#include "pit.h"
#include "isr.h"
#include "../../lib/stdio.h"
#include "../../lib/debug.h"

static volatile uint32_t g_tick_count = 0;

static void i686_pit_handler(registers *regs){
    g_tick_count++;
}

void i686_pit_initialize(){
    debug_printf("[PIT] Initializing\n");
    i686_isr_register_handler(IRQ(0), i686_pit_handler);
}

uint32_t i686_pit_get_tick_count(){
    return g_tick_count;
}
