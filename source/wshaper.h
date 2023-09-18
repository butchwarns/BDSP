#ifndef __WSHAPER_H__
#define __WSHAPER_H__

#include "utility.h"
#include <cmath>

namespace bdsp
{
    namespace wshaper
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

        // Atan soft clipping
        double atan_sat(double x, double sat)
        {
            return atan(x * sat) / atan(sat);
        }

        // Tanh soft clipping
        double tanh_sat(double x, double sat)
        {
            return tanh(x * sat) / tanh(sat);
        }

        // Exponential soft clipping
        double soft_exp(double x, double sat)
        {
            return utility::sgn(x) * (1.0 - exp(-1.0 * fabs(sat * x)));
        }

        // Sinusoidal soft clipping
        double sin(double x)
        {
            if (fabs(x) > 2.0 / 3.0)
            {
                return utility::sgn(x);
            }
            else
            {
                return sin(3.0 * utility::PI * x / 4.0);
            }
        }

        // Exponential soft clipping
        double expon(double x, double p)
        {
            if (fabs(x) > 2.0 / 3.0)
            {
                return utility::sgn(x);
            }
            else
            {
                return utility::sgn(x) * (1.0 - pow(fabs(1.5 * x - utility::sgn(x)), p));
            }
        }

        // Two stage quadratic soft clipping
        double two_stage_quad(double x)
        {
            if (fabs(x) > 2.0 / 3.0)
            {
                return utility::sgn(x);
            }
            else if (1.0f / 3.0 <= fabs(x) && fabs(x) <= 2.0 / 3.0)
            {
                return utility::sgn(x) * (3.0 - pow(2.0 - fabs(3.0 * x), 2.0)) / 3.0;
            }
            else
            {
                return 2.0 * x;
            }
        }

        // Cubic soft clipping
        double cubic(double x)
        {
            if (fabs(x) > 2.0 / 3.0)
            {
                return utility::sgn(x);
            }
            else
            {
                return 4.5 * x - 1.6875 * pow(x, 3.0);
            }
        }

        // Asymptotic soft clipping
        double asymp(double x)
        {
            return 1.0 / (fabs(x) + 1.0);
        }

    } // namespace wshaper
} // namespace bdsp

#endif // __WSHAPER_H__