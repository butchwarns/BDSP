#include "MM2_Butterworth_TPT.h"
#include "../constants.h"
#include "../mappings.h"

namespace bdsp::filter
{

    MM2_Butterworth_TPT::MM2_Butterworth_TPT()
        : sample_rate(0.0),
          g(0.0),
          g1(0.0),
          d(0.0),
          s1(0.0),
          s2(0.0)
    {
    }

    void MM2_Butterworth_TPT::reset(double _sample_rate)
    {
        sample_rate = _sample_rate;

        s1 = 0.0;
        s2 = 0.0;
    }

    MM2_Butterworth_TPT_Output MM2_Butterworth_TPT::process(double x)
    {
        const double yhp = (x - g1 * s1 - s2) * d;

        const double v1 = g * yhp;
        const double ybp = v1 + s1;
        s1 = v1 + ybp;

        const double v2 = g * ybp;
        const double ylp = v2 + s2;
        s2 = v2 + ylp;

        MM2_Butterworth_TPT_Output out{
            yhp,
            ylp,
            ybp,
        };

        return out;
    }

    void MM2_Butterworth_TPT::set_cutoff(double cutoff)
    {
        // Prewarp
        const double wc = bdsp::mappings::prewarp(cutoff, sample_rate);

        g = wc / (2.0 * sample_rate);

        g1 = sqrt(2.0) + g;

        const double g_sq = g * g;
        d = 1.0 / (1.0 + sqrt(2) * g + g_sq);
    }

} // namespace bdsp::filter