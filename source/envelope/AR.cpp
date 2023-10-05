#include "AR.h"

namespace bdsp::envelope
{

    AR::AR()
        : sample_rate(48000),
          attack(0.002f),
          release(0.4f),
          state(State::IDLE),
          is_triggered(false)
    {
    }

    void AR::reset(double _sample_rate)
    {
        sample_rate = _sample_rate;

        counter = 0.0;
        delta = 0.0;
        prev_output = 0.0;
    }

    void AR::set_attack(float _attack)
    {
        attack = _attack;
    }

    void AR::set_release(float _release)
    {
        release = _release;
    }

    void AR::trigger()
    {
        is_triggered = true;
    }

    float AR::process()
    {
        float output{0.0f};
        float counter_inv{0.0f};

        // Find next output
        switch (state)
        {
        case State::IDLE:
            output = 0.0f;
            break;

        case State::ATTACK:

            // Find curve

            // ATTACK "aims higher" to make the curve more linear, like in the analog circuit
            // 12 V is given by the Eurorack power specs (envelope output peaks at 8 V)
            // output = adsp::skewNormalized(counter, 1.8);
            output = mappings::map_linear_norm(counter, seg_start, ENV_AMPLITUDE);

            // Increment counter
            counter += delta;
            break;

        case State::RELEASE:

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
        output_prev = output;

        return output;
    }

    void AR::update_delta()
    {
        // Adjust time to compensate the curve "aiming higher" in ATTACK

        double time_adjusted = time;

        if (state == State::ATTACK)
        {
            time_adjusted = 12.0f / 8.0f * time;
        }

        // Calculate new delta
        delta = 1.0f / (time_adjusted * sample_rate);
    }

    void AR::transition_state()
    {
        switch (state)
        {
        case State::IDLE:
            // If triggered in IDLE..
            if (is_triggered)
            {
                // Change to ATTACK
                state = State::ATTACK;

                // Get new timing constant
                time = attack;

                update_delta();

                counter = 0.0f;

                // Start ATTACK segment from zero
                segment_start = 0.0f;
            }
            break;

        case State::ATTACK:
            // If ATTACK is over..
            if (output_prev >= (PEAK_AMPLITUDE - VOLTAGE_MARGIN))
            {
                // Change to RELEASE
                state = State::RELEASE;

                // Get new timing constant
                time = release;

                update_delta();

                counter = 0.0f;

                // Start RELEASE from current output voltage
                segment_start = output_prev;
            }
            break;

        case State::RELEASE:
            // If envelope is triggered in RELEASE..
            if (is_triggered)
            {
                // Change to ATTACK
                state = State::ATTACK;

                // Set new timing constant
                time = attack;

                // Update increment
                update_delta();

                // Reset counter
                counter = 0.0f;

                // Start ATTACK from current output value
                segment_start = output_preve;
            }
            // If RELEASE is over..
            else if (output_prev <= (0.0f + VOLTAGE_MARGIN))
            {
                // Change back to IDLE
                state = State::IDLE;
            }
            break;
        }

        // Untrigger envelope
        is_triggered = false;
    }

} // namespace bdsp::envelope