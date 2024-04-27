

/*********************************
 * Included Header Files
 *********************************/
#include <stdint.h>
#include "user_main.h"
#include "test/test_common.h"
#include "bsp/bsp_qspi_flash.h"
#include "bsp/bsp_uart_debug.h"
/*********************************
 * Macro Definitions
 *********************************/

/*********************************
 * Global Variables
 *********************************/
__AT_EXFLASH__
const static volatile uint32_t qspi_test_arr[10] = {
    0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL, 0xFFFFFFFFUL,
    0xA1B2C3D4UL, 0xA1B2C3D4UL, 0xA1B2C3D4UL, 0xA1B2C3D4UL, 0xA1B2C3D4UL,
};
/*********************************
 * External Function Implementations
 *********************************/
void test_qspiflash(void)
{
    TEST_UART_DEBUG("<QSPIFLASH TEST START>\n");

    for (int i = 0; i < 10; i++)
    {
        if (i < 5)
        {
            if(!(qspi_test_arr[i] == 0xFFFFFFFFUL))
            {
                TEST_UART_DEBUG("QSPIFLASH TEST ERROR\n");
                do{}while(1);
            }
        }
        else
        {
            if(!(qspi_test_arr[i] == 0xA1B2C3D4UL))
            {
                TEST_UART_DEBUG("QSPIFLASH TEST ERROR\n");
                do{}while(1);
            }
        }
    }

    TEST_UART_DEBUG("QSPIFLASH TEST OVER\n");
}
