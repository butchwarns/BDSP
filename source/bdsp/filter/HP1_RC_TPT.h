#ifndef HP1_RC_TPT_H
#define HP1_RC_TPT_H

#include "../mappings.h"

namespace bdsp::filter
{

    class HP1_RC_TPT
    {
    public:
        HP1_RC_TPT();
        ~HP1_RC_TPT() = default;

        void reset(double _sample_rate);

        double process(double x);

        void set_cutoff(double cutoff);
        void set_cutoff_prewarp(double cutoff);
        void set_cutoff_g1(double _g1);

        double get_state();

    private:
        double sample_rate;
        double s;  // State register
        double g1; // Constant used in calculations
    };

} // namespace bdsp::filter

#endif // HP1_RC_TPT_H