#include "vmm.h"
#include "pmm.h"
#include "../../../lib/memory.h"

i686_vmm_page_directory_t *g_vmm_current_dir = 0;
i686_phys_addr g_vmm_current_pdbr = 0;

void __attribute__((cdecl)) i686_vmm_flush_tlb_entry(i686_virt_addr addr);

static inline i686_pt_entry_t *i686_vmm_ptable_lookup_entry(i686_vmm_page_table_t *p, i686_virt_addr addr){
    if(p) return &p->entries[i686_PAGE_TABLE_INDEX(addr)];
    return 0;
}

static inline i686_pd_entry_t *i686_vmm_pdirectory_lookup_entry(i686_vmm_page_directory_t *p, i686_virt_addr addr){
    if(p) return &p->entries[i686_PAGE_DIRECTORY_INDEX(addr)];
    return 0;
}

static inline bool i686_vmm_switch_pdirectory(i686_vmm_page_directory_t *dir){
    if(!dir) return false;

    g_vmm_current_dir = dir;
    i686_pmm_load_pdbr(g_vmm_current_pdbr);
    return true;
}

static inline i686_vmm_page_directory_t *i686_vmm_get_pdirectory(){
    return g_vmm_current_dir;
}

bool i686_vmm_alloc_page(i686_pt_entry_t *entry){
    void *p = i686_pmm_alloc_block();
    if(!p) return false;

    i686_pt_entry_set_frame(entry, (i686_phys_addr)p);
    i686_pt_entry_add_attr(entry, i686_PTE_PRESENT);

    return true;
}

void i686_vmm_free_page(i686_pt_entry_t *entry){
    void *p = (void *)i686_pt_entry_get_frame(*entry);
    if(p) i686_pmm_free_block(p);

    i686_pt_entry_del_attr(entry, i686_PTE_PRESENT);
}

void i686_vmm_map_page(void *phys, void *virt){
    // Get page directory
    i686_vmm_page_directory_t *page_dir = i686_vmm_get_pdirectory();

    // Get page table
    i686_pd_entry_t *e = &page_dir->entries[i686_PAGE_DIRECTORY_INDEX((uint32_t)virt)];
    if((*e & i686_PTE_PRESENT) != i686_PTE_PRESENT){
        // Must allocate
        i686_vmm_page_table_t *table = (i686_vmm_page_table_t *)i686_pmm_alloc_block();
        if(!table) return;

        // Clear page table
        memset(table, 0, sizeof(i686_vmm_page_table_t));

        // Create a new entry
        i686_pd_entry_t *entry = &page_dir->entries[i686_PAGE_DIRECTORY_INDEX((uint32_t)virt)];
        
        // Map in the table
        i686_pd_entry_add_attr(entry, i686_PDE_PRESENT);
        i686_pd_entry_add_attr(entry, i686_PDE_WRITABLE);
        i686_pd_entry_set_frame(entry, (i686_phys_addr)table);
    }

    // Get table
    i686_vmm_page_table_t *table = (i686_vmm_page_table_t *)i686_PAGE_GET_PHYS_ADDR(e);

    // Get page
    i686_pt_entry_t *page = &table->entries[i686_PAGE_TABLE_INDEX((uint32_t)virt)];

    // Map it
    i686_pt_entry_set_frame(page, (i686_phys_addr)phys);
    i686_pt_entry_add_attr(page, i686_PTE_PRESENT);
}

void i686_vmm_initialize(){
    // Allocate default page table
    i686_vmm_page_table_t *table = (i686_vmm_page_table_t *)i686_pmm_alloc_block();
    if(!table) return;

    // Allocate 3GB page table
    i686_vmm_page_table_t *table2 = (i686_vmm_page_table_t *)i686_pmm_alloc_block();
    if(!table2) return;

    // Clear default table
    memset(table, 0, sizeof(i686_vmm_page_table_t));

    // First 4MB are identity mapped
    for(int i = 0, frame = 0x0, virt = 0x00000000; i<1024; i++, frame += 4096, virt += 4096){
        // Create a new page
        i686_pt_entry_t page = 0;
        i686_pt_entry_add_attr(&page, i686_PTE_PRESENT);
        i686_pt_entry_set_frame(&page, frame);
        
        // Add the page to the page table
        table2->entries[i686_PAGE_TABLE_INDEX(virt)] = page;
    }

    // Map 1MB to 3GB
    for(int i = 0, frame = 0x100000, virt = 0xc0000000; i<1024; i++, frame += 4096, virt += 4096){
        // Create a new page
        i686_pt_entry_t page = 0;
        i686_pt_entry_add_attr(&page, i686_PTE_PRESENT);
        i686_pt_entry_set_frame(&page, frame);
        
        // Add the page to the page table
        table->entries[i686_PAGE_TABLE_INDEX(virt)] = page;
    }

    // Create default directory table
    i686_vmm_page_directory_t *dir = (i686_vmm_page_directory_t *)i686_pmm_alloc_blocks(3);
    if(!dir) return;

    // Clear directory table and set it as current
    memset(dir, 0, sizeof(i686_vmm_page_directory_t));

    i686_pd_entry_t *entry = &dir->entries[i686_PAGE_DIRECTORY_INDEX(0xc0000000)];
    i686_pd_entry_add_attr(entry, i686_PDE_PRESENT);
    i686_pd_entry_add_attr(entry, i686_PDE_WRITABLE);
    i686_pd_entry_set_frame(entry, (i686_phys_addr)table);

    i686_pd_entry_t *entry2 = &dir->entries[i686_PAGE_DIRECTORY_INDEX(0x00000000)];
    i686_pd_entry_add_attr(entry2, i686_PDE_PRESENT);
    i686_pd_entry_add_attr(entry2, i686_PDE_WRITABLE);
    i686_pd_entry_set_frame(entry2, (i686_phys_addr)table2);

    // Store current PDBR
    g_vmm_current_pdbr = (i686_phys_addr)&dir->entries;

    // Switch to our page directory
    i686_vmm_switch_pdirectory(dir);

    // Enable paging
    i686_pmm_paging_enable(true);
}
