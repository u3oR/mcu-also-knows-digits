#ifndef _BSP_SDRAM_H
#define _BSP_SDRAM_H

#include "bsp/bsp_uart_debug.h"
#include "stm32h7xx.h"

#define SDRAM_SIZE 0x4000000 // 64M字节,两片W9825G6KH-6,32MB@16bit组成64M@32bit

/*SDRAM 的bank选择*/
#define FMC_COMMAND_TARGET_BANK FMC_SDRAM_CMD_TARGET_BANK2

/**
 * @brief  FMC SDRAM 数据基地址
 */
#define SDRAM_BANK_ADDR ((uint32_t)0xD0000000)

#define SDRAM_TIMEOUT ((uint32_t)0xFFFF)

/**
 * @brief  FMC SDRAM 模式配置的寄存器相关定义
 */
#define SDRAM_MODEREG_BURST_LENGTH_1                ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2                ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4                ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8                ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL         ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED        ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2                 ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3                 ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD       ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE        ((uint16_t)0x0200)

/*信息输出*/
#define SDRAM_DEBUG_ON 1

#define SDRAM_INFO(fmt, arg...) uart_debug("<SDRAM-INFO> " fmt "\n", ##arg)
#define SDRAM_ERROR(fmt, arg...) uart_debug("<SDRAM-ERROR> " fmt "\n", ##arg)
#define SDRAM_DEBUG(fmt, arg...)                                                                                       \
    do                                                                                                                 \
    {                                                                                                                  \
        if (SDRAM_DEBUG_ON)                                                                                            \
            uart_debug("<SDRAM-DEBUG> [%d]" fmt "\n", __LINE__, ##arg);                                            \
    } while (0)

/** @defgroup STM32H750 SDRAM函数
 * @{
 */
	
void SDRAM_InitSequence(void);
void SDRAM_WriteBuffer(uint32_t *pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize);
void SDRAM_ReadBuffer(uint32_t *pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize);

uint8_t SDRAM_Test(void);

#endif /* __SDRAM_H */
