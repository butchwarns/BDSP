#ifndef __CONSTS_H__
#define __CONSTS_H__

#include <cmath>

namespace bdsp
{
    namespace consts
    {

        /**
         * @brief @f$ \pi @f$
         */
        constexpr double PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899;

        /**
         * @brief @f$ 2\pi @f$
         */
        constexpr double TWO_PI = 2.0 * 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899;

        /**
         * @brief Minimum filter cutoff frequency, lower threshold of human hearing
         */
        constexpr double MIN_FILTER_FREQ = 20.0;

        /**
         * @brief Maximum filter cutoff frequency, upper threshold of human hearing
         */
        constexpr double MAX_FILTER_FREQ = 20480.0;

    } // namespace consts
} // namespace bdsp

#endif // __CONSTS_H__