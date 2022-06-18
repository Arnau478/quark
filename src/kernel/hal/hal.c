#include "hal.h"
#include "../arch/i686/gdt.h"
#include "../arch/i686/idt.h"
#include "../arch/i686/isr.h"

void hal_initialize(){
    i686_gdt_initialize();
    i686_idt_initialize();
    i686_isr_initialize();
}
