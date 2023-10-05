#ifndef VOLT_PER_OCTAVE_H
#define VOLT_PER_OCTAVE_H

#include "constants.h"

namespace bdsp::cv
{

    // Default tune to standard +-5V CV / 10 ocatve range
    const float ZERO_VOLT_FREQ_DEFAULT = (float)constants::MIN_FILTER_FREQ * powf(2.0f, 5.0f);

    class VoltPerOctave
    {
    public:
        VoltPerOctave();
        explicit VoltPerOctave(float _zero_volt_freq);
        ~VoltPerOctave() = default;

        void tune(float _zero_volt_freq);

        float volt_to_freq(float volt) const;
        float freq_to_volt(float freq) const;
        static float volt_to_freq(float volt, float zero_volt_freq);
        static float freq_to_volt(float freq, float zero_volt_freq);

    private:
        float zero_volt_freq;
    };

} // namespace bdsp::cv

#endif // VOLT_PER_OCTAVE_H