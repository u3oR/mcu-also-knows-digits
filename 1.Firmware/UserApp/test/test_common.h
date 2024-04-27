#ifndef _TEST_COMMON_H_
#define _TEST_COMMON_H_
/*********************************
 * Included Header Files
 *********************************/
#include <stdint.h>
#include "bsp/bsp_uart_debug.h"
/*********************************
 * Macro Definitions
 *********************************/
#define TEST_UART_DEBUG(x) uart_debug("[TEST]" x);
//#define TEST_UART_DEBUG(x) ((void)x)
/*********************************
 * Structure Definitions
 *********************************/

/*********************************
 * Global Variables
 *********************************/
 
/*********************************
 * External Function Implementations
 *********************************/

/*********************************
 * Public Function Declarations
 *********************************/
void test_sdram(void);
void test_armath(void);
void test_qspiflash(void);



#endif


