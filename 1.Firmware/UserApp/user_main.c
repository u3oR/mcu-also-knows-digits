/*********************************
 * Included Header Files
 *********************************/
#include "user_main.h"
#include <stdint.h>

#include "main.h"
#include "usart.h"
// cmsis dsp
#include "arm_math.h"
// bsp
#include "bsp/bsp_qspi_flash.h"
#include "bsp/bsp_sdram.h"
#include "bsp/bsp_uart_debug.h"
// FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
// test
#include "test/test_common.h"
// nn
#include "app_x-cube-ai.h"

/*********************************
 * Macro Definitions
 *********************************/

/*********************************
 * Global Variables
 *********************************/

__AT_ZERO__("0xD0000000")
float32_t uart_image_buffer[784] = {0};

static SemaphoreHandle_t xMutex;
/*********************************
 * Private Function Declarations
 *********************************/

/*********************************
 * Macro Functions
 *********************************/

/*********************************
 * Private Function Implementations
 *********************************/
void task_mnist_nn(void *arg)
{
    ((void)arg);
    
    while(1) {
//        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE)
//        {
//            MX_X_CUBE_AI_Process();
//            xSemaphoreGive(xMutex);
//        }
        
        MX_X_CUBE_AI_Process();
        vTaskDelay(2000);
    }
}

void task_get_image(void *arg)
{
    ((void)arg);
    
    while(1) {
        vTaskDelay(2000);
    }
}
/*********************************
 * Public Function Implementations
 *********************************/
void user_main()
{
    SDRAM_InitSequence();
    BSP_QSPI_Init();
    QSPI_ResetMemory();
    QSPI_EnableMemoryMappedMode();

    test_sdram();
    test_armath();
    test_qspiflash();

    MX_X_CUBE_AI_Init();

    
    xTaskCreate(task_mnist_nn,  "mnist_nn",             1024, NULL, 0, NULL);
    xTaskCreate(task_get_image, "task_uart_get_image",  1024, NULL, 0, NULL);
//    xMutex = xSemaphoreCreateMutex();

    vTaskStartScheduler();
    
    while (1);

    Error_Handler();
}
