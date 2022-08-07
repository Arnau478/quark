#include "uart.h"
#include "../arch/i686/io.h"

void uart_set_baudrate(uint16_t port, uint16_t divisor){
    i686_outb(port + 3, 0x80); // Enable DLAB
    i686_outb(port, (divisor >> 8) & 0x00FF); // High part
    i686_outb(port, divisor & 0x00FF); // Low part
}

void uart_initialize(uint16_t port, uint16_t baudrate_div){
    uart_set_baudrate(port, baudrate_div);

    // Configure line
    i686_outb(port + 3, 0x03); // 8 bit, no parity, 1 stop bit, no break control

    // Configure buffering
    i686_outb(port + 2, 0xC7); // FIFO enabled, clear both FIFO queues, 14 bytes queue(s)

    // Configure modem
    i686_outb(port + 4, 0x03); // RTS=1 DTS=1
}

static int uart_received(uint16_t port){
    return i686_inb(port + 5) & 0x01;
}

char uart_read(uint16_t port){
    while(!uart_received(port));

    return i686_inb(port);
}

static int uart_tx_empty(uint16_t port){
    return i686_inb(port + 5) & 0x20;
}

void uart_write(uint16_t port, char c){
    while(!uart_tx_empty(port));

    return i686_outb(port, c);
}
