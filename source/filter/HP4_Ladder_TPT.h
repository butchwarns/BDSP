#ifndef __HP4_LADDER_TPT_H__
#define __HP4_LADDER_TPT_H__

#include "../mappings.h"
#include "HP1_RC_TPT.h"

namespace bdsp
{
    namespace filter
    {

        class HP4_Ladder_TPT
        {
        public:
            HP4_Ladder_TPT();
            ~HP4_Ladder_TPT();

            void reset(double _sample_rate);

            double process(double x);

            void set_cutoff(double cutoff);
            void set_q(double q_norm);

        private:
            HP1_RC_TPT hp[4];

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

#endif // __HP4_LADDER_TPT_H__