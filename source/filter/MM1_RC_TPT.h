#ifndef __MM1_RC_TPT_H__
#define __MM1_RC_TPT_H__

#include "../mappings.h"

namespace bdsp
{
    namespace filter
    {

        struct MM1_RC_TPT_Output
        {
            double hp;
            double lp;
        };

        class MM1_RC_TPT
        {
        public:
            MM1_RC_TPT();
            ~MM1_RC_TPT();

            void reset(double _sample_rate);

            MM1_RC_TPT_Output process(double x);

            void set_cutoff(double cutoff);
            void set_cutoff_prewarp(double cutoff);
            void set_cutoff_g1(double _g1);

            float get_state();

        private:
            double sample_rate;
            double s;  // State register
            double g1; // Constant used in calculations
        };

    } // filter
} // bdsp

#endif // __MM1_RC_TPT_H__