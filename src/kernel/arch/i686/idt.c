#include "idt.h"
#include "../../lib/binary.h"

typedef struct{
    uint16_t base_low;
    uint16_t segment_selector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed)) idt_entry;

typedef struct{
    uint16_t limit;
    idt_entry *ptr;
} __attribute__((packed)) idt_descriptor;

idt_entry g_idt[256];

idt_descriptor g_idt_descriptor = {sizeof(g_idt) - 1, g_idt};

void __attribute__((cdecl)) i686_idt_load(idt_descriptor *descriptor);

void i686_idt_set_gate(int interrupt, void *base, uint16_t segment_descriptor, uint8_t flags){
    g_idt[interrupt].base_low = ((uint32_t)base) & 0xFFFF;
    g_idt[interrupt].segment_selector = segment_descriptor;
    g_idt[interrupt].reserved = 0;
    g_idt[interrupt].flags = flags;
    g_idt[interrupt].base_high = ((uint32_t)base >> 16) & 0xFFFF;
}

void i686_idt_enable_gate(int interrupt){
    FLAG_SET(g_idt[interrupt].flags, IDT_FLAG_PRESENT);
}

void i686_idt_disable_gate(int interrupt){
    FLAG_UNSET(g_idt[interrupt].flags, IDT_FLAG_PRESENT);
}

void i686_idt_initialize(){
    i686_idt_load(&g_idt_descriptor);
}
