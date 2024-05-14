#ifndef A_R_H
#define A_R_H

#include "../mappings.h"

namespace bdsp::envelope
{

    class AR
    {
    public:
        AR();
        ~AR() = default;

        enum class State
        {
            IDLE,
            ATTACK,
            RELEASE
        };

        void reset(double _sample_rate);

        void set_attack(float _attack);
        void set_release(float _release);

        //==============================================================================

        void trigger();
        float process();

    private:
        double sample_rate;

        float attack;  // [s] Attack time
        float release; // [s] Release time

        State state; // Current envelope state

        bool is_triggered;

        void update_delta();
        void transition_state();

        const float PEAK_AMPLITUDE = 8.0f;    // [V] Peak envelope amplitude
        const float CHARGE_AMPLITUDE = 12.0f; // [V] Charging voltage
        const float VOLTAGE_MARGIN = 0.001f;  // [V] Margin for triggering envelope state switches

        float output_prev{0.0};   // Previous output sample
        float time{0.0};          // Time constant of current segment
        float segment_start{0.0}; // Start value for linear segments
        float counter{0.0};       // Counter for the linear segments
        float delta{0.0};         // Increment per sample for the linear segments
    };

} // namespace bdsp::envelope

#endif // A_R_H