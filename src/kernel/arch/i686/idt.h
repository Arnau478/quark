#pragma once

#include <stdint.h>

typedef enum{
    IDT_FLAG_GATE_TASK = 0x5,
    IDT_FLAG_GATE_16BIT_INT = 0x6,
    IDT_FLAG_GATE_16BIT_TRAP = 0x7,
    IDT_FLAG_GATE_32BIT_INT = 0xE,
    IDT_FLAG_GATE_32BIT_TRAP = 0xF,

    IDT_FLAG_RING0 = (0 << 5),
    IDT_FLAG_RING1 = (1 << 5),
    IDT_FLAG_RING2 = (2 << 5),
    IDT_FLAG_RING3 = (3 << 5),

    IDT_FLAG_PRESENT = 0x80,
} idt_flags;

void i686_idt_initialize();
void i686_idt_enable_gate(int interrupt);
void i686_idt_disable_gate(int interrupt);
void i686_idt_set_gate(int interrupt, void *base, uint16_t segment_descriptor, uint8_t flags);
