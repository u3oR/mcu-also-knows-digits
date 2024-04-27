

/*********************************
 * Included Header Files
 *********************************/
#include <stdint.h>
#include "bsp/bsp_sdram.h"
#include "bsp/bsp_uart_debug.h"
#include "test/test_common.h"
/*********************************
 * Macro Definitions
 *********************************/
#define SDRAM_4BYTE_LEN (SDRAM_SIZE/4)
/*********************************
 * External Function Implementations
 *********************************/
void test_sdram(void)
{
    TEST_UART_DEBUG("<SDRAM TEST START>\n");
    
    uint32_t count;
   
    volatile uint32_t *pSDRAM = (volatile uint32_t *)SDRAM_BANK_ADDR;
    
    for (count = 0; count < SDRAM_4BYTE_LEN; count++)
    {
        //*pSDRAM = (0xE1D2C3B0 ^ (uint32_t)pSDRAM) ^ (count + 3);
        *pSDRAM = 0xFFFFFFFFUL;
        //*pSDRAM = 0x00000000UL;
        // user_debug("val:0x%8X, addr:0x%8X, cnt:%lld,  \r\n", *pSDRAM, (uint32_t)pSDRAM, count);
        pSDRAM++;
    }
    
    TEST_UART_DEBUG("SDRAM TEST HALF\n");

    HAL_Delay(300);

    pSDRAM = (volatile uint32_t *)SDRAM_BANK_ADDR;

    for (count = 0; count < SDRAM_4BYTE_LEN; count++)
    {

        // user_debug("val:0x%8X, addr:0x%8X, cnt:%lld, \n", *pSDRAM, (uint32_t)pSDRAM, count);
        //if(*pSDRAM != ((0xE1D2C3B0 ^ (uint32_t)pSDRAM) ^ (count + 3)) )
        if(*pSDRAM != (0xFFFFFFFFUL) )
        //if (*pSDRAM != (0x00000000UL))
        {
            TEST_UART_DEBUG("SDRAM TEST ERROR\n");
            break;
        }
        pSDRAM++;
    }

    TEST_UART_DEBUG("SDRAM TEST OVER\n");
}

