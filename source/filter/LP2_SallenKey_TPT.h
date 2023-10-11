#ifndef LP2_SALLEN_KEY_TPT_H
#define LP2_SALLEN_KEY_TPT_H

#include "LP1_RC_TPT.h"

namespace bdsp::filter
{

    class LP2_SallenKey_TPT
    {
    public:
        LP2_SallenKey_TPT();
        ~LP2_SallenKey_TPT() = default;

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

} // namespace bdsp::filter

#endif // LP2_SALLEN_KEY_TPT_H