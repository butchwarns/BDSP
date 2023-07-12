#include "OscWavetable.h"

OscWavetable::OscWavetable()
    : sample_rate(48000), idx(0.0f), freq(0.0f), delta(0.0f), wavetable(sine4096)
{
}

OscWavetable::~OscWavetable()
{
}

//==============================================================================

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
    if (idx >= static_cast<float>(SINE4096_LEN - 1))
    {
        idx -= SINE4096_LEN;
    }

    // Output
    return y;
}

//==============================================================================

void OscWavetable::update_delta()
{
    delta = static_cast<float>(SINE4096_LEN) * freq / sample_rate;
}

float OscWavetable::lookup(float index)
{
    // Split index into integer and fractional parts
    const int idx_int = static_cast<int>(index);
    const float idx_frac = index - idx_int;

    // Wrap indices
    const int idx0 = idx_int % SINE4096_LEN;
    const int idx1 = (idx_int + 1) % SINE4096_LEN;

    // Read adjacent samples
    const float x0 = wavetable[idx0];
    const float x1 = wavetable[idx1];

    // Interpolate to find output
    const float y = bdsp::maps::map_linear_norm_pos(idx_frac, x0, x1);

    return y;
}