
/**
 ******************************************************************************
 * @file    app_x-cube-ai.c
 * @author  X-CUBE-AI C code generator
 * @brief   AI program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/*
 * Description
 *   v1.0 - Minimum template to show how to use the Embedded Client API
 *          model. Only one input and one output is supported. All
 *          memory resources are allocated statically (AI_NETWORK_XX, defines
 *          are used).
 *          Re-target of the printf function is out-of-scope.
 *   v2.0 - add multiple IO and/or multiple heap support
 *
 *   For more information, see the embeded documentation:
 *
 *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
 *
 *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
 *   typical : C:\Users\<user_name>\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\7.1.0
 */

#ifdef __cplusplus
extern "C"
{
#endif

    /* Includes ------------------------------------------------------------------*/

#if defined(__ICCARM__)
#elif defined(__CC_ARM) || (__GNUC__)
#endif

/* System headers */
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ai_datatypes_defines.h"
#include "app_x-cube-ai.h"
#include "main.h"
#include "mnist.h"
#include "mnist_data.h"

/* USER CODE BEGIN includes */
#include "bsp/bsp_uart_debug.h"
#include "user_main.h"
#include "arm_math.h"
    /* USER CODE END includes */

    /* IO buffers ----------------------------------------------------------------*/

#if !defined(AI_MNIST_INPUTS_IN_ACTIVATIONS)
    AI_ALIGNED(4) ai_i8 data_in_1[AI_MNIST_IN_1_SIZE_BYTES];
    ai_i8 *data_ins[AI_MNIST_IN_NUM] = {data_in_1};
#else
ai_i8 *data_ins[AI_MNIST_IN_NUM] = {NULL};
#endif

#if !defined(AI_MNIST_OUTPUTS_IN_ACTIVATIONS)
    AI_ALIGNED(4) ai_i8 data_out_1[AI_MNIST_OUT_1_SIZE_BYTES];
    ai_i8 *data_outs[AI_MNIST_OUT_NUM] = {data_out_1};
#else
ai_i8 *data_outs[AI_MNIST_OUT_NUM] = {NULL};
#endif

    /* Activations buffers -------------------------------------------------------*/

    AI_ALIGNED(32)
    static uint8_t pool0[AI_MNIST_DATA_ACTIVATION_1_SIZE];

    ai_handle data_activations0[] = {pool0};

    /* AI objects ----------------------------------------------------------------*/

    static ai_handle mnist = AI_HANDLE_NULL;

    static ai_buffer *ai_input;
    static ai_buffer *ai_output;

    static void ai_log_err(const ai_error err, const char *fct)
    {
        /* USER CODE BEGIN log */
        if (fct)
            uart_debug("TEMPLATE - Error (%s) - type=0x%02x code=0x%02x\r\n", fct, err.type, err.code);
        else
            uart_debug("TEMPLATE - Error - type=0x%02x code=0x%02x\r\n", err.type, err.code);

        do
        {
        } while (1);
        /* USER CODE END log */
    }

    static int ai_boostrap(ai_handle *act_addr)
    {
        ai_error err;

        /* Create and initialize an instance of the model */
        err = ai_mnist_create_and_init(&mnist, act_addr, NULL);
        if (err.type != AI_ERROR_NONE)
        {
            ai_log_err(err, "ai_mnist_create_and_init");
            return -1;
        }

        ai_input = ai_mnist_inputs_get(mnist, NULL);
        ai_output = ai_mnist_outputs_get(mnist, NULL);

#if defined(AI_MNIST_INPUTS_IN_ACTIVATIONS)
        /*  In the case where "--allocate-inputs" option is used, memory buffer can be
         *  used from the activations buffer. This is not mandatory.
         */
        for (int idx = 0; idx < AI_MNIST_IN_NUM; idx++)
        {
            data_ins[idx] = ai_input[idx].data;
        }
#else
    for (int idx = 0; idx < AI_MNIST_IN_NUM; idx++)
    {
        ai_input[idx].data = data_ins[idx];
    }
#endif

#if defined(AI_MNIST_OUTPUTS_IN_ACTIVATIONS)
        /*  In the case where "--allocate-outputs" option is used, memory buffer can be
         *  used from the activations buffer. This is no mandatory.
         */
        for (int idx = 0; idx < AI_MNIST_OUT_NUM; idx++)
        {
            data_outs[idx] = ai_output[idx].data;
        }
#else
    for (int idx = 0; idx < AI_MNIST_OUT_NUM; idx++)
    {
        ai_output[idx].data = data_outs[idx];
    }
#endif

        return 0;
    }

    static int ai_run(void)
    {
        ai_i32 batch;

        batch = ai_mnist_run(mnist, ai_input, ai_output);
        if (batch != 1)
        {
            ai_log_err(ai_mnist_get_error(mnist), "ai_mnist_run");
            return -1;
        }

        return 0;
    }

    /* USER CODE BEGIN 2 */
    #include "utils/mnist_test_data/mnist_test_data.h"
//    extern float32_t uart_image_buffer[784];
    int acquire_and_process_data(ai_i8 *data[])
    {
        /* fill the inputs of the c-model */
        for (int idx=0; idx < AI_MNIST_IN_NUM; idx++ )
        {
            ai_i8 *p = data[idx];
            
            for (int i = 0; i < AI_MNIST_IN_1_SIZE; i++)
            {
                *((ai_float *)(p + i * 4)) = image_data[i];
            }
        }
        
        return 0;
    }

    int post_process(ai_i8 *data[])
    {
        /* process the predictions */
        for (int idx = 0; idx < AI_MNIST_OUT_NUM; idx++)
        {
            float32_t max_val = 0;
            uint32_t  max_idx = 0;
            
            for (int i = 0; i < AI_MNIST_OUT_1_SIZE; i++)
            {
                uart_debug("post_process %d = %f\n", i, *((ai_float *)(data[idx] + i * 4)));
            }
            
            arm_max_f32((float *)(data[idx]), 10, &max_val, &max_idx);
            
            uart_debug("the closest number is %d, with a probability of %.5f\n", max_idx, max_val);
        }

        return 0;
    }
    /* USER CODE END 2 */

    /* Entry points --------------------------------------------------------------*/

    void MX_X_CUBE_AI_Init(void)
    {
        /* USER CODE BEGIN 5 */
        uart_debug("\r\nTEMPLATE - initialization\r\n");

        ai_boostrap(data_activations0);
        /* USER CODE END 5 */
    }

    void MX_X_CUBE_AI_Process(void)
    {
        /* USER CODE BEGIN 6 */
        int res = -1;

        // uart_debug("TEMPLATE - run - main loop\r\n");

        if (mnist)
        {
            // uart_debug("TEMPLATE - run - mnist\r\n");
            do
            {
                /* 1 - acquire and pre-process input data */
                res = acquire_and_process_data(data_ins);
                /* 2 - process the data - call inference engine */
                if (res == 0)
                    res = ai_run();
                /* 3- post-process the predictions */
                if (res == 0)
                    res = post_process(data_outs);
            } while (0);
            //} while (res == 0);
        }

        if (res)
        {
            ai_error err = {AI_ERROR_INVALID_STATE, AI_ERROR_CODE_NETWORK};
            ai_log_err(err, "Process has FAILED");
        }
        /* USER CODE END 6 */
    }
#ifdef __cplusplus
}
#endif
