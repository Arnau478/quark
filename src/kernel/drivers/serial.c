#include "serial.h"
#include "../arch/i686/io.h"

int serial_initialize(uint8_t port){
    i686_outb(port + 1, 0x00); // Disable all interrupts
    i686_outb(port + 3, 0x80); // Enable DLAB
    i686_outb(port + 0, 0x03); // Divisor high byte (38400 baud)
    i686_outb(port + 1, 0x00); // Divisor low byte
    i686_outb(port + 3, 0x03); // 8 bits, no parity, one stop bit
    i686_outb(port + 2, 0xC7); // Enable FIFO
    i686_outb(port + 4, 0x0B); // IRQs enabled, RTS/DSR set
    
    i686_outb(port + 4, 0x1E); // Loopback mode, test serial chip
    i686_outb(port + 0, 0xAE); // Test serial chip sending 0xAE
    
    if(i686_inb(port + 0) != 0xAE){ // Not working
        return 1;
    }

    i686_outb(port + 4, 0x0F); // Normal operation mode
    return 0;
}

static int serial_received(uint8_t port){
    return i686_inb(port + 5) & 0x01;
}

char serial_read(uint8_t port){
    while(!serial_received(port));

    return i686_inb(port);
}

static int serial_tx_empty(uint8_t port){
    return i686_inb(port + 5) & 0x20;
}

void serial_write(uint8_t port, char c){
    while(!serial_tx_empty(port));

    return i686_outb(port, c);
}
