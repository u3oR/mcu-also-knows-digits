
// ActivationFunctions
#include "ActivationFunctions/arm_nn_activations_q7.c"
#include "ActivationFunctions/arm_nn_activations_q15.c"
#include "ActivationFunctions/arm_relu_q7.c"
#include "ActivationFunctions/arm_relu_q15.c"

// ConvolutionFunctions
#include "ConvolutionFunctions/arm_convolve_1x1_HWC_q7_fast_nonsquare.c"
#include "ConvolutionFunctions/arm_convolve_HWC_q7_basic.c"
#include "ConvolutionFunctions/arm_convolve_HWC_q7_basic_nonsquare.c"
#include "ConvolutionFunctions/arm_convolve_HWC_q7_fast.c"
#include "ConvolutionFunctions/arm_convolve_HWC_q7_fast_nonsquare.c"
#include "ConvolutionFunctions/arm_convolve_HWC_q7_RGB.c"
#include "ConvolutionFunctions/arm_convolve_HWC_q15_basic.c"
#include "ConvolutionFunctions/arm_convolve_HWC_q15_fast.c"
#include "ConvolutionFunctions/arm_convolve_HWC_q15_fast_nonsquare.c"
#include "ConvolutionFunctions/arm_depthwise_conv_u8_basic_ver1.c"
#include "ConvolutionFunctions/arm_depthwise_separable_conv_HWC_q7.c"
#include "ConvolutionFunctions/arm_depthwise_separable_conv_HWC_q7_nonsquare.c"
#include "ConvolutionFunctions/arm_nn_mat_mult_kernel_q7_q15.c"
#include "ConvolutionFunctions/arm_nn_mat_mult_kernel_q7_q15_reordered.c"

// FullyConnectedFunctions
#include "FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15.c"
#include "FullyConnectedFunctions/arm_fully_connected_mat_q7_vec_q15_opt.c"
#include "FullyConnectedFunctions/arm_fully_connected_q7.c"
#include "FullyConnectedFunctions/arm_fully_connected_q7_opt.c"
#include "FullyConnectedFunctions/arm_fully_connected_q15.c"
#include "FullyConnectedFunctions/arm_fully_connected_q15_opt.c"

// NNSupportFunctions
#include "NNSupportFunctions/arm_nn_mult_q7.c"
#include "NNSupportFunctions/arm_nn_mult_q15.c"
#include "NNSupportFunctions/arm_nntables.c"
#include "NNSupportFunctions/arm_q7_to_q15_no_shift.c"
#include "NNSupportFunctions/arm_q7_to_q15_reordered_no_shift.c"

// PoolingFunctions
#include "PoolingFunctions/arm_pool_q7_HWC.c"

// SoftmaxFunctions
#include "SoftmaxFunctions/arm_softmax_q7.c"
#include "SoftmaxFunctions/arm_softmax_q15.c"
