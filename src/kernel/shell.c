#include "shell.h"
#include "lib/stdio.h"
#include "lib/string.h"
#include "lib/memory.h"

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
        serial_printf("Hello world!\n");
    }
    else{
        printf("SHELL: Unknown command \"%s\"\n", cmd);
        ret = 127;
    }
    puts("\x1b[0m");
    
    return ret;
}
