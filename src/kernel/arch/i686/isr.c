#include <stddef.h>
#include "isr.h"
#include "../../lib/stdio.h"
#include "idt.h"
#include "io.h"
#include "pic.h"

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

    i686_pic_initialize();

    for(int i = 0; i < 256; i++){
        i686_idt_enable_gate(i);
    }
}

void __attribute__((cdecl)) i686_isr_handler(registers *regs){
    if(g_isr_handlers[regs->interrupt] != NULL){
        g_isr_handlers[regs->interrupt](regs);

        // Send EOI to PIC if necessary
        if(regs->interrupt >= PIC1_VEC_OFFSET && regs->interrupt < PIC1_VEC_OFFSET+8){
            i686_outb(PIC1_CMD_PORT, PIC_EOI);
        }
        else if(regs->interrupt >= PIC2_VEC_OFFSET && regs->interrupt < PIC2_VEC_OFFSET+8){
            i686_outb(PIC2_CMD_PORT, PIC_EOI);
        }
    }
    else if(regs->interrupt >= 32){
        printf("Unhandled interrupt %i\n", regs->interrupt);
    }
    else{
        printf("Unhandled interrupt %i %s\n", regs->interrupt, g_exceptions[regs->interrupt]);
        printf("  eax=%i ebx=%i ecx=%i edx=%i esi=%i edi=%i\n", regs->eax, regs->ebx, regs->ecx, regs->edx, regs->esi, regs->edi);
        printf("  esp=%i ebp=%i eip=%i eflags=%i cs=%i ds=%i ss=%i\n", regs->esp, regs->ebp, regs->eip, regs->eflags, regs->cs, regs->ds, regs->ss);
        printf("  interrupt=%i errorcode=%i\n", regs->interrupt, regs->error);
        printf("!!! KERNEL PANIC !!!\n");
        i686_panic();
    }
}

void i686_isr_register_handler(int interrupt, isr_handler handler){
    g_isr_handlers[interrupt] = handler;
}
