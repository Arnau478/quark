#include <stdbool.h>
#include "../lib/string.h"
#include "keyboard.h"
#include "../arch/i686/isr.h"
#include "../lib/stdio.h"
#include "../arch/i686/io.h"
#include "../lib/stdio.h"
#include "../shell.h"

static bool g_caps_lock = false;
static bool g_shift = false;

static char g_key_buffer[256];

static const char g_sc_ascii[128] = {
    '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p', '[', ']', '?', '?', 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', '?', '?',
    '?', ' '
};

static void user_input(char *str){
    shell_run(str);
}

static void keyboard_callback(){
    uint8_t scancode = i686_inb(0x60);
    if(scancode == 0x2A) g_shift = true; // Shift pressed
    else if(scancode == 0x2A + 128) g_shift = false; // Shift released
    else if(scancode == 0x3A) g_caps_lock = !g_caps_lock; // Caps lock pressed
    else if(scancode < 128){ // If it's a "pressed" event, not "released"
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
            char c = g_sc_ascii[scancode];
            if(c >= 'a' && c <= 'z' && g_shift != g_caps_lock) c += 'A' - 'a';
            putc(c);

            // strlen() works here because char[] is the same as
            // char*, and both are null-terminated, so they are
            // exactly the same
            int len = strlen(g_key_buffer);
            g_key_buffer[len] = c;
            g_key_buffer[len+1] = '\0';
        }
    }
}

void keyboard_initialize(){
    i686_isr_register_handler(IRQ(1), keyboard_callback);
}
