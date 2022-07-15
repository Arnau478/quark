#include <stddef.h>
#include <stdbool.h>
#include "vfs.h"
#include "../lib/string.h"

file_t g_file_table[256];

// Return some OR-ed flags for the given mode string
static uint8_t flags_from_mode(const char *mode){
    uint8_t flags = 0;
    bool read = false;
    bool write = false;
    while(*mode){
        switch(*mode){
            case 'r':
                read = true;
                break;
            case 'w':
                write = true;
                break;
            case 'a':
                flags |= VFS_FLAG_O_APPEND;
                break;
            case '+':
            case 'c':
                flags |= VFS_FLAG_O_CREAT;
                break;
            default:
                break;
        }
        mode++;
    }

    if(read && write) flags |= VFS_FLAG_O_RDWR;
    else if(read) flags |= VFS_FLAG_O_RDONLY;
    else if(write) flags |= VFS_FLAG_O_WRONLY;

    return flags;
}

// Initialize VFS
void vfs_initialize(){
    for(int i = 0; i < 256; i++){
        *g_file_table[i].name = '\0';
        g_file_table[i].flags = 0;
    }
}

// Open a file and return its file descriptor
file_t *vfs_open(const char *path, const char *mode){
    uint8_t flags = flags_from_mode(mode);
    for(int i = 0; i < 256; i++){
        if(!*g_file_table[i].name){ // If empty
            g_file_table[i].flags = flags;
            strcpy(g_file_table[i].name, (char *)path); // TODO: Check if path is longer than expected
            return &g_file_table[i];
        }
    }
    return NULL; // No free file descriptors
}
