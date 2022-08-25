#pragma once

#include <stdint.h>
#include <stdbool.h>

#define i686_FDC_DOR 0x3F2
#define i686_FDC_MSR 0x3F4
#define i686_FDC_FIFO 0x3F5
#define i686_FDC_CTRL 0x3F7
#define i686_FDC_DOR_DRIVE0 0x00
#define i686_FDC_DOR_DRIVE1 0x01
#define i686_FDC_DOR_DRIVE2 0x02
#define i686_FDC_DOR_DRIVE3 0x03
#define i686_FDC_DOR_RESET 0x04
#define i686_FDC_DOR_DMA 0x08
#define i686_FDC_DOR_DRIVE0_MOTOR 0x10
#define i686_FDC_DOR_DRIVE1_MOTOR 0x20
#define i686_FDC_DOR_DRIVE2_MOTOR 0x40
#define i686_FDC_DOR_DRIVE3_MOTOR 0x80
#define i686_FDC_MSR_DRIVE0_POS_MODE 0x01
#define i686_FDC_MSR_DRIVE1_POS_MODE 0x02
#define i686_FDC_MSR_DRIVE2_POS_MODE 0x04
#define i686_FDC_MSR_DRIVE3_POS_MODE 0x08
#define i686_FDC_MSR_BUSY 0x10
#define i686_FDC_MSR_DMA 0x20
#define i686_FDC_MSR_DATAIO 0x40
#define i686_FDC_MSR_DATAREG 0x80
#define i686_FDC_CMD_READ_TRACK 0x02
#define i686_FDC_CMD_SPECIFY 0x03
#define i686_FDC_CMD_CHECK_STAT 0x04
#define i686_FDC_CMD_WRITE_SECT 0x05
#define i686_FDC_CMD_READ_SECT 0x06
#define i686_FDC_CMD_CALIBRATE 0x07
#define i686_FDC_CMD_CHECK_INT 0x08
#define i686_FDC_CMD_WRITE_DEL_S 0x09
#define i686_FDC_CMD_READ_ID_S 0x0A
#define i686_FDC_CMD_READ_DEL_S 0x0C
#define i686_FDC_CMD_FORMAT_TRACK 0x0D
#define i686_FDC_CMD_SEEK 0x0F
#define i686_FDC_CMD_EXT_SKIP 0x20
#define i686_FDC_CMD_EXT_DENSITY 0x40
#define i686_FDC_CMD_EXT_MULTITRACK 0x80
#define i686_FDC_GAP3_STD 42
#define i686_FDC_GAP3_5_14 32
#define i686_FDC_GAP3_3_5 27
#define i686_FDC_SECTOR_DTL_128 0
#define i686_FDC_SECTOR_DTL_256 1
#define i686_FDC_SECTOR_DTL_512 2
#define i686_FDC_SECTOR_DTL_1024 4
#define i686_FDC_SECTORS_PER_TRACK 18
#define i686_FDC_DMA_BUFFER 0x1000
#define i686_FDC_DMA_CHANNEL 2

void i686_fdc_initialize_dma();
void i686_fdc_dma_read();
void i686_fdc_dma_write();
uint8_t i686_fdc_msr_read();
void i686_fdc_send_cmd(uint8_t cmd);
uint8_t i686_fdc_read_data();
void i686_fdc_write_ccr(uint8_t v);
void i686_fdc_drive_data(uint32_t stepr, uint32_t loadt, uint32_t unloadt, bool dma);
void i686_fdc_check_int(uint32_t *st0, uint32_t *cyl);
int i686_fdc_motor(bool b);
void i686_fdc_read_sector_imp(uint8_t head, uint8_t track, uint8_t sector);
uint8_t *i686_fdc_read_sector(int lba);
int i686_fdc_calibrate(uint32_t drive);
int i686_fdc_seek(uint32_t cyl, uint32_t head);
void i686_fdc_disable();
void i686_fdc_enable();
void i686_fdc_reset();
void i686_fdc_set_working_drive(int drive);
void i686_fdc_initialize();
void i686_dma_initialize_floppy(uint8_t *buffer, unsigned length);
