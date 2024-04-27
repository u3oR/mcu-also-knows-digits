

/*********************************
 * Included Header Files
 *********************************/
#include <stdint.h>
#include "arm_math.h"
#include "bsp/bsp_uart_debug.h"
#include "test/test_common.h"
/*********************************
 * Macro Definitions
 *********************************/
#define TEST_LENGTH_SAMPLES (32)
/*********************************
 * Private Global Variables
 *********************************/
static float32_t test_input_data[TEST_LENGTH_SAMPLES] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

static float32_t test_hamming_data[TEST_LENGTH_SAMPLES] = {0};
static float32_t test_output_data[TEST_LENGTH_SAMPLES] = {0};
static float32_t test_output_data_mag[TEST_LENGTH_SAMPLES] = {0};
/*********************************
 * External Function Implementations
 *********************************/
void test_armath(void)
{
//    static float32_t test_input_data[TEST_LENGTH_SAMPLES] = {
//      1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//      1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//      1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//      1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};

    arm_hamming_f32(test_hamming_data, TEST_LENGTH_SAMPLES);

    arm_mult_f32(test_input_data, test_hamming_data, test_input_data, TEST_LENGTH_SAMPLES);

    TEST_UART_DEBUG("<CMSIS-DSP-1.15.0 rfft test >\n");

    arm_rfft_fast_instance_f32 rfft_ins;

    arm_rfft_fast_init_f32(&rfft_ins, TEST_LENGTH_SAMPLES);
    TEST_UART_DEBUG("CMSIS-DSP rfft init ok \n");

    uint8_t irfftFlag = 0;

    arm_rfft_fast_f32(&rfft_ins, test_input_data, test_output_data, irfftFlag);
    TEST_UART_DEBUG("CMSIS-DSP rfft calc ok \n");

//    for (int i = 0; i < TEST_LENGTH_SAMPLES / 2; ++i)
//    {
//        user_debug("%.2f+%.2fj, ", test_output_data[2 * i], test_output_data[2 * i + 1]);
//        if (i % 8 == 0)
//            user_debug("\n");
//    }

    TEST_UART_DEBUG("CMSIS-DSP rfft calc mag test\n");
    
    arm_cmplx_mag_f32(test_output_data, test_output_data_mag, TEST_LENGTH_SAMPLES / 2);

//    for (int i = 0; i < TEST_LENGTH_SAMPLES / 2; ++i)
//    {
//        user_debug("%.2f,", test_output_data_mag[i]);
//        if (i % 8 == 0)
//            user_debug("\n");
//    }
}


