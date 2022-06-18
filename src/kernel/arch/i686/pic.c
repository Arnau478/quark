#include "pic.h"
#include "io.h"

void i686_pic_initialize(){
    uint8_t pic1_mask;
    uint8_t pic2_mask;

    // Save PIC masks
    pic1_mask = i686_inb(PIC1_DATA_PORT);
    pic2_mask = i686_inb(PIC2_DATA_PORT);

    // ICW1: Initialize/reset PICs
    i686_outb(PIC1_CMD_PORT, 0x11); // PIC1
    i686_outb(PIC2_CMD_PORT, 0x11); // PIC2

    // ICW2: Remap IRQs
    i686_outb(PIC1_DATA_PORT, PIC1_VEC_OFFSET); // PIC1 remapped to PIC1_VEC_OFFSET
    i686_outb(PIC2_DATA_PORT, PIC2_VEC_OFFSET); // PIC2 remapped to PIC2_VEC_OFFSET

    // ICW3: Cascade settings
    i686_outb(PIC1_DATA_PORT, 0x04); // PIC1 is told that slave PIC is at IRQ2
    i686_outb(PIC2_DATA_PORT, 0x02); // PIC2 has cascade identity 2

    // ICW4: Env info
    i686_outb(PIC1_DATA_PORT, 0x01); // PIC1 on 8086/88 mode
    i686_outb(PIC2_DATA_PORT, 0x01); // PIC2 on 8086/88 mode

    // Restore PIC masks
    i686_outb(PIC1_DATA_PORT, pic1_mask);
    i686_outb(PIC2_DATA_PORT, pic2_mask);
}
