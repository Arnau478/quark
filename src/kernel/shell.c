#include "shell.h"
#include "lib/stdio.h"
#include "lib/string.h"

int shell_run(char *cmd){
    if(!strcmp(cmd, "HELLO")){
        printf("Hello!\n");
    }
    else{
        printf("SHELL: Unknown command \"%s\"\n", cmd);
        return 127;
    }
}
