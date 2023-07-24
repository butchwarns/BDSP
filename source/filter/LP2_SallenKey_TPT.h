#ifndef __LP2_SALLEN_KEY_TPT_H__
#define __LP2_SALLEN_KEY_TPT_H__

#include "LP1_RC_TPT.h"

namespace bdsp
{
    namespace filter
    {

        class LP2_SallenKey_TPT
        {
        public:
            LP2_SallenKey_TPT();
            ~LP2_SallenKey_TPT();

            void reset(double _sample_rate);

            double process(double x);

            void set_cutoff(double cutoff);
            void set_q(double q_norm);

        private:
            LP1_RC_TPT lp[2];

            double sample_rate;

            // Intermediate values for calculations
            // (hold info about cutoff)
            double g;
            double g2mg;
            double gm1;

            double k; // Feedback coefficient
        };

    } // namespace filter
} // namespace bdsp

#endif // __LP2_SALLEN_KEY_TPT_H__