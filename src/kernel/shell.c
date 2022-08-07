#include "shell.h"
#include "lib/stdio.h"
#include "lib/string.h"
#include "lib/memory.h"
#include "drivers/uart.h"

int shell_run(char *cmd){
    int ret = 0;

    puts("\x1b[32m");
    if(!strcmp(cmd, "hello")){
        printf("Hello!\n");
    }
    else if(!strcmp(cmd, "version")){
        printf("%s\n", OS_VERSION);
    }
    else if(!strcmp(cmd, "clear")){
        clear_screen();
    }
    else if(!strcmp(cmd, "uart")){
        uart_write(COM1, '\x1b');
        uart_write(COM1, '[');
        uart_write(COM1, '3');
        uart_write(COM1, '2');
        uart_write(COM1, 'm');
        uart_write(COM1, 'H');
        uart_write(COM1, 'E');
        uart_write(COM1, 'L');
        uart_write(COM1, 'L');
        uart_write(COM1, 'O');
        uart_write(COM1, '\n');
        uart_write(COM1, '\x1b');
        uart_write(COM1, '[');
        uart_write(COM1, '0');
        uart_write(COM1, 'm');
    }
    else{
        printf("SHELL: Unknown command \"%s\"\n", cmd);
        ret = 127;
    }
    puts("\x1b[0m");
    
    return ret;
}
