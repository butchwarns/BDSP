#include "SmootherLinear.h"

namespace bdsp::smoother
{

    template <typename FloatType>
    SmootherLinear<FloatType>::SmootherLinear()
        : sample_rate(1.0), num_frames(1.0f), target_val(0.0f), state(0.0f), delta(0.0f)
    {
    }

    template <typename FloatType>
    void SmootherLinear<FloatType>::reset(FloatType _sample_rate)
    {
        state = 0.0;
        sample_rate = _sample_rate;
    }

    template <typename FloatType>
    void SmootherLinear<FloatType>::set_time_constant(FloatType time_constant)
    {
        num_frames = time_constant * sample_rate;
    }

    template <typename FloatType>
    void SmootherLinear<FloatType>::set_target_val(FloatType _target_val)
    {
        target_val = _target_val;
        delta = (target_val - state) / num_frames;
    }

    template <typename FloatType>
    FloatType SmootherLinear<FloatType>::next()
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

    template class SmootherLinear<float>;
    template class SmootherLinear<double>;

} // namespace bdsp::smoother