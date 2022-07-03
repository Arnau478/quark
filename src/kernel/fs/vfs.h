#pragma once

#include <stdint.h>

// Only one!
#define VFS_FLAG_O_RDONLY 0x00
#define VFS_FLAG_O_WRONLY 0x01
#define VFS_FLAG_O_RDWR 0x02

// Combinable
#define VFS_FLAG_O_APPEND 0x04
#define VFS_FLAG_O_CREAT 0x08

typedef struct{
    char name[256];
    uint8_t flags;
} file_descriptor_t;

file_descriptor_t g_fds[256];

file_descriptor_t *vfs_open(const char *path, const char *mode);
