#include "timer.h"
#include "../arch/i686/isr.h"
#include "../stdio.h"

static void timer_handler(registers *regs){
    printf("TICK\n");
}

void timer_initialize(){
    i686_isr_register_handler(IRQ(0), timer_handler);
}
