#include "OscWavetable.h"

namespace bdsp::oscillator
{

    OscWavetable::OscWavetable()
        : sample_rate(48000),
          idx(0.0f),
          freq(0.0f),
          delta(0.0f),
          wavetable(bdsp::wavetable::SINE4096),
          table_len(4096)
    {
    }

    void OscWavetable::reset(double _sample_rate)
    {
        sample_rate = _sample_rate;
        idx = 0.0f;
    }

    void OscWavetable::set_freq(float _freq)
    {
        freq = _freq;
        update_delta();
    }

    float OscWavetable::process()
    {
        // Perform interpolated table lookup at current read index
        // to find output sample
        const float y = lookup(idx);

        // Increment current read index
        idx += delta;

        // Keep index from wrapping erroneously due to overflow
        if (idx >= static_cast<float>(table_len - 1))
        {
            idx -= (float)table_len;
        }

        // Output
        return y;
    }

    void OscWavetable::update_delta()
    {
        delta = (float)((float)table_len * freq / sample_rate);
    }

    float OscWavetable::lookup(float index)
    {
        // Split index into integer and fractional parts
        const int idx_int = static_cast<int>(index);
        const float idx_frac = index - (float)idx_int;

        // Wrap indices
        const int idx0 = idx_int % table_len;
        const int idx1 = (idx_int + 1) % table_len;

        // Read adjacent samples
        const float x0 = wavetable[idx0];
        const float x1 = wavetable[idx1];

        // Interpolate to find output
        const float y = bdsp::mappings::linear_norm(idx_frac, x0, x1);

        return y;
    }

} // namespace bdsp::oscillator