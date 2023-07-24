#ifndef __HP2_SALLEN_KEY_TPT_H__
#define __HP2_SALLEN_KEY_TPT_H__

#include "HP1_RC_TPT.h"

namespace bdsp
{
    namespace filter
    {

        class HP2_SallenKey_TPT
        {
        public:
            HP2_SallenKey_TPT();
            ~HP2_SallenKey_TPT();

            void reset(double _sample_rate);

            double process(double x);

            void set_cutoff(double cutoff);
            void set_q(double q_norm);

        private:
            HP1_RC_TPT hp[2];

            double sample_rate;

            // Intermediate values for calculations
            // (hold info about cutoff)
            double g;
            double g1;
            double g2;

            double k; // Feedback coefficient
        };

    } // namespace filter
} // namespace bdsp

#endif // __HP2_SALLEN_KEY_TPT_H__