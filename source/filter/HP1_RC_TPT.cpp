#include "HP1_RC_TPT.h"

namespace bdsp
{
    namespace filter
    {

        HP1_RC_TPT::HP1_RC_TPT()
            : sample_rate(0.0),
              s(0.0)
        {
        }

        HP1_RC_TPT::~HP1_RC_TPT()
        {
        }

        void HP1_RC_TPT::reset(double _sample_rate)
        {
            sample_rate = _sample_rate;

            s = 0.0;
            g1 = 0.0;
        }

        double HP1_RC_TPT::process(double x)
        {
            // Calculate output for low-pass
            double v = g1 * (x - s);
            double y = v + s;

            // Update state register
            s = v + y;

            // Subtract low-pass output from input to find high-pass output
            return x - y;
        }

        void HP1_RC_TPT::set_cutoff(double cutoff)
        {
            // Calculate gamma from cutoff
            const double w = bdsp::consts::TWO_PI * cutoff;
            const double g = w / (2.0 * sample_rate);
            g1 = g / (1.0 + g);
        }

        void HP1_RC_TPT::set_cutoff_prewarp(double cutoff)
        {
            // Calculate gamma from prewarped cutoff
            const double w_prewarped = mappings::prewarp(cutoff, sample_rate);
            const double g = w_prewarped / (2.0 * sample_rate);
            g1 = g / (1.0 + g);
        }

        void HP1_RC_TPT::set_cutoff_g1(double _g1)
        {
            g1 = _g1;
        }

        float HP1_RC_TPT::get_state()
        {
            return s;
        }

    } // filter
} // bdsp