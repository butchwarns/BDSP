#ifndef __LP1_RC_TPT_H__
#define __LP1_RC_TPT_H__

#include "../mappings.h"

namespace bdsp
{
    namespace filter
    {

        class LP1_RC_TPT
        {
        public:
            LP1_RC_TPT();
            ~LP1_RC_TPT();

            void reset(double _sample_rate);

            double process(double x);

            void set_cutoff(double cutoff);
            void set_cutoff_prewarp(double cutoff);
            void set_cutoff_g1(double _g1);

            double get_state() const;

        private:
            double sample_rate;
            double s;  // State register
            double g1; // Constant used in calculations
        };

    } // filter
} // bdsp

#endif // __LP1_RC_TPT_H__