#ifndef NOISE_H
#define NOISE_H

#include <array>
#include <random>

#include "mappings.h"

namespace bdsp
{

    class Noise
    {
    public:
        Noise() = default;

        static inline double white()
        {
            double noise = 0.0;

#if defined _WINDOWS || defined _WINDLL
            constexpr double RAND_MAX = 32767.0; // (2^15 - 1)

            noise = (double)rand();
            noise = noise / RAND_MAX
                                noise = mappings::unipolar_to_bipolar(noise);
#else
            const double ARC4RANDOM_MAX = 4294967295.0; // (2^32 - 1)

            noise = (double)arc4random();
            noise = noise / ARC4RANDOM_MAX;
            noise = mappings::unipolar_to_bipolar(noise);
#endif

            return noise;
        }
    };

} // namespace bdsp

#endif // NOISE_H