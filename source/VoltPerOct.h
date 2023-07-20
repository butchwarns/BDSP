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

        private:
            float zero_freq;
        };

    } // namespace cv
} // namespace bdsp

#endif // __VOLT_PER_OCT_H__