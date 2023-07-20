#include "LP1_RC_TPT.h"

namespace bdsp
{
    namespace filter
    {

        LP1_RC_TPT::LP1_RC_TPT()
            : sample_rate(static_cast<double>(0.0)),
              s(static_cast<double>(0.0))
        {
        }

        LP1_RC_TPT::~LP1_RC_TPT()
        {
        }

        void LP1_RC_TPT::reset(double _sample_rate)
        {
            sample_rate = _sample_rate;

            s = static_cast<double>(0.0);
            gamma = static_cast<double>(0.0);
        }

        double LP1_RC_TPT::process(double x)
        {
            // Calculate output sample
            double v = gamma * (x - s);
            double y = v + s;

            // Update state register
            s = v + y;

            return y;
        }

        void LP1_RC_TPT::set_cutoff(double _cutoff)
        {
            // Calculate gamma from prewarped cutoff
            double w_prewarped = maps::prewarp(_cutoff, sample_rate);
            double g = w_prewarped / (static_cast<double>(2.0) * sample_rate);
            gamma = g / (static_cast<double>(1.0) + g);
        }

    } // filter
} // bdsp