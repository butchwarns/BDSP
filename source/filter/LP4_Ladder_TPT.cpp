#include "LP4_Ladder_TPT.h"

namespace bdsp
{
    namespace filter
    {

        LP4_Ladder_TPT::LP4_Ladder_TPT()
            : sample_rate(0.0),
              g(0.0),
              g1(0.0),
              g2(0.0),
              g3(0.0),
              g4(0.0),
              k(0.0)
        {
        }

        LP4_Ladder_TPT::~LP4_Ladder_TPT()
        {
        }

        void LP4_Ladder_TPT::reset(double _sample_rate)
        {
            sample_rate = _sample_rate;

            for (int n = 0; n < 4; ++n)
            {
                lp[n].reset(sample_rate);
            }
        }

        double LP4_Ladder_TPT::process(double x)
        {
            // Calculate input to low-pass chain

            const double s1 = lp[0].get_state() * g3;
            const double s2 = lp[1].get_state() * g2;
            const double s3 = lp[2].get_state() * g1;
            const double s4 = lp[3].get_state();
            const double s_bar = (s1 + s2 + s3 + s4) / (1.0 + g);
            const double u = (x - k * s_bar) / (1 + k * g4);

            // Calculate output by processing low-pass chain

            double y = u;

            for (int n = 0; n < 4; ++n)
            {
                y = lp[n].process(y);
            }

            y *= (1.0 + k); // Compensate for volume loss from increased resonance

            return y;
        }

        void LP4_Ladder_TPT::set_cutoff(double cutoff)
        {
            g = cutoff / sample_rate;
            g1 = g / (1.0 + g);
            g2 = g1 * g1;
            g3 = g2 * g1;
            g4 = g3 * g1;

            for (int n = 0; n < 4; ++n)
            {
                lp[n].set_cutoff_g1(g1);
            }
        }

        void LP4_Ladder_TPT::set_q(double q_norm)
        {
            k = 4.0 * q_norm;
        }

    } // filter
} // bdsp