#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <limits>

typedef std::numeric_limits<float> flt;

namespace bdsp
{
    namespace utility
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

    } // namespace utility
} // namespace bdsp

#endif // __UTILITY_H__