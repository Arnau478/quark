#include "isr.h"
#include "../../stdio.h"

static isr_handler g_isr_handlers[256];

static const char *const g_exceptions[] = {
    "Divide by zero error",
    "Debug",
    "Non-maskable interrupt",
    "Breakpoint",
    "Overflow",
    "Bound range exceeded",
    "Invalid opcode",
    "Device not available",
    "Double fault",
    "Coprocessor segment overrun",
    "Invalid TTS",
    "Segment not present",
    "Stack-segment fault",
    "General protection fault",
    "Page fault",
    "",
    "x87 floating point exception",
    "Alignment check",
    "Machine check",
    "SIMD floating-point exception",
    "Virtualization exception",
    "Control protection exception",
    "",
    "",
    "",
    "",
    "",
    "",
    "Hypervisor injection exception",
    "VMM communication exception",
    "Security exception",
    ""
};

void i686_isr_initialize_gates();

void i686_isr_initialize(){
    i686_isr_initialize_gates();

    // Remap PIC
}

void i686_isr_handler(registers *regs){
    printf("Interrupt %i\n", regs->interrupt);
}

void i686_isr_register_handler(int interrupt, isr_handler handler){
    g_isr_handlers[interrupt] = handler;
}
