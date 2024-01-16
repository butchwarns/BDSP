#ifndef BIQUAD_H
#define BIQUAD_H

#include <memory>

namespace bdsp::filter
{
    //        a0 * x + a1 * x * z^-1 + a2 * x * z^-2
    // H(z) = --------------------------------------
    //          1 + b1 * y * z^-1 + b2 * y * z^-2
    enum Coefficient
    {
        A0,
        A1,
        A2,
        B1,
        B2,
        NUM_COEFFS,
    };

    // State register naming only directly reflected in DIRECT form biquad!
    enum StateRegister
    {
        X_Z1, // x[n-1]
        X_Z2, // x[n-2]
        Y_Z1, // y[n-1]
        Y_Z2, // y[n-2]
        NUM_STATE_REGISTERS,
    };

    enum class BiquadStructure
    {
        DIRECT,
        CANONICAL,
        TRANSPOSED_DIRECT,
        TRANSPOSED_CANONICAL,
    };

    class Biquad
    {
    public:
        Biquad();
        ~Biquad() = default;

        bool reset(double _sampleRate);

        virtual double process(double x);

        void set_structure(BiquadStructure _structure);
        void set_coefficients(double *coeffs_new);
        double *get_coefficients();
        double *get_state_array();

    protected:
        double coefficients[NUM_COEFFS];
        double state_registers[NUM_STATE_REGISTERS];

        BiquadStructure structure;
    };

} // namespace bdsp::filter

#endif // BIQUAD_H