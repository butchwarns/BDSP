#ifndef VOLT_PER_OCTAVE_H
#define VOLT_PER_OCTAVE_H

#include "../constants.h"

namespace bdsp::cv
{

    // Default tune to standard +-5V CV / 10 ocatve range
    const double ZERO_VOLT_FREQ_DEFAULT = constants::MIN_FILTER_FREQ * pow(2.0, 5.0);

    template <typename FloatType>
    class VoltPerOctave
    {
    public:
        VoltPerOctave();
        explicit VoltPerOctave(FloatType _zero_volt_freq);
        ~VoltPerOctave() = default;

        void tune(FloatType _zero_volt_freq);

        FloatType volt_to_freq(FloatType volt) const;
        FloatType freq_to_volt(FloatType freq) const;
        static float volt_to_freq(float volt, float zero_volt_freq);
        static double volt_to_freq(double volt, double zero_volt_freq);
        static float freq_to_volt(float freq, float zero_volt_freq);
        static double freq_to_volt(double freq, double zero_volt_freq);

    private:
        FloatType zero_volt_freq;
    };

} // namespace bdsp::cv

#endif // VOLT_PER_OCTAVE_H