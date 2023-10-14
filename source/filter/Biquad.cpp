#include "Biquad.h"
#include "../utility.h"

namespace bdsp::filter
{

    Biquad::Biquad()
        : coefficients{0.0, 0.0, 0.0, 0.0, 0.0},
          state_registers{0.0, 0.0, 0.0, 0.0},
          structure(BiquadStructure::TRANSPOSED_CANONICAL)
    {
    }

    bool Biquad::reset(double _sampleRate)
    {
        memset(&state_registers[0], 0, sizeof(double) * NUM_STATE_REGISTERS);
        return true; // handled = true
    }

    void Biquad::set_structure(BiquadStructure _structure) { structure = _structure; }

    void Biquad::set_coefficients(double *coeffs_new)
    {
        memcpy(&coefficients[0], &coeffs_new[0], sizeof(double) * NUM_COEFFS);
    }

    double *Biquad::get_coefficients()
    {
        return &coefficients[0];
    }

    double *Biquad::get_state_array()
    {
        return &coefficients[0];
    }

    double Biquad::process(double x)
    {
        if (structure == BiquadStructure::DIRECT)
        {
            // y[n] = a0*x[n] + a1*x[n-1] + a2*x[n-2] - b1*y[n-1] - b2*y[n-2]
            double y = coefficients[A0] * x +
                       coefficients[A1] * state_registers[X_Z1] +
                       coefficients[A2] * state_registers[X_Z2] -
                       coefficients[B1] * state_registers[Y_Z1] -
                       coefficients[B2] * state_registers[Y_Z2];

            utility::fix_underflow(y);

            // Update state registers
            state_registers[X_Z2] = state_registers[X_Z1];
            state_registers[X_Z1] = x;
            state_registers[Y_Z2] = state_registers[Y_Z1];
            state_registers[Y_Z1] = y;

            return y;
        }
        else if (structure == BiquadStructure::CANONICAL)
        {
            // w[n] = x[n] - b1*x[n-1] - b2*x[n-2]
            double w = x - coefficients[B1] * state_registers[X_Z1] - coefficients[B2] * state_registers[X_Z2];

            // y[n] = a0*w[n] + a1*x[n-1] + a2*x[n-2];
            double y = coefficients[A0] * w + coefficients[A1] * state_registers[X_Z1] + coefficients[A2] * state_registers[X_Z2];

            utility::fix_underflow(y);

            // Update state registers
            state_registers[X_Z2] = state_registers[X_Z1];
            state_registers[X_Z1] = w;

            return y;
        }
        else if (structure == BiquadStructure::TRANSPOSED_DIRECT)
        {
            // w[n] = x[n] + y[n-1]
            double w = x + state_registers[Y_Z1];

            // y[n] = a0*w[n] + x[n-1]
            double y = coefficients[A0] * w + state_registers[X_Z1];

            utility::fix_underflow(y);

            // Update state registers
            state_registers[Y_Z1] = state_registers[Y_Z2] - coefficients[B1] * w;
            state_registers[Y_Z2] = -coefficients[B2] * w;
            state_registers[X_Z1] = state_registers[X_Z2] + coefficients[A1] * w;
            state_registers[X_Z2] = coefficients[A2] * w;

            return y;
        }
        else if (structure == BiquadStructure::TRANSPOSED_CANONICAL)
        {
            // y[n] = a0*x[n] + x[n-1]
            double y = coefficients[A0] * x + state_registers[X_Z1];

            utility::fix_underflow(y);

            // Update state registers
            state_registers[X_Z1] = coefficients[A1] * x - coefficients[B1] * y + state_registers[X_Z2];
            state_registers[X_Z2] = coefficients[A2] * x - coefficients[B2] * y;

            return y;
        }

        return x; // Unknown structure -> pass-through!
    }

} // namespace bdsp::filter