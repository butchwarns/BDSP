#include "LP2_SallenKey_TPT.h"

namespace bdsp::filter
{

    LP2_SallenKey_TPT::LP2_SallenKey_TPT()
        : sample_rate(0.0),
          g(0.0),
          g2mg(0.0),
          gm1(0.0),
          k(0.0)
    {
    }

    void LP2_SallenKey_TPT::reset(double _sample_rate)
    {
        sample_rate = _sample_rate;

        for (int n = 0; n < 2; ++n)
        {
            lp[n].reset(sample_rate);
        }
    }

    double LP2_SallenKey_TPT::process(double x)
    {
        // Calculate input to low-pass chain

        const double s_bar = (lp[0].get_state() * gm1 + lp[1].get_state()) / (1.0 + g);
        const double u = (x - k * s_bar) / (1 + k * g2mg);

        // Calculate output by processing low-pass chain

        double y = u;

        for (int n = 0; n < 2; ++n)
        {
            y = lp[n].process(y);
        }

        return y;
    }

    void LP2_SallenKey_TPT::set_cutoff(double cutoff)
    {
        g = cutoff / sample_rate;
        const double g1 = g / (1.0 + g);
        g2mg = g1 * g1 - g1;
        gm1 = g1 - 1.0;

        for (int n = 0; n < 2; ++n)
        {
            lp[n].set_cutoff_g1(g1);
        }
    }

    void LP2_SallenKey_TPT::set_q(double q_norm)
    {
        k = 2.0 * q_norm;
    }

} // namespace bdsp::filter