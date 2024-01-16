#include "VoltPerOctave.h"

namespace bdsp::cv
{

    template <typename FloatType>
    VoltPerOctave<FloatType>::VoltPerOctave()
        : zero_volt_freq((FloatType)ZERO_VOLT_FREQ_DEFAULT)
    {
    }

    template <typename FloatType>
    VoltPerOctave<FloatType>::VoltPerOctave(FloatType _zero_volt_freq)
        : zero_volt_freq(_zero_volt_freq)
    {
    }

    template <typename FloatType>
    void VoltPerOctave<FloatType>::tune(FloatType _zero_volt_freq)
    {
        zero_volt_freq = _zero_volt_freq;
    }

    template <>
    float VoltPerOctave<float>::volt_to_freq(float volt) const
    {
        return zero_volt_freq * powf(2.0f, volt);
    }

    template <>
    double VoltPerOctave<double>::volt_to_freq(double volt) const
    {
        return zero_volt_freq * pow(2.0, volt);
    }

    template <>
    float VoltPerOctave<float>::freq_to_volt(float freq) const
    {
        return log2f(freq / zero_volt_freq);
    }

    template <>
    double VoltPerOctave<double>::freq_to_volt(double freq) const
    {
        return log2(freq / zero_volt_freq);
    }

    template <>
    float VoltPerOctave<float>::volt_to_freq(float volt, float zero_volt_freq)
    {
        return zero_volt_freq * powf(2.0f, volt);
    }

    template <>
    double VoltPerOctave<double>::volt_to_freq(double volt, double zero_volt_freq)
    {
        return zero_volt_freq * pow(2.0, volt);
    }

    template <>
    float VoltPerOctave<float>::freq_to_volt(float freq, float zero_volt_freq)
    {
        return log2f(freq / zero_volt_freq);
    }

    template <>
    double VoltPerOctave<double>::freq_to_volt(double freq, double zero_volt_freq)
    {
        return log2(freq / zero_volt_freq);
    }

    template class VoltPerOctave<float>;
    template class VoltPerOctave<double>;

} // namespace bdsp::cv