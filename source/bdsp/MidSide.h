#ifndef MIDSIDE_H
#define MIDSIDE_H

#include <cmath>

namespace bdsp
{

    static constexpr double SCALING_UNCORRELATED = 1.4142135623730950488016887242096980785696718753769480731766797379;

    template <typename FloatType>
    class MidSide
    {
    public:
        MidSide() = delete;
        MidSide(const MidSide &) = delete;
        MidSide &operator=(const MidSide &) = delete;
        ~MidSide() = delete;

        static inline void
        encode(
            FloatType left,
            FloatType right,
            FloatType &mid,
            FloatType &side)
        {
            mid = (left + right) / SCALING_UNCORRELATED;
            side = (left - right) / SCALING_UNCORRELATED;
        }

        static inline void decode(
            FloatType &left,
            FloatType &right,
            FloatType mid,
            FloatType side)
        {
            left = (mid + side) / SCALING_UNCORRELATED;
            right = (mid - side) / SCALING_UNCORRELATED;
        }
    };

} // namespace BDSP

#endif // MIDSIDE_H
