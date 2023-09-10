#ifndef __VOLT_PER_OCT_H__
#define __VOLT_PER_OCT_H__

#include "consts.h"

namespace bdsp
{
    namespace cv
    {

        class VoltPerOct
        {
        public:
            VoltPerOct();
            VoltPerOct(float _zero_freq);
            ~VoltPerOct();

            void tune(float _zero_freq);

            float volt_to_freq(float volt);
            float freq_to_volt(float freq);
            static float volt_to_freq(float volt, float zero_volt_freq);
            static float freq_to_volt(float freq, float zero_volt_freq);

        private:
            float zero_freq;
        };

    } // namespace cv
} // namespace bdsp

#endif // __VOLT_PER_OCT_H__