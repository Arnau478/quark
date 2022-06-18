#pragma once

#include <stdint.h>

#define IRQ(n) ((n)+32)

typedef struct{
    uint32_t ds;
    uint32_t edi, esi, ebp, kern_esp, ebx, edx, ecx, eax;
    uint32_t interrupt, error;
    uint32_t eip, cs, eflags, esp, ss;
} __attribute__((packed)) registers;

typedef void (*isr_handler)(registers regs);

void i686_isr_initialize();
void i686_isr_register_handler(int interrupt, isr_handler handler);
