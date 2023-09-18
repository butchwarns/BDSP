#ifndef __LP4_LADDER_TPT_H__
#define __LP4_LADDER_TPT_H__

#include "../mappings.h"
#include "LP1_RC_TPT.h"

namespace bdsp
{
    namespace filter
    {

        class LP4_Ladder_TPT
        {
        public:
            LP4_Ladder_TPT();
            ~LP4_Ladder_TPT();

            void reset(double _sample_rate);

            double process(double x);

            void set_cutoff(double cutoff);
            void set_q(double q_norm);

        private:
            LP1_RC_TPT lp[4];

            double sample_rate;

            // Intermediate values for calculations
            // (hold info about cutoff)
            double g;
            double g1;
            double g2;
            double g3;
            double g4;

            double k; // Feedback coefficient
        };

    } // filter
} // bdsp

#endif // __LP4_LADDER_TPT_H__