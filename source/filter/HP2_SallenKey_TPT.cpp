#include "HP2_SallenKey_TPT.h"

namespace bdsp
{
    namespace filter
    {

        HP2_SallenKey_TPT::HP2_SallenKey_TPT()
            : sample_rate(0.0),
              g(0.0),
              g1(0.0),
              g2(0.0),
              k(0.0)
        {
        }

        HP2_SallenKey_TPT::~HP2_SallenKey_TPT()
        {
        }

        void HP2_SallenKey_TPT::reset(double _sample_rate)
        {
            sample_rate = _sample_rate;

            for (int n = 0; n < 2; ++n)
            {
                hp[n].reset(sample_rate);
            }
        }

        double HP2_SallenKey_TPT::process(double x)
        {
            // Calculate input to low-pass chain

            const double s_bar = (-hp[0].get_state() * g1 - hp[1].get_state()) / (1.0 + g);
            const double u = (x - k * s_bar) / (1.0 - k * g2);

            // Calculate output by processing high-pass chain

            double y = u;

            for (int n = 0; n < 2; ++n)
            {
                y = hp[n].process(y);
            }

            return y;
        }

        void HP2_SallenKey_TPT::set_cutoff(double cutoff)
        {
            g = cutoff / sample_rate;
            const double gg = 1 / (1.0 + g);
            g1 = 1.0 - gg;
            g2 = gg - gg * gg;

            for (int n = 0; n < 2; ++n)
            {
                hp[n].set_cutoff_g1(g1);
            }
        }

        void HP2_SallenKey_TPT::set_q(double q_norm)
        {
            k = 2.0 * q_norm;
        }

    } // filter
} // bdsp