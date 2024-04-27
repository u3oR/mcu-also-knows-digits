#include "utils/create_wave_f32.h"
#include "arm_math.h"

void create_wave_f32(   float32_t wave[], 
                        const uint32_t wave_len, 
                        const uint32_t fs, 
                        const float32_t factor_freq[],
                        const float32_t factor_mag[], 
                        const uint32_t freq_mag_len)
{
    if(fs <= 0) return;
    
    float32_t wt = (float32_t)1.0f / fs;

    for (uint32_t i = 0; i < wave_len; i++)
    {
        wave[i] = 0.0f;

        for (uint32_t j = 0; j < freq_mag_len; j++)
        {
            wave[i] += factor_mag[j] * arm_sin_f32(2 * PI * i * factor_freq[j] * wt);
        }
    }
}
