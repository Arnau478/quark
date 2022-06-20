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
    else if(!strcmp(cmd, "malloc")){
        printf("Allocated 10 bytes:\n%x\n", kmalloc(10));
    }
    else if(!strcmp(cmd, "calloc")){
        printf("Allocated and zeroed 10 chars:\n%x\n", kcalloc(10, sizeof(char)));
    }
    else if(!strcmp(cmd, "clear")){
        clear_screen();
    }
    else{
        printf("SHELL: Unknown command \"%s\"\n", cmd);
        ret = 127;
    }
    puts("\x1b[0m");
    
    return ret;
}
