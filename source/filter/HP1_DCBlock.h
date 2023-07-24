#ifndef __HP1_DC_BLOCK_H__
#define __HP1_DC_BLOCK_H__

namespace bdsp
{
    namespace filter
    {
        class HP1_DCBlock
        {
        public:
            HP1_DCBlock();
            ~HP1_DCBlock();

            void reset(double _sample_rate);

            double process(double x);

        private:
            double sample_rate;
            double xz1; // Input state register
            double yz1; // Output state register
            double a;   // Filter coeff feed-forward
            double b;   // Filter coeff feed-back
        };

    } // namespace filter
} // namespace bdsp

#endif // __HP1_DC_BLOCK_H__