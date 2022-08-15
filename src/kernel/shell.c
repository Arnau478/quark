#include <stdint.h>
#include "shell.h"
#include "lib/stdio.h"
#include "lib/string.h"
#include "lib/memory.h"
#include "lib/time.h"
#include "arch/i686/fdc.h"

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
    else if(!strcmp(cmd, "sleep")){
        printf("Sleeping...\n");
        sleep(25);
        printf("Done!\n");
    }
    else if(!strcmp(cmd, "readsect")){
        puts("Sector number: ");
        char secn_str[4];
        gets(secn_str, 3);
        int secn = atoi(secn_str);

        uint8_t *sector = i686_fdc_read_sector(secn);

        if(sector){
            int i = 0;
            for(int c = 0; c < 4; c++){
                for(int j = 0; j < 128; j++){
                    printf("0x%x ", sector[i+j]);
                }
                i += 128;
                printf("\nPress enter to continue\n");
                gets(NULL, 0);
            }
        }
        else{
            printf("ERROR reading sector %i from disk", secn);
        }
        printf("Done!\n");
    }
    else{
        printf("SHELL: Unknown command \"%s\"\n", cmd);
        ret = 127;
    }
    puts("\x1b[0m");
    
    return ret;
}

void shell(){
    puts("\x1b[33mWelcome to quark!\x1b[0m\n\n");

    for(;;){
        static char cmd_buffer[256];
        puts("$>");
        gets(cmd_buffer, 255);
        shell_run(cmd_buffer);
    }
}
