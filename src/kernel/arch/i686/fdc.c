#include <stdbool.h>
#include "fdc.h"
#include "isr.h"
#include "io.h"
#include "../../lib/time.h"
#include "../../lib/debug.h"

static volatile bool g_fdc_irq = false;
static int g_curr_drive = 0;

static void i686_fdc_irq(registers *regs){
    g_fdc_irq = true;
}

static inline void wait_irq(){
    while(!g_fdc_irq); // Wait until g_fdc_irq is true
    g_fdc_irq = false; // Then reset it to false
}

void i686_fdc_initialize_dma(){
    i686_outb(0x0A, 0x06); // Mask DMA channel 2
    i686_outb(0xD8, 0xFF); // Reset master flip-flop
    i686_outw(0x04, 0x1000); // Address = 0x1000
    i686_outb(0xD8, 0xFF); // Reset master flip-flop
    i686_outb(0x05, 0xFF); // Count to 0x23FF (bytes in 2.5" floppy disk track)
    i686_outb(0x05, 0x23);
    i686_outb(0x80, 0x00); // External page register = 0
    i686_outb(0x0A, 0x02); // Unmask DMA channel 2
}

void i686_fdc_dma_read(){
    i686_outb(0x0A, 0x06); // Mask DMA channel 2
    i686_outb(0x0B, 0x56); // single transfer, address increment, autoinit, read, channel 2
    i686_outb(0x0A, 0x02); // Unmask DMA channel 2
}

void i686_fdc_dma_write(){
    i686_outb(0x0A, 0x06); // Mask DMA channel 2
    i686_outb(0x0B, 0x5A); // single transfer, address increment, autoinit, write, channel 2
    i686_outb(0x0A, 0x02); // Unmask DMA channel 2
}

uint8_t i686_fdc_msr_read(){
    return i686_inb(i686_FDC_MSR);
}

void i686_fdc_send_cmd(uint8_t cmd){
    while(!(i686_fdc_msr_read() & i686_FDC_MSR_DATAREG));
    i686_outb(i686_FDC_FIFO, cmd);
}

uint8_t i686_fdc_read_data(){
    while(!(i686_fdc_msr_read() & i686_FDC_MSR_DATAREG));
    return i686_inb(i686_FDC_FIFO);
}

void i686_fdc_write_ccr(uint8_t v){
    i686_outb(i686_FDC_CTRL, v);
}

void i686_fdc_drive_data(uint32_t stepr, uint32_t loadt, uint32_t unloadt, bool dma){
    uint32_t data = 0;
    
    i686_fdc_send_cmd(i686_FDC_CMD_SPECIFY);
    
    data = ((stepr & 0xF) << 4) | (unloadt & 0xF);
    i686_fdc_send_cmd(data);
    
    data = loadt << 1 | dma ? 1 : 0; // Ensure dma is a 0/1 bool
    i686_fdc_send_cmd(data);
}

void i686_fdc_check_int(uint32_t *st0, uint32_t *cyl){
    i686_fdc_send_cmd(i686_FDC_CMD_CHECK_INT);
    *st0 = i686_fdc_read_data();
    *cyl = i686_fdc_read_data();
}

int i686_fdc_motor(bool b){
    if(g_curr_drive > 3) return -2;

    uint32_t motor = 0;
    switch(g_curr_drive){
        case 0: motor = i686_FDC_DOR_DRIVE0_MOTOR; break;
        case 1: motor = i686_FDC_DOR_DRIVE1_MOTOR; break;
        case 2: motor = i686_FDC_DOR_DRIVE2_MOTOR; break;
        case 3: motor = i686_FDC_DOR_DRIVE3_MOTOR; break;
    }

    if(b) i686_outb(i686_FDC_DOR, g_curr_drive | motor | i686_FDC_DOR_RESET | i686_FDC_DOR_DMA);
    else i686_outb(i686_FDC_DOR, i686_FDC_DOR_RESET);

    // Give the motor some time
    sleep(20);
}

void i686_fdc_read_sector_imp(uint8_t head, uint8_t track, uint8_t sector){
    uint32_t st0, cyl;

    // Set DMA for read
    i686_fdc_dma_read();

    // Read a sector
    i686_fdc_send_cmd(i686_FDC_CMD_READ_SECT | i686_FDC_CMD_EXT_MULTITRACK | i686_FDC_CMD_EXT_SKIP | i686_FDC_CMD_EXT_DENSITY);
    i686_fdc_send_cmd(head << 2 | g_curr_drive);
    i686_fdc_send_cmd(track);
    i686_fdc_send_cmd(head);
    i686_fdc_send_cmd(sector);
    i686_fdc_send_cmd(i686_FDC_SECTOR_DTL_512);
    i686_fdc_send_cmd((sector + 1) >= i686_FDC_SECTORS_PER_TRACK ? i686_FDC_SECTORS_PER_TRACK : sector + 1);
    i686_fdc_send_cmd(i686_FDC_GAP3_3_5);
    i686_fdc_send_cmd(0xFF);

    // Wait for IRQ
    wait_irq();

    // Read output
    for(int i = 0; i < 7; i++) i686_fdc_read_data();

    // Tell the FDC we are done
    i686_fdc_check_int(&st0, &cyl);
}

static void lba_to_chs(int lba, int *head, int *track, int *sector){
    *head = (lba % (i686_FDC_SECTORS_PER_TRACK * 2)) / i686_FDC_SECTORS_PER_TRACK;
    *track = lba / (i686_FDC_SECTORS_PER_TRACK * 2);
    *sector = lba % i686_FDC_SECTORS_PER_TRACK + 1;
}

uint8_t *i686_fdc_read_sector(int lba){
    if(g_curr_drive > 3) return 0;

    // Convert LBA to CHS
    int head = 0, track = 0, sector = 1;
    lba_to_chs(lba, &head, &track, &sector);

    // Turn on motor and seek
    i686_fdc_motor(true);
    if(i686_fdc_seek(track, head) != 0) return 0;

    // Read and turn off motor
    i686_fdc_read_sector_imp(head, track, sector);
    i686_fdc_motor(false);

    return (uint8_t *)0x1000;
}

int i686_fdc_calibrate(uint32_t drive){
    uint32_t st0, cyl;

    if(drive > 3) return -2;

    i686_fdc_motor(true);

    for(int i = 0; i < 10; i++){
        // Send command
        i686_fdc_send_cmd(i686_FDC_CMD_CALIBRATE);
        i686_fdc_send_cmd(drive);
        wait_irq();
        i686_fdc_check_int(&st0, &cyl);

        if(!cyl){
            i686_fdc_motor(false);
            return 0;
        }
    }


    i686_fdc_motor(false);
    return -1;
}

int i686_fdc_seek(uint32_t cyl, uint32_t head){
    uint32_t st0, cyl0;

    if(g_curr_drive > 3) return -2;

    for(int i = 0; i < 10; i++){
        // Send the command
        i686_fdc_send_cmd(i686_FDC_CMD_SEEK);
        i686_fdc_send_cmd(head << 2 | g_curr_drive);
        i686_fdc_send_cmd(cyl);

        // Wait for the results
        wait_irq();
        i686_fdc_check_int(&st0, &cyl0);

        // Found?
        if(cyl0 == cyl) return 0;
    }

    return -1;
}

void i686_fdc_disable(){
    i686_outb(i686_FDC_DOR, 0);
}

void i686_fdc_enable(){
    i686_outb(i686_FDC_DOR, i686_FDC_DOR_RESET | i686_FDC_DOR_DMA);
}

void i686_fdc_reset(){
    uint32_t st0, cyl;

    // Reset the controller
    i686_fdc_disable();
    i686_fdc_enable();
    wait_irq();

    // CHECK_INT to all drives
    for(int i = 0; i < 4; i++) i686_fdc_check_int(&st0, &cyl);

    // 500kb/s
    i686_fdc_write_ccr(0);

    // steprate = 3ms, unload time = 240ms, load time = 16ms, dma = true
    i686_fdc_drive_data(3, 16, 240, true);

    // Calibrate the disk
    i686_fdc_calibrate(g_curr_drive);
}

void i686_fdc_set_working_drive(int drive){
    if(drive < 4) g_curr_drive = drive;
}

void i686_fdc_initialize(){
    debug_printf("[FDC] Initializing\n");
    // Setup IRQ
    i686_isr_register_handler(IRQ(6), i686_fdc_irq);

    // Initialize DMA
    i686_fdc_initialize_dma();

    // Reset FDC
    i686_fdc_reset();

    // Set drive info
    i686_fdc_drive_data(13, 1, 0x0F, true);
}
