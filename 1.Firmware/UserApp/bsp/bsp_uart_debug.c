
#include "bsp/bsp_uart_debug.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int uart_debug(const char *fmt, ...)
{
#if (ENABLE_USERDEBUG != 0U)
    int size = 0;
    char buf[USERDEBUG_BUFFER_SIZE];
    char *p = buf;

    va_list arg_list;
    va_start(arg_list, fmt);

    vsprintf(buf, fmt, arg_list);
    while (*p++)
        size++; /*计算字符串大小*/

    int ret = HAL_UART_Transmit(&USERDEBUG_UART_HANDLE, (uint8_t *)buf, size, 10);
    va_end(arg_list);
    return ret;
#else
    return 0;
#endif
}
