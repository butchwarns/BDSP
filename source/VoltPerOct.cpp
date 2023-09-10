#include "VoltPerOct.h"

namespace bdsp
{
    namespace cv
    {

        VoltPerOct::VoltPerOct()
            : zero_freq(consts::MIN_FILTER_FREQ * powf(2.0f, 5.0f)) // Default tune to standard +-5V CV
        {
        }

        VoltPerOct::VoltPerOct(float _zero_freq)
            : zero_freq(_zero_freq)
        {
        }

        VoltPerOct::~VoltPerOct()
        {
        }

        void VoltPerOct::tune(float _zero_freq)
        {
            zero_freq = _zero_freq;
        }

        float VoltPerOct::volt_to_freq(float volt)
        {
            return zero_freq * powf(2.0f, volt);
        }

        float VoltPerOct::freq_to_volt(float freq)
        {
            return log2f(freq / zero_freq);
        }

        float VoltPerOct::volt_to_freq(float volt, float zero_volt_freq)
        {
            return zero_volt_freq * powf(2.0f, volt);
        }

        float VoltPerOct::freq_to_volt(float freq, float zero_volt_freq)
        {
            return log2f(freq / zero_volt_freq);
        }

    } // namespace cv
} // namespace bdsp