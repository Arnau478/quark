#include "timer.h"
#include "../arch/i686/isr.h"
#include "../lib/stdio.h"
#include "../lib/debug.h"

static void timer_handler(registers *regs){
    //printf("TICK\n");
}

void timer_initialize(){
    debug_printf("[TIMER] Initializing PIT\n");
    i686_isr_register_handler(IRQ(0), timer_handler);
}
