#include <stdint.h>
#include "dma.h"
#include "io.h"

void i686_dma_set_address(uint8_t channel, uint16_t addr){
    if(channel > 8) return;

    uint16_t port = 0;
    switch(channel){
        case 0: port = i686_DMA0_CHAN0_ADDR_REG; break;
        case 1: port = i686_DMA0_CHAN1_ADDR_REG; break;
        case 2: port = i686_DMA0_CHAN2_ADDR_REG; break;
        case 3: port = i686_DMA0_CHAN3_ADDR_REG; break;
        case 4: port = i686_DMA1_CHAN4_ADDR_REG; break;
        case 5: port = i686_DMA1_CHAN5_ADDR_REG; break;
        case 6: port = i686_DMA1_CHAN6_ADDR_REG; break;
        case 7: port = i686_DMA1_CHAN7_ADDR_REG; break;
    }

    i686_outw(port, addr);
}

void i686_dma_set_count(uint8_t channel, uint16_t count){
    if(channel > 8) return;

    uint16_t port = 0;
    switch(channel){
        case 0: port = i686_DMA0_CHAN0_COUNT_REG; break;
        case 1: port = i686_DMA0_CHAN1_COUNT_REG; break;
        case 2: port = i686_DMA0_CHAN2_COUNT_REG; break;
        case 3: port = i686_DMA0_CHAN3_COUNT_REG; break;
        case 4: port = i686_DMA1_CHAN4_COUNT_REG; break;
        case 5: port = i686_DMA1_CHAN5_COUNT_REG; break;
        case 6: port = i686_DMA1_CHAN6_COUNT_REG; break;
        case 7: port = i686_DMA1_CHAN7_COUNT_REG; break;
    }

    i686_outw(port, count);
}

void i686_dma_set_external_page_register(uint8_t reg, uint8_t val){
    uint16_t port = 0;

    switch(reg){
        case 1: port = i686_DMA_PAGE_CHAN1_ADDRBYTE2; break;
        case 2: port = i686_DMA_PAGE_CHAN2_ADDRBYTE2; break;
        case 3: port = i686_DMA_PAGE_CHAN3_ADDRBYTE2; break;
        // 4 is not valid
        case 5: port = i686_DMA_PAGE_CHAN5_ADDRBYTE2; break;
        case 6: port = i686_DMA_PAGE_CHAN6_ADDRBYTE2; break;
        case 7: port = i686_DMA_PAGE_CHAN7_ADDRBYTE2; break;
        default: return;
    }
}

void i686_dma_set_mode(uint8_t channel, uint8_t mode){
    int dma = (channel < 4) ? 0 : 1;
    int chan = (dma == 0) ? channel : channel-4;

    i686_dma_mask_channel(channel);
    i686_outb((channel < 4) ? i686_DMA0_MODE_REG : i686_DMA1_MODE_REG, chan | mode);
    i686_dma_unmask_all(dma);
}

void i686_dma_set_read(uint8_t channel){
    i686_dma_set_mode(channel, i686_DMA_MODE_READ_TRANSFER | i686_DMA_MODE_TRANSFER_SINGLE | i686_DMA_MODE_MASK_AUTO);
}

void i686_dma_set_write(uint8_t channel){
    i686_dma_set_mode(channel, i686_DMA_MODE_WRITE_TRANSFER | i686_DMA_MODE_TRANSFER_SINGLE | i686_DMA_MODE_MASK_AUTO);
}

void i686_dma_mask_channel(uint8_t channel){
    if(channel <= 4) i686_outb(i686_DMA0_CHANMASK_REG, (1 << (channel-1)));
    else i686_outb(i686_DMA1_CHANMASK_REG, (1 << (channel-5)));
}

void i686_dma_unmask_channel(uint8_t channel){
    i686_outb(channel <= 4 ? i686_DMA0_CHANMASK_REG : i686_DMA1_CHANMASK_REG, channel);
}

void i686_dma_reset_flipflop(int dma){
    if(dma > 2) return;

    i686_outb((dma == 0) ? i686_DMA0_CLEARBYTE_FLIPFLOP_REG : i686_DMA1_CLEARBYTE_FLIPFLOP_REG, 0xFF);
}

void i686_dma_reset(int dma){
    i686_outb(i686_DMA0_TEMP_REG, 0xFF);
}

void i686_dma_unmask_all(int dma){
    i686_outb(i686_DMA1_UNMASK_ALL_REG, 0xFF);
}
