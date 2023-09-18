#include "EnvAR.h"

namespace bdsp
{
    namespace env
    {

        EnvAR::EnvAR()
            : sample_rate(48000), attack(0.002f), release(0.4f), state(EnvState::IDLE), is_triggered(false)
        {
        }

        EnvAR::~EnvAR()
        {
        }

        //==============================================================================

        void EnvAR::reset(double _sample_rate)
        {
            sample_rate = _sample_rate;

            counter = 0.0;
            delta = 0.0;
            prev_output = 0.0;
        }

        void EnvAR::set_attack(float _attack)
        {
            attack = _attack;
        }

        void EnvAR::set_release(float _release)
        {
            release = _release;
        }

        //==============================================================================

        void EnvAR::trigger()
        {
            is_triggered = true;
        }

        float EnvAR::process()
        {
            float output{0.0};
            float counter_inv{0.0};

            // Find next output
            switch (state)
            {
            case EnvState::IDLE:
                output = 0.0f;
                break;

            case EnvState::ATTACK:

                // Find curve

                // ATTACK "aims higher" to make the curve more linear, like in the analog circuit
                // 12 V is given by the Eurorack power specs (envelope output peaks at 8 V)
                // output = adsp::skewNormalized(counter, 1.8);
                output = mappings::map_linear_norm(counter, seg_start, ENV_AMPLITUDE);

                // Increment counter
                counter += delta;
                break;

            case EnvState::RELEASE:

                // Shape and scale to desired linear segment
                // Counter needs to be inverted for the correct shape of the decreasing segment
                counter_inv = 1.0f - counter;
                counter_inv = mappings::skew_norm_pos(counter_inv, 0.2f);
                counter_inv = 1.0f - counter_inv;
                output = mappings::map_linear_norm(counter_inv, seg_start, 0.0f);

                // Decrement counter
                counter += delta;

                break;
            }

            // Check for state transitions
            transition_state();

            // Save output for future calculations
            prev_output = output;

            return output;
        }

        //==============================================================================

        void EnvAR::update_delta()
        {
            // Adjust time to compensate the curve "aiming higher" in ATTACK

            double time_adjusted = time;

            if (state == EnvState::ATTACK)
            {
                time_adjusted = 12.0f / 8.0f * time;
            }

            // Calculate new delta
            delta = 1.0f / (time_adjusted * sample_rate);
        }

        void EnvAR::transition_state()
        {
            switch (state)
            {
            case EnvState::IDLE:
                // If triggered in IDLE..
                if (is_triggered)
                {
                    // Change to ATTACK phase
                    state = EnvState::ATTACK;

                    // Get new timing constant
                    time = attack;

                    update_delta();

                    counter = 0.0f;

                    // Start ATTACK segment from zero
                    seg_start = 0.0f;
                }
                break;

            case EnvState::ATTACK:
                // If ATTACK phase is over..
                if (prev_output >= (ENV_AMPLITUDE - VOLTAGE_MARGIN))
                {
                    // Change to RELEASE phase
                    state = EnvState::RELEASE;

                    // Get new timing constant
                    time = release;

                    update_delta();

                    counter = 0.0f;

                    // Start release phase from current output voltage
                    seg_start = prev_output;
                }
                break;

            case EnvState::RELEASE:
                // If envelope is triggered in RELEASE..
                if (is_triggered)
                {
                    // Change to ATTACK phase
                    state = EnvState::ATTACK;

                    // Set new timing constant
                    time = attack;

                    // Update increment
                    update_delta();

                    // Reset counter
                    counter = 0.0f;

                    // Start ATTACK from current output value
                    seg_start = prev_output;
                }
                // If RELEASE phase is over..
                else if (prev_output <= (0.0f + VOLTAGE_MARGIN))
                {
                    // Change back to IDLE phase
                    state = EnvState::IDLE;
                }
                break;
            }

            // Untrigger envelope, so it doenst hang in attack
            is_triggered = false;
        }

    } // namespace env
} // namespace bdsp