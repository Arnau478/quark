#pragma once

#include <stdint.h>

#define FS_FILE 0x01
#define FS_DIRECTORY 0x02
#define FS_CHARDEVICE 0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE 0x05
#define FS_SYMLINK 0x06
#define FS_MOUNTPOINT 0x08

typedef struct fs_node{
    char name[128];
    uint32_t mask;
    uint32_t uid;
    uint32_t gid;
    uint32_t flags;
    uint32_t inode;
    uint32_t length;
    uint32_t impl;
    fs_read_fn_t read;
    fs_write_fn_t write;
    fs_open_fn_t open;
    fs_close_fn_t close;
    fs_readdir_fn_t readdir;
    fs_finddir_fn_t finddir;
    struct fs_node *ptr;
} fs_node_t;

typedef struct dirent{
    char name[128];
    uint32_t inode;
} dirent_t;

typedef uint32_t (*fs_read_fn_t)(fs_node_t *, uint32_t, uint32_t, uint8_t *);
typedef uint32_t (*fs_write_fn_t)(fs_node_t *, uint32_t, uint32_t, uint8_t *);
typedef void (*fs_open_fn_t)(fs_node_t *);
typedef void (*fs_close_fn_t)(fs_node_t *);
typedef dirent_t *(*fs_readdir_fn_t)(fs_node_t *, uint32_t);
typedef fs_node_t *(*fs_finddir_fn_t)(fs_node_t *, char *);

extern fs_node_t *fs_root;

uint32_t fs_read(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);
uint32_t fs_write(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);
void fs_open(fs_node_t *node, uint8_t read, uint8_t write);
void fs_close(fs_node_t *node);
dirent_t *fs_readdir(fs_node_t *node, uint32_t index);
fs_node_t *fs_finddir(fs_node_t *node, char *name);
