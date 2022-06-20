#include "shell.h"
#include "lib/stdio.h"
#include "lib/string.h"

int shell_run(char *cmd){
    int ret = 0;

    puts("\x1b[32m");
    if(!strcmp(cmd, "HELLO")){
        printf("Hello!\n");
    }
    else if(!strcmp(cmd, "VERSION")){
        printf("%s\n", OS_VERSION);
    }
    else{
        printf("SHELL: Unknown command \"%s\"\n", cmd);
        ret = 127;
    }
    puts("\x1b[0m");
    
    return ret;
}
