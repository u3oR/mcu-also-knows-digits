#ifndef _CREATE_WAVE_H
#define _CREATE_WAVE_H
#include "arm_math.h"

void create_wave_f32(   float32_t wave[], 
                        const uint32_t wave_len, 
                        const uint32_t fs, 
                        const float32_t freq[],
                        const float32_t mag[], 
                        const uint32_t freq_mag_len);

#endif
