#ifndef __UTIL_H__
#define __UTIL_H__

#include <limits>

typedef std::numeric_limits<float> flt;

namespace bdsp
{
    namespace util
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

    } // namespace util
} // namespace bdsp

#endif // __UTIL_H__