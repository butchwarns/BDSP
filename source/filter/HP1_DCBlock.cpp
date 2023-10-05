#include "HP1_DCBlock.h"

namespace bdsp::filter
{

    HP1_DCBlock::HP1_DCBlock()
        : sample_rate(48000),
          xz1(0.0),
          yz1(0.0),
          a(0.0),
          b(0.0)
    {
    }

    void HP1_DCBlock::reset(double _sample_rate)
    {
        xz1 = 0.0;
        yz1 = 0.0;

        sample_rate = _sample_rate;

        const double wc = 0.0015 * 44100.0 / sample_rate;
        a = 1.0 - wc / 2.0;
        b = 1.0 - wc;
    }

    double HP1_DCBlock::process(double x)
    {
        const double y = a * (x - xz1) + b * yz1;

        xz1 = x;
        yz1 = y;

        return y;
    }

} // namespace bdsp::filter