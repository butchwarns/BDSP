#include "SmootherLinear.h"

namespace bdsp::smoother
{

    SmootherLinear::SmootherLinear()
        : sample_rate(1.0), num_frames(1.0f), target_val(0.0f), state(0.0f), delta(0.0f)
    {
    }

    void SmootherLinear::reset(double _sample_rate)
    {
        state = 0.0;
        sample_rate = _sample_rate;
    }

    void SmootherLinear::set_time_constant(float time_constant)
    {
        num_frames = time_constant * (float)sample_rate;
    }

    void SmootherLinear::set_target_val(float _target_val)
    {
        target_val = _target_val;
        delta = (target_val - state) / num_frames;
    }

    float SmootherLinear::next()
    {
        // Rising
        if (delta >= 0.0f)
        {
            if (state >= target_val)
            {
                delta = 0.0f;
            }
        }
        // Falling
        else
        {
            if (state <= target_val)
            {
                delta = 0.0f;
            }
        }

        state += delta;
        return state;
    }

} // namespace bdsp::smoother