#include <stdint.h>

uint8_t __attribute__((cdecl)) i686_inb(uint16_t port);
void __attribute__((cdecl)) i686_outb(uint16_t port, uint8_t value);
uint16_t __attribute__((cdecl)) i686_inw(uint16_t port);
void __attribute__((cdecl)) i686_outw(uint16_t port, uint16_t value);

void __attribute__((cdecl)) i686_panic();
