#ifndef UTILITY_H
#define UTILITY_H

#include <limits>

typedef std::numeric_limits<float> flt;

namespace bdsp::utility
{

    /**
     * @brief sgn(x), signum function
     *
     * @tparam T Integral or floating-point type
     * @param x
     * @return 1 if x > 0
     * 0 if x = 0,
     * -1 if x < 0
     */
    template <typename T>
    inline int sgn(T x)
    {
        return (static_cast<T>(0.0) < x) - (x < static_cast<T>(0.0));
    }

    /**
     * @brief Fix possible float underflows before casting from double to avoid denormals
     *
     * @param d double value to be checked for possible underflow
     */
    inline void fixUnderflow(double &d)
    {
        // Positive underflow
        const bool underflow_positive = d > 0.0 && d < flt::min();
        // Negative underflow
        const bool underflow_negative = d < 0.0 && d > -flt::min();

        // Fix
        if (underflow_positive || underflow_negative)
        {
            d = 0.0;
        }
    }

    /**
     * @brief Clamps value to given interval
     *
     * @tparam T floating-point type
     * @param x Value to clamp
     * @param min Lower bound
     * @param max Upper bound
     * @return Clamped value
     */
    template <typename T>
    inline T clamp(T x, T min = static_cast<T>(-1.0), T max = static_cast<T>(1.0))
    {
        if (x < min)
        {
            x = min;
        }
        if (x > max)
        {
            x = max;
        }

        return x;
    }

} // namespace bdsp::utility

#endif // UTILITY_H