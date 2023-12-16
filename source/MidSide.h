#ifndef MIDSIDE_H
#define MIDSIDE_H

#include <cmath>

namespace bdsp
{

    struct MidSideScalingFactor
    {
        static constexpr double CORRELATED = 2.0;
        static constexpr double UNCORRELATED = 1.4142135623730950488016887242096980785696718753769480731766797379;
    };

    template <typename FloatType>
    class MidSide
    {
    public:
        MidSide() = delete;
        MidSide(const MidSide &) = delete;
        MidSide &operator=(const MidSide &) = delete;
        ~MidSide() = delete;

        static inline void
        encode_custom(FloatType scaling_factor,
                      FloatType left,
                      FloatType right,
                      FloatType &mid,
                      FloatType &side)
        {
            mid = (left + right) / scaling_factor;
            side = (left - right) / scaling_factor;
        }

        static inline void encode_correlated(FloatType left, FloatType right, FloatType &mid, FloatType &side)
        {
            encode_custom((FloatType)MidSideScalingFactor::CORRELATED, left, right, mid, side);
        }

        static inline void encode_uncorrelated(FloatType left, FloatType right, FloatType &mid, FloatType &side)
        {
            encode_custom((FloatType)MidSideScalingFactor::UNCORRELATED, left, right, mid, side);
        }

        static inline void decode_custom(FloatType scaling_factor,
                                         FloatType &left,
                                         FloatType &right,
                                         FloatType mid,
                                         FloatType side)
        {
            left = (mid + side) / scaling_factor;
            right = (mid - side) / scaling_factor;
        }

        static inline void decode_correlated(FloatType &left, FloatType &right, FloatType mid, FloatType side)
        {
            decode_custom((FloatType)MidSideScalingFactor::CORRELATED, left, right, mid, side);
        }

        static inline void decode_uncorrelated(FloatType &left, FloatType &right, FloatType mid, FloatType side)
        {
            decode_custom((FloatType)MidSideScalingFactor::UNCORRELATED, left, right, mid, side);
        }
    };

} // namespace BDSP

#endif // MIDSIDE_H
