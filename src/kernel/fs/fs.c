#include <stddef.h>
#include "fs.h"

fs_node_t *fs_root = NULL;

uint32_t fs_read(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer){
    if(node->read != NULL){
        return node->read(node, offset, size, buffer);
    }
    return 0;
}

uint32_t fs_write(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer){
    if(node->write != NULL){
        return node->write(node, offset, size, buffer);
    }
    return 0;
}

void fs_open(fs_node_t *node, uint8_t read, uint8_t write){
    if(node->open != NULL){
        return node->open(node);
    }
    return 0;
}

void fs_close(fs_node_t *node){
    if(node->close != NULL){
        return node->close(node);
    }
    return 0;
}

dirent_t *fs_readdir(fs_node_t *node, uint32_t index){
    if(node->readdir != NULL && (node->flags & 0x7 == FS_DIRECTORY)){
        return node->readdir(node, index);
    }
    return 0;
}

fs_node_t *fs_finddir(fs_node_t *node, char *name){
    if(node->finddir != NULL && (node->flags & 0x7 == FS_DIRECTORY)){
        return node->finddir(node, name);
    }
    return 0;
}
