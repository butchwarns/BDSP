#ifndef __OSC_WAVETABLE_H__
#define __OSC_WAVETABLE_H__

#include "../../tables/wavetables/sine4096.h"
#include "../maps.h"

namespace bdsp
{
    namespace osc
    {

        class OscWavetable
        {
        public:
            OscWavetable();
            ~OscWavetable();

            //==============================================================================

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

            float lookup(float index);
        };

    } // namespace osc
} // namespace bdsp

#endif // __OSC_WAVETABLE_H__