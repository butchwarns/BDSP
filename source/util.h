#ifndef __UTIL_H__
#define __UTIL_H__

#include <limits>

typedef std::numeric_limits<float> flt;

namespace bdsp::util
{
    /**
     * @brief @f$ \pi @f$
     */
    constexpr double PI =
        3.14159265358979323846264338327950288419716939937510582097494459230781640628620899;

    /**
     * @brief @f$ 2\pi @f$
     */
    constexpr double TWO_PI =
        2.0 *
        3.14159265358979323846264338327950288419716939937510582097494459230781640628620899;

    /**
     * @brief sgn(x), signum function
     *
     * @tparam T Integral or floating point type
     * @param x
     * @return 1 if x > 0
     * 0 if x = 0,
     * -1 if x < 0
     */
    template <typename T = double>
    inline int sgn(T x)
    {
        return (static_cast<T>(0) < x) - (x < static_cast<T>(0));
    }

    /**
     * @brief Fix possible float underflows before casting from double to avoid denormals
     *
     * @param d double value to be checked for possible underflow
     * @return true if underflow was fixed
     * @return false if no underflow occured
     */
    inline void fixUnderflow(double &d)
    {
        // Positive underflow
        if (d > 0.0 && d < flt::min())
        {
            d = 0.0;
        }
        // Negative underflow
        else if (d < 0.0 && d > -flt::min())
        {
            d = 0.0;
        }
    }

    /**
     * @brief Convert value from bipolar to unipolar range
     *
     * @tparam T float or double
     * @param x Bipolar value in range [-1.0, 1.0]
     * @return Corresponding unipolar value in range [0.0, 1.0]
     */
    template <typename T = double>
    inline T bipolarToUnipolar(T x)
    {
        return static_cast<T>(0.5) * x + static_cast<T>(0.5);
    }

    /**
     * @brief Convert value from unipolar to bipolar range
     *
     * @tparam T float or double
     * @param x Unipolar value in range [0.0, 1.0]
     * @return Corresponding bipolar value in range [-1.0, 1.0]
     */
    template <typename T = double>
    inline T unipolarToBipolar(T x)
    {
        return (x - static_cast<T>(0.5)) * static_cast<T>(2.0);
    }
} // namespace bdsp::util
#endif // __UTIL_H__