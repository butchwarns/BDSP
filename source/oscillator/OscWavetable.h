#ifndef OSC_WAVETABLE_H
#define OSC_WAVETABLE_H

#include "../../tables/wavetables/SINE4096.h"
#include "../mappings.h"

namespace bdsp::oscillator
{

    class OscWavetable
    {
    public:
        OscWavetable();
        ~OscWavetable() = default;

        void reset(double _sample_rate);
        void set_freq(float _freq);

        float process();

    private:
        double sample_rate;
        float idx;   // Current read index
        float freq;  // Oscillator tuning
        float delta; // Index increment per sample
        void update_delta();

        const float *const wavetable;
        const int table_len;

        float lookup(float index);
    };

} // namespace bdsp::oscillator

#endif // OSC_WAVETABLE_H