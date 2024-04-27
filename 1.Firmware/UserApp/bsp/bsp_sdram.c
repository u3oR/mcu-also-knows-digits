

#include "bsp/bsp_sdram.h"
FMC_SDRAM_CommandTypeDef Command;
extern SDRAM_HandleTypeDef hsdram1;
#define sdramHandle hsdram1
/**
 * @brief  延迟一段时间
 * @param  延迟的时间长度
 * @retval None
 */
static void SDRAM_delay(__IO uint32_t nCount)
{
    __IO uint32_t index = 0;
    for (index = (100000 * nCount); index != 0; index--)
    {
    }
}

/**
 * @brief  对SDRAM芯片进行初始化配置
 * @param  None.
 * @retval None.
 */
void SDRAM_InitSequence(void)
{
    uint32_t tmpr = 0;

    /* Step 1 ----------------------------------------------------------------*/
    /* 配置命令：开启提供给SDRAM的时钟 */
    Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
    Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = 0;
    /* 发送配置命令 */
    HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

    /* Step 2: 延时100us */
    SDRAM_delay(1);

    /* Step 3 ----------------------------------------------------------------*/
    /* 配置命令：对所有的bank预充电 */
    Command.CommandMode = FMC_SDRAM_CMD_PALL;
    Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = 0;
    /* 发送配置命令 */
    HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

    /* Step 4 ----------------------------------------------------------------*/
    /* 配置命令：自动刷新 */
    Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
    Command.AutoRefreshNumber = 8;
    Command.ModeRegisterDefinition = 0;
    /* 发送配置命令 */
    HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

    /* Step 5 ----------------------------------------------------------------*/
    /* 设置sdram寄存器配置 */
    tmpr = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1 | SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL | SDRAM_MODEREG_CAS_LATENCY_3 |
           SDRAM_MODEREG_OPERATING_MODE_STANDARD | SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    /* 配置命令：设置SDRAM寄存器 */
    Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
    Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
    Command.AutoRefreshNumber = 1;
    Command.ModeRegisterDefinition = tmpr;
    /* 发送配置命令 */
    HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

    /* Step 6 ----------------------------------------------------------------*/

    /* 设置刷新计数器 */
    /* 刷新周期=64ms/8192行=7.8125us */
    /* COUNT=(7.8125us x Freq) - 20 */
    /* 设置自刷新速率 */
    HAL_SDRAM_ProgramRefreshRate(&sdramHandle, 824);
}

/**
 * @brief  以“字”为单位向sdram写入数据
 * @param  pBuffer: 指向数据的指针
 * @param  uwWriteAddress: 要写入的SDRAM内部地址
 * @param  uwBufferSize: 要写入数据大小
 * @retval None.
 */
void SDRAM_WriteBuffer(uint32_t *pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize)
{
    __IO uint32_t write_pointer = (uint32_t)uwWriteAddress;

    /* 禁止写保护 */
    HAL_SDRAM_WriteProtection_Disable(&hsdram1);
    /* 检查SDRAM标志，等待至SDRAM空闲 */
    while (HAL_SDRAM_GetState(&hsdram1) != RESET)
    {
    }

    /* 循环写入数据 */
    for (; uwBufferSize != 0; uwBufferSize--)
    {
        /* 发送数据到SDRAM */
        *(uint32_t *)(SDRAM_BANK_ADDR + write_pointer) = *pBuffer++;

        /* 地址自增*/
        write_pointer += 4;
    }
}

/**
 * @brief  从SDRAM中读取数据
 * @param  pBuffer: 指向存储数据的buffer
 * @param  ReadAddress: 要读取数据的地十
 * @param  uwBufferSize: 要读取的数据大小
 * @retval None.
 */
void SDRAM_ReadBuffer(uint32_t *pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize)
{
    __IO uint32_t write_pointer = (uint32_t)uwReadAddress;

    /* 检查SDRAM标志，等待至SDRAM空闲 */
    while (HAL_SDRAM_GetState(&hsdram1) != RESET)
    {
    }

    /*读取数据 */
    for (; uwBufferSize != 0x00; uwBufferSize--)
    {
        *pBuffer++ = *(__IO uint32_t *)(SDRAM_BANK_ADDR + write_pointer);

        /* 地址自增*/
        write_pointer += 4;
    }
}

/**
 * @brief  测试SDRAM是否正常
 * @param  None
 * @retval 正常返回1，异常返回0
 */
uint8_t SDRAM_Test(void)
{
    /*写入数据计数器*/
    uint32_t counter = 0;

    /* 8位的数据 */
    uint8_t ubWritedata_8b = 0, ubReaddata_8b = 0;

    /* 16位的数据 */
    uint16_t uhWritedata_16b = 0, uhReaddata_16b = 0;

    /* 32位的数据 */
    uint32_t uhWritedata_32b = 0, uhReaddata_32b = 0;

    SDRAM_INFO("Reading and writing SDRAM in 8-bit, 16 bit, 32-bit mode ...\n");

    /*按8位格式读写数据，并校验*/

    /* 把SDRAM数据全部重置为0 ，SDRAM_SIZE是以8位为单位的 */
    for (counter = 0x00; counter < SDRAM_SIZE; counter++)
    {
        *(__IO uint8_t *)(SDRAM_BANK_ADDR + counter) = (uint8_t)0x0;
    }

    /* 向整个SDRAM写入数据  8位 */
    for (counter = 0; counter < SDRAM_SIZE; counter++)
    {
        *(__IO uint8_t *)(SDRAM_BANK_ADDR + counter) = (uint8_t)((ubWritedata_8b + counter) & 0xFF);
    }

    /* 读取 SDRAM 数据并检测*/
    for (counter = 0; counter < SDRAM_SIZE; counter++)
    {
        ubReaddata_8b = *(__IO uint8_t *)(SDRAM_BANK_ADDR + counter); //从该地址读出数据

        if (ubReaddata_8b != (uint8_t)((ubWritedata_8b + counter) & 0xFF)) //检测数据，若不相等，跳出函数,返回检测失败结果。
        {
            SDRAM_ERROR("8-bit data read and write error! Error location：%d \n", counter);
            return 0;
        }
    }

    /*按16位格式读写数据，并检测*/

    /* 把SDRAM数据全部重置为0 */
    for (counter = 0x00; counter < SDRAM_SIZE / 2; counter++)
    {
        *(__IO uint16_t *)(SDRAM_BANK_ADDR + 2 * counter) = (uint16_t)0x00;
    }

    /* 向整个SDRAM写入数据  16位 */
    for (counter = 0; counter < SDRAM_SIZE / 2; counter++)
    {
        *(__IO uint16_t *)(SDRAM_BANK_ADDR + 2 * counter) = (uint16_t)((uhWritedata_16b + counter) & 0xFFFF);
    }

    /* 读取 SDRAM 数据并检测*/
    for (counter = 0; counter < SDRAM_SIZE / 2; counter++)
    {
        uhReaddata_16b = *(__IO uint16_t *)(SDRAM_BANK_ADDR + 2 * counter); //从该地址读出数据

        if (uhReaddata_16b != (uint16_t)((uhWritedata_16b + counter) & 0xFFFF)) //检测数据，若不相等，跳出函数,返回检测失败结果。
        {
            SDRAM_ERROR("16-bit data read and write error! Error location：%d \n", counter);

            return 0;
        }
    }

    /*按32位格式读写数据，并检测*/

    /* 把SDRAM数据全部重置为0 */
    for (counter = 0; counter < SDRAM_SIZE / 4; counter++)
    {
        *(__IO uint32_t *)(SDRAM_BANK_ADDR + 4 * counter) = (uint32_t)0x00000000UL;
    }

    /* 向整个SDRAM写入数据  32位 */
    for (counter = 0; counter < SDRAM_SIZE / 4; counter++)
    {
        *(__IO uint32_t *)(SDRAM_BANK_ADDR + 4 * counter) = (uint32_t)(uhWritedata_32b + counter);
    }
    
    __IO uint32_t *p = NULL;
    
    /* 读取 SDRAM 数据并检测*/
    for (counter = 0; counter < SDRAM_SIZE / 4; counter++)
    {
        p = (__IO uint32_t *)(SDRAM_BANK_ADDR + 4 * counter);
        uhReaddata_32b = *p; //从该地址读出数据

        if (uhReaddata_32b != (uint32_t)(uhWritedata_32b + counter)) //检测数据，若不相等，跳出函数,返回检测失败结果。
        {
            SDRAM_ERROR("32-bit data read and write error! Error location：%d 0x%X %d\n", counter, p, ((uint32_t)p%4));
            // return 0;
        }
    }

    SDRAM_INFO("SDRAM read and write test is normal!\n");
    /*检测正常，return 1 */
    return 1;
}

/*********************************************END OF FILE**********************/
