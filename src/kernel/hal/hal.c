#include "hal.h"
#include "../arch/i686/idt.h"

void hal_initialize(){
    i686_idt_initialize();
}
