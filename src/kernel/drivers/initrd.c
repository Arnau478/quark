#include "../lib/debug.h"
#include "initrd.h"

static uint8_t *_initrd_addr;

void initrd_set_addr(uint8_t *addr){
    debug_printf("Initrd addr set to %x\n", addr);
    _initrd_addr = addr;
}

uint8_t *initrd_get_addr(){
    return _initrd_addr;
}
