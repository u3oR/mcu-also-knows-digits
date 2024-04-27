#ifndef _BSP_UART_DEBUG_H
#define _BSP_UART_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
* include
*********************/
#include "main.h"
#include "usart.h"
/*********************
 * define
 *********************/
#define USERDEBUG_UART_HANDLE huart1
#define USERDEBUG_BUFFER_SIZE 128 /*byte*/

#define ENABLE_USERDEBUG 1
/*********************
 * function
 *********************/

int uart_debug(const char *,...);

#ifdef __cplusplus
}
#endif

#endif //_SERIAL_H
