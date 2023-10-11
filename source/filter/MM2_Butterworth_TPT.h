#ifndef LP2_SALLEN_KEY_TPT_H
#define LP2_SALLEN_KEY_TPT_H

namespace bdsp::filter
{
    struct MM2_Butterworth_TPT_Output
    {
        double hp;
        double lp;
        double bp;
    };

    class MM2_Butterworth_TPT
    {
    public:
        MM2_Butterworth_TPT();
        ~MM2_Butterworth_TPT() = default;

        void reset(double _sample_rate);
        void set_cutoff(double cutoff);
        MM2_Butterworth_TPT_Output process(double x);

    private:
        double sample_rate;

        // Intermediate values for calculations
        // (hold info about cutoff)
        double g;
        double g1;
        double d;

        // State variables
        double s1;
        double s2;
    };

} // namespace bdsp::filter

#endif // LP2_SALLEN_KEY_TPT_H