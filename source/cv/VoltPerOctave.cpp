#include "VoltPerOctave.h"

namespace bdsp::cv
{

    VoltPerOctave::VoltPerOctave()
        : zero_volt_freq(ZERO_VOLT_FREQ_DEFAULT)
    {
    }

    VoltPerOctave::VoltPerOctave(float _zero_volt_freq)
        : zero_volt_freq(_zero_volt_freq)
    {
    }

    void VoltPerOctave::tune(float _zero_volt_freq)
    {
        zero_volt_freq = _zero_volt_freq;
    }

    float VoltPerOctave::volt_to_freq(float volt) const
    {
        return zero_volt_freq * powf(2.0f, volt);
    }

    float VoltPerOctave::freq_to_volt(float freq) const
    {
        return log2f(freq / zero_volt_freq);
    }

    float VoltPerOctave::volt_to_freq(float volt, float zero_volt_freq)
    {
        return zero_volt_freq * powf(2.0f, volt);
    }

    float VoltPerOctave::freq_to_volt(float freq, float zero_volt_freq)
    {
        return log2f(freq / zero_volt_freq);
    }

} // namespace bdsp::cv