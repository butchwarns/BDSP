#ifndef HP1_DC_BLOCK_H
#define HP1_DC_BLOCK_H

namespace bdsp::filter
{

    class HP1_DCBlock
    {
    public:
        HP1_DCBlock();
        ~HP1_DCBlock() = default;

        void reset(double _sample_rate);

        double process(double x);

    private:
        double sample_rate;
        double xz1; // Input state register
        double yz1; // Output state register
        double a;   // Coefficient feed-forward
        double b;   // Coefficient feed-back
    };

} // namespace bdsp::filter

#endif // HP1_DC_BLOCK_H