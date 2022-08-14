#include "hal.h"
#include "../arch/i686/gdt.h"
#include "../arch/i686/idt.h"
#include "../arch/i686/isr.h"
#include "../arch/i686/pit.h"

void hal_initialize(){
    i686_gdt_initialize();
    i686_idt_initialize();
    i686_isr_initialize();
    i686_pit_initialize();
}

uint32_t hal_get_tick_count(){
    return i686_pit_get_tick_count();
}
