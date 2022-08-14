#include <stdbool.h>
#include "../lib/string.h"
#include "keyboard.h"
#include "../arch/i686/isr.h"
#include "../lib/stdio.h"
#include "../arch/i686/io.h"
#include "../lib/stdio.h"
#include "../shell.h"
#include "../lib/debug.h"

static bool g_caps_lock = false;
static bool g_shift = false;

static struct {
    char buffer[KEY_BUFFER_LENGTH];
    int base;
    int top;
} g_key_buffer;

void keyboard_buffer_add(char c){
    g_key_buffer.buffer[g_key_buffer.top] = c;
    g_key_buffer.top++;
    g_key_buffer.top %= KEY_BUFFER_LENGTH;
}

char keyboard_buffer_get(){
    char c = g_key_buffer.buffer[g_key_buffer.base];
    g_key_buffer.base++;
    g_key_buffer.base %= KEY_BUFFER_LENGTH;
    return c;
}

int keyboard_buffer_length(){
    int base = g_key_buffer.base;
    int top = g_key_buffer.top;
    if(top < base) top += KEY_BUFFER_LENGTH;
    return top - base;
}

static const char g_sc_ascii[128] = {
    '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '\b', '?',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p', '[', ']', '\n', '?', 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', '?', '?',
    '?', ' '
};

static void keyboard_callback(){
    uint8_t scancode = i686_inb(0x60);
    if(scancode == 0x2A) g_shift = true; // Shift pressed
    else if(scancode == 0x2A + 128) g_shift = false; // Shift released
    else if(scancode == 0x3A) g_caps_lock = !g_caps_lock; // Caps lock pressed
    else if(scancode < 128){ // If it's a "pressed" event, not "released"
        char c = g_sc_ascii[scancode];
        if(c >= 'a' && c <= 'z' && g_shift != g_caps_lock) c += 'A' - 'a';

        // strlen() works here because char[] is the same as
        // char*, and both are null-terminated, so they are
        // exactly the same
        keyboard_buffer_add(c);
    }
}

void keyboard_initialize(){
    debug_printf("[KEYBOARD] Initializing\n");

    // Setup IRQ
    i686_isr_register_handler(IRQ(1), keyboard_callback);

    // Initialize key buffer
    g_key_buffer.base = 0;
    g_key_buffer.top = 0;
}
