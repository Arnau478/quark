#include "shell.h"
#include "lib/stdio.h"
#include "lib/string.h"
#include "lib/memory.h"
#include "drivers/serial.h"

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
    else if(!strcmp(cmd, "serial")){
        serial_write(COM1, 'H');
        serial_write(COM1, 'E');
        serial_write(COM1, 'L');
        serial_write(COM1, 'L');
        serial_write(COM1, 'O');
    }
    else{
        printf("SHELL: Unknown command \"%s\"\n", cmd);
        ret = 127;
    }
    puts("\x1b[0m");
    
    return ret;
}
