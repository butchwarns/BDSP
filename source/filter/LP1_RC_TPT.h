#ifndef __LP1_RC_TPT_H__
#define __LP1_RC_TPT_H__

#include "../maps.h"

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

            void set_cutoff(double _cutoff);

        private:
            double sample_rate;
            double s;     // State register
            double gamma; // Constant used in calculations
        };

    } // filter
} // bdsp

#endif // __LP1_RC_TPT_H__