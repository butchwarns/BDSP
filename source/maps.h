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
     * @param out_hi
     * @param out_lo
     * @return T
     */
    template <typename T>
    inline T map_linear_norm(const T norm_val, const T out_hi, const T out_lo)
    {
        return norm_val * (out_hi - out_lo) + out_lo;
    }

    /**
     * @brief Maps a value linearly from an input range to an output range
     *        The "lo" bounds can be higher than the "hi" bounds
     *
     * @tparam T float or double
     * @param val
     * @param in_hi
     * @param in_lo
     * @param out_hi
     * @param out_lo
     * @return T
     */
    template <typename T>
    inline T map_linear(const T val, const T in_hi, const T in_lo, const T out_hi, const T out_lo)
    {
        const T in_norm = (val - in_lo) / (in_hi - in_lo);
        return map_linear_norm<T>(in_norm, out_hi, out_lo);
    }
} // namespace bdsp::maps
#endif // __MAPS_H__