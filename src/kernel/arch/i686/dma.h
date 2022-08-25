#pragma once

#include <stdint.h>

#define i686_DMA0_STATUS_REG 0x08
#define i686_DMA0_COMMAND_REG 0x08
#define i686_DMA0_REQUEST_REG 0x09
#define i686_DMA0_CHANMASK_REG 0x0A
#define i686_DMA0_MODE_REG 0x0B
#define i686_DMA0_CLEARBYTE_FLIPFLOP_REG 0x0C
#define i686_DMA0_TEMP_REG 0x0D
#define i686_DMA0_MASTER_CLEAR_REG 0x0D
#define i686_DMA0_CLEAR_MASK_REG 0x0E
#define i686_DMA0_MASK_REG 0x0F
#define i686_DMA0_CHAN0_ADDR_REG 0x00
#define i686_DMA0_CHAN0_COUNT_REG 0x01
#define i686_DMA0_CHAN1_ADDR_REG 0x02
#define i686_DMA0_CHAN1_COUNT_REG 0x03
#define i686_DMA0_CHAN2_ADDR_REG 0x04
#define i686_DMA0_CHAN2_COUNT_REG 0x05
#define i686_DMA0_CHAN3_ADDR_REG 0x06
#define i686_DMA0_CHAN3_COUNT_REG 0x07
#define i686_DMA1_STATUS_REG 0xD0
#define i686_DMA1_COMMAND_REG 0xD0
#define i686_DMA1_REQUEST_REG 0xD2
#define i686_DMA1_CHANMASK_REG 0xD4
#define i686_DMA1_MODE_REG 0xD6
#define i686_DMA1_CLEARBYTE_FLIPFLOP_REG 0xD8
#define i686_DMA1_INTER_REG 0xDA
#define i686_DMA1_UNMASK_ALL_REG 0xDC
#define i686_DMA1_MASK_REG 0xDE
#define i686_DMA1_CHAN4_ADDR_REG 0xC0
#define i686_DMA1_CHAN4_COUNT_REG 0xC2
#define i686_DMA1_CHAN5_ADDR_REG 0xC4
#define i686_DMA1_CHAN5_COUNT_REG 0xC6
#define i686_DMA1_CHAN6_ADDR_REG 0xC8
#define i686_DMA1_CHAN6_COUNT_REG 0xCA
#define i686_DMA1_CHAN7_ADDR_REG 0xCC
#define i686_DMA1_CHAN7_COUNT_REG 0xCE
#define i686_DMA_PAGE_EXTRA0 0x80
#define i686_DMA_PAGE_CHAN2_ADDRBYTE2 0x81
#define i686_DMA_PAGE_CHAN3_ADDRBYTE2 0x82
#define i686_DMA_PAGE_CHAN1_ADDRBYTE2 0x83
#define i686_DMA_PAGE_EXTRA1 0x84
#define i686_DMA_PAGE_EXTRA2 0x85
#define i686_DMA_PAGE_EXTRA3 0x86
#define i686_DMA_PAGE_CHAN6_ADDRBYTE2 0x87
#define i686_DMA_PAGE_CHAN7_ADDRBYTE2 0x88
#define i686_DMA_PAGE_CHAN5_ADDRBYTE2 0x89
#define i686_DMA_PAGE_EXTRA4 0x8C
#define i686_DMA_PAGE_EXTRA5 0x8D
#define i686_DMA_PAGE_EXTRA6 0x8E
#define i686_DMA_PAGE_DRAM_REFRESH 0x8F
#define i686_DMA_CMD_MASK_MEMTOMEM 0x01
#define i686_DMA_CMD_MASK_CHAN0ADDRHOLD 0x02
#define i686_DMA_CMD_MASK_ENABLE 0x04
#define i686_DMA_CMD_MASK_TIMING 0x08
#define i686_DMA_CMD_MASK_PRIORITY 0x10
#define i686_DMA_CMD_MASK_WRITESEL 0x20
#define i686_DMA_CMD_MASK_DREQ 0x40
#define i686_DMA_CMD_MASK_DACK 0x80
#define i686_DMA_MODE_MASK_SEL 0x03
#define i686_DMA_MODE_MASK_TRA 0x0C
#define i686_DMA_MODE_MASK_TEST 0x00
#define i686_DMA_MODE_READ_TRANSFER 0x04
#define i686_DMA_MODE_WRITE_TRANSFER 0x08
#define i686_DMA_MODE_MASK_AUTO 0x10
#define i686_DMA_MODE_MASK_IDEC 0x20
#define i686_DMA_MODE_MASK 0xC0
#define i686_DMA_MODE_TRANSFER_ON_DEMAND 0x00
#define i686_DMA_MODE_TRANSFER_SINGLE 0x40
#define i686_DMA_MODE_TRANSFER_BLOCK 0x80
#define i686_DMA_MODE_TRANSFER_CASCADE 0xC0

void i686_dma_set_address(uint8_t channel, uint16_t addr);
void i686_dma_set_count(uint8_t channel, uint16_t count);
void i686_dma_set_external_page_register(uint8_t reg, uint8_t val);
void i686_dma_set_mode(uint8_t channel, uint8_t mode);
void i686_dma_set_read(uint8_t channel);
void i686_dma_set_write(uint8_t channel);
void i686_dma_mask_channel(uint8_t channel);
void i686_dma_unmask_channel(uint8_t channel);
void i686_dma_reset_flipflop(int dma);
void i686_dma_reset(int dma);
void i686_dma_unmask_all(int dma);
