#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

/*********************************
 * Included Header Files
 *********************************/
#include "stm32h7xx.h"
 
#include <stdio.h>
#include <stdint.h>

/*********************************
 * Macro Definitions
 *********************************/

// W25Q256JVEM
#define sFLASH_ID   (0xEF4019U)

/* QSPI Error codes */
#define QSPI_OK             ((uint8_t)0x00U)
#define QSPI_ERROR          ((uint8_t)0x01U)
#define QSPI_BUSY           ((uint8_t)0x02U)
#define QSPI_NOT_SUPPORTED  ((uint8_t)0x04U)
#define QSPI_SUSPENDED      ((uint8_t)0x08U)

/**
 * @brief  W25Q256JV配置
 */
#define W25Q256JV_FLASH_SIZE                0x2000000U  /* 128 MBits => 16MBytes */
#define W25Q256JV_SECTOR_SIZE               0x10000U    /* 256 sectors of 64KBytes */
#define W25Q256JV_SUBSECTOR_SIZE            0x1000U     /* 4096 subsectors of 4kBytes */
#define W25Q256JV_PAGE_SIZE                 0x100U      /* 65536 pages of 256 bytes */

/* 状态寄存器标志 */
#define W25Q256JV_FSR_BUSY  ((uint8_t)0x01)     /*!< busy */
#define W25Q256JV_FSR_WREN  ((uint8_t)0x02)     /*!< write enable */
#define W25Q256JV_FSR_QE    ((uint8_t)0x02)     /*!< quad enable */

#define W25Q256JV_DUMMY_CYCLES_READ         4
#define W25Q256JV_DUMMY_CYCLES_READ_QUAD    10

#define W25Q256JV_BULK_ERASE_MAX_TIME       250000
#define W25Q256JV_SECTOR_ERASE_MAX_TIME     3000
#define W25Q256JV_SUBSECTOR_ERASE_MAX_TIME  800


/* W25Q256JV Micron memory */
/* Size of the flash */
#define QSPI_FLASH_SIZE          (24)
#define QSPI_FLASH_SIZES         (W25Q256JV_FLASH_SIZE)
#define QSPI_PAGE_SIZE           (W25Q256JV_PAGE_SIZE)
#define QSPI_FLASH_MEM_ADDR      (0x90000000UL)


/**
 * @brief  W25Q256JV 指令
 */
/* 复位操作 */
#define RESET_ENABLE_CMD                (0x66U)
#define RESET_MEMORY_CMD                (0x99U)

#define ENTER_QPI_MODE_CMD              (0x38U)
#define EXIT_QPI_MODE_CMD               (0xFFU)
/* 识别操作 */                          
#define READ_ID_CMD                     (0x90U)
#define DUAL_READ_ID_CMD                (0x92U)
#define QUAD_READ_ID_CMD                (0x94U)
#define READ_JEDEC_ID_CMD               (0x9FU)
/* 读操作 */                            
#define READ_CMD_4BYTE                  (0x03U)
#define QUAD_INOUT_FAST_READ_CMD_4BYTE  (0xECU)
/* 写操作 */                            
#define WRITE_ENABLE_CMD                (0x06U)
#define WRITE_DISABLE_CMD               (0x04U)
/* 寄存器操作 */
#define READ_STATUS_REG1_CMD            (0x05U)
#define READ_STATUS_REG2_CMD            (0x35U)
#define READ_STATUS_REG3_CMD            (0x15U)
#define WRITE_STATUS_REG1_CMD           (0x01U)
#define WRITE_STATUS_REG2_CMD           (0x31U)
#define WRITE_STATUS_REG3_CMD           (0x11U)
/* 编程操作 */
#define QUAD_INPUT_PAGE_PROG_CMD_4BYTE  (0x34U)
#define EXT_QUAD_IN_FAST_PROG_CMD_4BYTE (0x12U)
/* 擦除操作 */
#define SECTOR_ERASE_CMD_4BYTE          (0x21U)
#define BLOCK64K_ERASE_CMD_4BYTE        (0xDCU)
#define CHIP_ERASE_CMD                  (0xC7U)

#define PROG_ERASE_RESUME_CMD           (0x7AU)
#define PROG_ERASE_SUSPEND_CMD          (0x75U)

#define ENTER_4_BYTE_ADDR_MODE_CMD 0xB7

/*********************************
 * Structure Definitions
 *********************************/
/* QSPI Info */
typedef struct
{
    uint32_t FlashSize;          /*!< 闪存大小 */
    uint32_t EraseSectorSize;    /*!< 擦除操作的扇区大小 */
    uint32_t EraseSectorsNumber; /*!< 擦除操作的扇区数 */
    uint32_t ProgPageSize;       /*!< 编程操作的页面大小 */
    uint32_t ProgPagesNumber;    /*!< 编程操作的页面数 */
} QSPI_Info;

/*********************************
 * Public Function Declarations
 *********************************/
uint8_t  BSP_QSPI_Init(void);
uint8_t  BSP_QSPI_Erase_Chip(void);
uint8_t  BSP_QSPI_Erase_Block(uint32_t BlockAddress);
uint8_t  BSP_QSPI_Read(uint8_t *pData, uint32_t ReadAddr, uint32_t Size);
uint8_t  BSP_QSPI_FastRead(uint8_t *pData, uint32_t ReadAddr, uint32_t Size);
uint8_t  BSP_QSPI_Write(uint8_t *pData, uint32_t WriteAddr, uint32_t Size);

void     QSPI_Set_WP_High(void);
void     QSPI_Set_WP_TO_QSPI_IO(void);
void     QSPI_FLASH_Wait_Busy(void);
void     QSPI_FLASH_Init(void);
uint8_t  QSPI_ResetMemory(void);
uint32_t QSPI_FLASH_ReadDeviceID(void);
uint32_t QSPI_FLASH_ReadID(void);
uint32_t QSPI_FLASH_ReadStatusReg(uint8_t reg);
uint32_t QSPI_FLASH_WriteStatusReg(uint8_t reg, uint8_t regvalue);
uint32_t QSPI_EnableMemoryMappedMode(void); //使能直接映射模式

#endif /* __SPI_FLASH_H */
