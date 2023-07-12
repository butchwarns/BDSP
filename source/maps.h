#ifndef __MAPS_H__
#define __MAPS_H__

namespace bdsp::maps
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
} // namespace bdsp::maps
#endif // __MAPS_H__