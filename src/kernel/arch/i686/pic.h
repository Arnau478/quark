#pragma once

#define PIC1_CMD_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_CMD_PORT 0xA0
#define PIC2_DATA_PORT 0xA1

#define PIC1_VEC_OFFSET 0x20
#define PIC2_VEC_OFFSET 0x28

#define PIC_EOI 0x20

void i686_pic_initialize();
