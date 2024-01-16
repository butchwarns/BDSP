#include "HP1_DCBlock.h"
#include "../constants.h"

namespace bdsp::filter
{

    HP1_DCBlock::HP1_DCBlock()
        : sample_rate(48000),
          R(0.0),
          xz1(0.0),
          yz1(0.0)
    {
    }

    void HP1_DCBlock::reset(double _sample_rate)
    {
        xz1 = 0.0;
        yz1 = 0.0;

        sample_rate = _sample_rate;
    }

    void HP1_DCBlock::set_cutoff(double frequency)
    {
        R = 1 - (constants::TWO_PI * frequency / sample_rate);
    }

    double HP1_DCBlock::process(double x)
    {
        const double y = x - xz1 + R * yz1;

        xz1 = x;
        yz1 = y;

        return y;
    }

} // namespace bdsp::filter