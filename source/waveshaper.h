#ifndef __WAVESHAPER_H__
#define __WAVESHAPER_H__

#include <cmath>

namespace bdsp::waveshper
{
    /**
     * @brief Fast polynomial tanh approximation
     *
     * This approximation was proposed by "Aleksey Vaneef" in this forum post
     * https://www.kvraudio.com/forum/viewtopic.php?t=388650&start=50
     *
     * - 0.427% peak relative error
     * - smooth 1st and 2nd derivatives
     * - 3rd derivative's magnitude relative to the 1st derivative at discontinuity point around -191 dB
     *
     *
     * @param x
     * @return double
     */
    inline double tanh2_fast(const double x)
    {
        const double x_abs = fabs(x);
        const double x2 = x * x;

        return (x * (2.45550750702956 + 2.45550750702956 * x_abs + (0.893229853513558 + 0.821226666969744 * x_abs) * x2) /
                (2.44506634652299 + (2.44506634652299 + x2) *
                                        fabs(x + 0.814642734961073 * x * x_abs)));
    }
} // namespace bdsp::waveshaper
#endif