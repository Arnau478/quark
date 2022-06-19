#include "../util/string.h"
#include "keyboard.h"
#include "../arch/i686/isr.h"
#include "../stdio.h"
#include "../arch/i686/io.h"
#include "../stdio.h"

static char g_key_buffer[256];

static const char g_sc_ascii[128] = {
    '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?',
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '[', ']', '?', '?', 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',
    '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
    'B', 'N', 'M', ',', '.', '/', '?', '?',
    '?', ' '
};

static void user_input(char *str){
    printf("In: \"%s\"\n", str);
}

static void keyboard_callback(){
    uint8_t scancode = i686_inb(0x60);
    //printf("KEYBOARD (%i)!\n", scancode);
    if(scancode < 128){ // If it's a "pressed" event, not "released"
        if(scancode == 0x0E){ // Backspace
            putc('\b');
            g_key_buffer[strlen(g_key_buffer)-1] = '\0';
        }
        else if(scancode == 0x1C){ // Enter
            putc('\n');
            user_input(g_key_buffer);
            g_key_buffer[0] = '\0';
        }
        else{
            putc(g_sc_ascii[scancode]);

            // strlen() works here because char[] is the same as
            // char*, and both are null-terminated, so they are
            // exactly the same
            g_key_buffer[strlen(g_key_buffer)] = g_sc_ascii[scancode];
        }
    }
}

void keyboard_initialize(){
    i686_isr_register_handler(IRQ(1), keyboard_callback);
}
