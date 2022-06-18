#include <stdint.h>
#include "gdt.h"

typedef struct{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags_limit_high;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry;

typedef struct{
    uint16_t limit;
    gdt_entry *ptr;
} __attribute__((packed)) gdt_descriptor;

typedef enum{
    GDT_ACCESS_CODE_READABLE = 0x02,
    GDT_ACCESS_DATA_WRITEABLE = 0x02,
    
    GDT_ACCESS_CODE_CONFORMING = 0x04,
    GDT_ACCESS_DATA_DIRECTION_NORMAL = 0x00,
    GDT_ACCESS_DATA_DIRECTION_DOWN = 0x04,

    GDT_ACCESS_DATA_SEGMENT = 0x10,
    GDT_ACCESS_CODE_SEGMENT = 0x18,

    GDT_ACCESS_DESCRIPTOR_TSS = 0x00,
    
    GDT_ACCESS_RING0 = 0x00,
    GDT_ACCESS_RING1 = 0x20,
    GDT_ACCESS_RING2 = 0x40,
    GDT_ACCESS_RING3 = 0x60,

    GDT_ACCESS_PRESENT = 0x80,
} GDT_ACCESS;

typedef enum{
    GDT_FLAG_64BIT = 0x20,
    GDT_FLAG_32BIT = 0x40,
    GDT_FLAG_16BIT = 0x00,

    GDT_FLAG_GRANULARITY_1B = 0x00,
    GDT_FLAG_GRANULARITY_4K = 0x80,
} GDT_FLAGS;

// Helpful macros
#define GDT_LIMIT_LOW(limit) ((limit) & 0xFFFF)
#define GDT_BASE_LOW(base) ((base) & 0xFFFF)
#define GDT_BASE_MIDDLE(base) (((base) >> 16) & 0xFF)
#define GDT_FLAGS_LIMIT_HIGH(limit, flags) ((((limit) >> 16) & 0xF) | ((flags) & 0xF0))
#define GDT_BASE_HIGH(base) (((base) >> 24) & 0xFF)

#define GDT_ENTRY(base, limit, access, flags) { \
    GDT_LIMIT_LOW(limit), \
    GDT_BASE_LOW(base), \
    GDT_BASE_MIDDLE(base), \
    access, \
    GDT_FLAGS_LIMIT_HIGH(limit, flags), \
    GDT_BASE_HIGH(base), \
}

static gdt_entry g_gdt[] = {
    // Null descriptor
    GDT_ENTRY(0, 0, 0, 0),

    // Kernel 32-bit code segment
    GDT_ENTRY(
        0,
        0xFFFFF,
        GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_CODE_SEGMENT | GDT_ACCESS_CODE_READABLE,
        GDT_FLAG_32BIT | GDT_FLAG_GRANULARITY_4K
    ),

    // Kernel 32-bit data segment
    GDT_ENTRY(
        0,
        0xFFFFF,
        GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_DATA_SEGMENT | GDT_ACCESS_DATA_WRITEABLE,
        GDT_FLAG_32BIT | GDT_FLAG_GRANULARITY_4K
    ),
};

static gdt_descriptor g_gdt_descriptor = {sizeof(g_gdt) - 1, g_gdt};

void __attribute__((cdecl)) i686_gdt_load(gdt_descriptor *descriptor, uint16_t code_segment, int16_t data_segment);

void i686_gdt_initialize(){
    i686_gdt_load(&g_gdt_descriptor, i686_GDT_CODE_SEGMENT, i686_GDT_DATA_SEGMENT);
}
