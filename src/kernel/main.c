#include <stdint.h>
#include "lib/stdio.h"
#include "hal/hal.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"
#include "drivers/serial.h"
#include "fs/vfs.h"
#include "arch/i686/mm/pmm.h"
#include "arch/i686/mm/vmm.h"
#include "multiboot.h"

extern uint8_t end; // Kernel end

void __attribute__((cdecl)) kmain(multiboot_info_t *multiboot_info){
    // Clear screen
    clear_screen();

    // Initialize chip-specific hardware
    hal_initialize();

    // Initialize physical memory manager
    uint32_t mem_size = 1024 + multiboot_info->mem_lower + multiboot_info->mem_upper*64;

    i686_pmm_initialize(mem_size, (int)(&end));

    for(int i = 0; i < multiboot_info->mmap_length; i += sizeof(multiboot_memory_map_t)){
        multiboot_memory_map_t *memory_map = (multiboot_memory_map_t *)(multiboot_info->mmap_addr + i);
        printf("Start Addr: 0x%x%x | Length: 0x%x%x | Size: 0x%x | Type: %i\n", memory_map->addr_h, memory_map->addr_l, memory_map->len_h, memory_map->len_l, memory_map->size, memory_map->type);
    
        if(memory_map->type == 1){
            i686_pmm_init_region(memory_map->addr_l, memory_map->len_l);
        }
    }

    i686_pmm_deinit_region(0x100000, (int)(&end) - 0x100000); // Deinit the section the kernel is in

    // Initialize virtual memory
    i686_vmm_initialize();

    // Initialize drivers
    timer_initialize();
    keyboard_initialize();
    
    // Initialize FS
    vfs_initialize();
    
    for(;;);
}
