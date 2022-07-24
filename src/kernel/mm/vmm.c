#include "vmm.h"
#include "pmm.h"
#include "../lib/memory.h"

vmm_page_directory_t *g_vmm_current_dir = 0;
phys_addr g_vmm_current_pdbr = 0;

void __attribute__((cdecl)) vmm_flush_tlb_entry(virt_addr addr);

static inline pt_entry_t *vmm_ptable_lookup_entry(vmm_page_table_t *p, virt_addr addr){
    if(p) return &p->entries[PAGE_TABLE_INDEX(addr)];
    return 0;
}

static inline pd_entry_t *vmm_pdirectory_lookup_entry(vmm_page_directory_t *p, virt_addr addr){
    if(p) return &p->entries[PAGE_DIRECTORY_INDEX(addr)];
    return 0;
}

static inline bool vmm_switch_pdirectory(vmm_page_directory_t *dir){
    if(!dir) return false;

    g_vmm_current_dir = dir;
    pmm_load_pdbr(g_vmm_current_pdbr);
    return true;
}

static inline vmm_page_directory_t *vmm_get_pdirectory(){
    return g_vmm_current_dir;
}

bool vmm_alloc_page(pt_entry_t *entry){
    void *p = pmm_alloc_block();
    if(!p) return false;

    pt_entry_set_frame(entry, (phys_addr)p);
    pt_entry_add_attr(entry, PTE_PRESENT);

    return true;
}

void vmm_free_page(pt_entry_t *entry){
    void *p = (void *)pt_entry_get_frame(*entry);
    if(p) pmm_free_block(p);

    pt_entry_del_attr(entry, PTE_PRESENT);
}

void vmm_map_page(void *phys, void *virt){
    // Get page directory
    vmm_page_directory_t *page_dir = vmm_get_pdirectory();

    // Get page table
    pd_entry_t *e = &page_dir->entries[PAGE_DIRECTORY_INDEX((uint32_t)virt)];
    if((*e & PTE_PRESENT) != PTE_PRESENT){
        // Must allocate
        vmm_page_table_t *table = (vmm_page_table_t *)pmm_alloc_block();
        if(!table) return;

        // Clear page table
        memset(table, 0, sizeof(vmm_page_table_t));

        // Create a new entry
        pd_entry_t *entry = &page_dir->entries[PAGE_DIRECTORY_INDEX((uint32_t)virt)];
        
        // Map in the table
        pd_entry_add_attr(entry, PDE_PRESENT);
        pd_entry_add_attr(entry, PDE_WRITABLE);
        pd_entry_set_frame(entry, (phys_addr)table);
    }

    // Get table
    vmm_page_table_t *table = (vmm_page_table_t *)PAGE_GET_PHYS_ADDR(e);

    // Get page
    pt_entry_t *page = &table->entries[PAGE_TABLE_INDEX((uint32_t)virt)];

    // Map it
    pt_entry_set_frame(page, (phys_addr)phys);
    pt_entry_add_attr(page, PTE_PRESENT);
}

void vmm_initialize(){
    // Allocate default page table
    vmm_page_table_t *table = (vmm_page_table_t *)pmm_alloc_block();
    if(!table) return;

    // Allocate 3GB page table
    vmm_page_table_t *table2 = (vmm_page_table_t *)pmm_alloc_block();
    if(!table2) return;

    // Clear default table
    memset(table, 0, sizeof(vmm_page_table_t));

    // First 4MB are identity mapped
    for(int i = 0, frame = 0x0, virt = 0x00000000; i<1024; i++, frame += 4096, virt += 4096){
        // Create a new page
        pt_entry_t page = 0;
        pt_entry_add_attr(&page, PTE_PRESENT);
        pt_entry_set_frame(&page, frame);
        
        // Add the page to the page table
        table2->entries[PAGE_TABLE_INDEX(virt)] = page;
    }

    // Map 1MB to 3GB
    for(int i = 0, frame = 0x100000, virt = 0xc0000000; i<1024; i++, frame += 4096, virt += 4096){
        // Create a new page
        pt_entry_t page = 0;
        pt_entry_add_attr(&page, PTE_PRESENT);
        pt_entry_set_frame(&page, frame);
        
        // Add the page to the page table
        table->entries[PAGE_TABLE_INDEX(virt)] = page;
    }

    // Create default directory table
    vmm_page_directory_t *dir = (vmm_page_directory_t *)pmm_alloc_blocks(3);
    if(!dir) return;

    // Clear directory table and set it as current
    memset(dir, 0, sizeof(vmm_page_directory_t));

    pd_entry_t *entry = &dir->entries[PAGE_DIRECTORY_INDEX(0xc0000000)];
    pd_entry_add_attr(entry, PDE_PRESENT);
    pd_entry_add_attr(entry, PDE_WRITABLE);
    pd_entry_set_frame(entry, (phys_addr)table);

    pd_entry_t *entry2 = &dir->entries[PAGE_DIRECTORY_INDEX(0x00000000)];
    pd_entry_add_attr(entry2, PDE_PRESENT);
    pd_entry_add_attr(entry2, PDE_WRITABLE);
    pd_entry_set_frame(entry2, (phys_addr)table2);

    // Store current PDBR
    g_vmm_current_pdbr = (phys_addr)&dir->entries;

    // Switch to our page directory
    vmm_switch_pdirectory(dir);

    // Enable paging
    pmm_paging_enable(true);
}
