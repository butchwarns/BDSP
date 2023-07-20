#ifndef __MAPS_H__
#define __MAPS_H__

#include "consts.h"
#include <cmath>

namespace bdsp
{
    namespace maps
    {
        /**
         * @brief Maps a normalized value (-1.0 to 1.0) to a given output range
         *        The "lo" bound can be higher than the "hi" bound
         *
         * @tparam T float or double
         * @param norm_val
         * @param out_lo
         * @param out_hi
         * @return T
         */
        template <typename T>
        inline T map_linear_norm(const T norm_val, const T out_lo, const T out_hi)
        {
            return (norm_val + static_cast<T>(1.0)) / static_cast<T>(2.0) * (out_hi - out_lo) + out_lo;
        }

        /**
         * @brief Maps a normalized positive value (0.0 to 1.0) to a given output range
         *        The "lo" bound can be higher than the "hi" bound
         *
         * @tparam T float or double
         * @param norm_val
         * @param out_lo
         * @param out_hi
         * @return T
         */
        template <typename T>
        inline T map_linear_norm_pos(const T norm_val, const T out_lo, const T out_hi)
        {
            return norm_val * (out_hi - out_lo) + out_lo;
        }

        /**
         * @brief Maps a value linearly from an input range to an output range
         *        The "lo" bounds can be higher than the "hi" bounds
         *
         * @tparam T float or double
         * @param val
         * @param in_lo
         * @param in_hi
         * @param out_lo
         * @param out_hi
         * @return T
         */
        template <typename T>
        inline T map_linear(const T val, const T in_lo, const T in_hi, const T out_lo, const T out_hi)
        {
            const T in_norm = (val - in_lo) / (in_hi - in_lo);
            return map_linear_norm<T>(in_norm, out_lo, out_hi);
        }

        /**
         * @brief Convert value from unipolar to bipolar range
         *
         * @tparam T float or double
         * @param x Unipolar value in range [0.0, 1.0]
         * @return Corresponding bipolar value in range [-1.0, 1.0]
         */
        template <typename T>
        inline T unipolarToBipolar(T x)
        {
            // return (x - static_cast<T>(0.5)) * static_cast<T>(2.0);
            return map_linear_norm<T>(x, static_cast<T>(-1.0), static_cast<T>(1.0));
        }

        /**
         * @brief Convert value from bipolar to unipolar range
         *
         * @tparam T float or double
         * @param x Bipolar value in range [-1.0, 1.0]
         * @return Corresponding unipolar value in range [0.0, 1.0]
         */
        template <typename T>
        inline T bipolarToUnipolar(T x)
        {
            // return static_cast<T>(0.5) * x + static_cast<T>(0.5);
            return map_linear<T>(x, static_cast<T>(-1.0), static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(1.0));
        }

        /**
         * @brief Map a value in [0.0, 1.0] to the same interval with a skew factor
         *
         * skew = 1.0 gives a linear map
         * skew in [0.0, 1.0[ gives more resolution in the lower range
         * skew in [1.0, INF[ gives more resolution in the upper range
         *
         * @param NormVal Normalised value to map
         * @param skew Skew factor
         * @return Mapped value
         */
        inline float skew_norm_pos(float val, float skew)
        {
            return powf(val, 1.0f / skew);
        }

        /**
         * @brief Map a value in [0.0, 1.0] to the same interval with a skew factor
         *
         * skew = 1.0 gives a linear map
         * skew in [0.0, 1.0[ gives more resolution in the lower range
         * skew in [1.0, INF[ gives more resolution in the upper range
         *
         * @param NormVal Normalised value to map
         * @param skew Skew factor
         * @return Mapped value
         */
        inline double skew_norm_pos(double val, double skew)
        {
            return pow(val, 1.0 / skew);
        }

        /**
         * @brief Prewarp a frequency to be preserved in trapezoidal integration
         *
         * To be used with bilinear transformation, topology-preserving transformation, etc.
         *
         * @param freq Frequency to be preserved
         * @param sample_rate Sample rate of the system
         * @return Prewarped frequency
         */
        inline float prewarp(const float freq, const float sample_rate)
        {
            const float wd = consts::TWO_PI * freq;
            const float wa = 2.0 * sample_rate * tanf(wd / (2.0 * sample_rate));

            return wa;
        }

    } // maps
} // bdsp

#endif // __MAPS_H__