#include "HP4_Ladder_TPT.h"

namespace bdsp
{
    namespace filter
    {

        HP4_Ladder_TPT::HP4_Ladder_TPT()
            : sample_rate(0.0),
              g(0.0),
              g1(0.0),
              g2(0.0),
              g3(0.0),
              g4(0.0),
              k(0.0)
        {
        }

        HP4_Ladder_TPT::~HP4_Ladder_TPT()
        {
        }

        void HP4_Ladder_TPT::reset(double _sample_rate)
        {
            sample_rate = _sample_rate;

            for (int n = 0; n < 4; ++n)
            {
                hp[n].reset(sample_rate);
            }
        }

        double HP4_Ladder_TPT::process(double x)
        {
            // Calculate input to low-pass chain

            const double s1 = hp[0].get_state() * g4;
            const double s2 = hp[1].get_state() * g3;
            const double s3 = hp[2].get_state() * g2;
            const double s4 = hp[3].get_state() * g1;
            const double s_bar = -1.0 * (s1 + s2 + s3 + s4);
            const double u = (x - k * s_bar) / (1 + k * g4);

            // Calculate output by processing low-pass chain

            double y = u;

            for (int n = 0; n < 4; ++n)
            {
                y = hp[n].process(y);
            }

            y *= (1.0 + k); // Compensate for volume loss from increased resonance

            return y;
        }

        void HP4_Ladder_TPT::set_cutoff(double cutoff)
        {
            g = cutoff / sample_rate;
            g1 = 1.0 / (1.0 + g);
            g2 = g1 * g1;
            g3 = g2 * g1;
            g4 = g3 * g1;

            const double gg = g * g1;

            for (int n = 0; n < 4; ++n)
            {
                hp[n].set_cutoff_g1(gg);
            }
        }

        void HP4_Ladder_TPT::set_q(double q_norm)
        {
            k = 4.0 * q_norm;
        }

    } // filter
} // bdsp