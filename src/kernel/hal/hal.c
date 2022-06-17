#include "hal.h"
#include "../arch/i686/gdt.h"
#include "../arch/i686/idt.h"

void hal_initialize(){
    i686_gdt_initialize();
    i686_idt_initialize();
}
