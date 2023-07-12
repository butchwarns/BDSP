#ifndef __ENV_A_R_H__V
#define __ENV_A_R_H__V

#include "../maps.h"

namespace bdsp
{
    namespace env
    {
        class EnvAR
        {
        public:
            EnvAR();
            ~EnvAR();

            //==============================================================================

            enum class EnvState
            {
                IDLE,
                ATTACK,
                RELEASE
            };

            //==============================================================================

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

            EnvState state; // Current envelope state

            bool is_triggered;

            //==============================================================================

            void update_delta();
            void transition_state();

            //==============================================================================

            const float ENV_AMPLITUDE = 8.0f;     // [V] Peak envelope amplitude
            const float CHARGE_AMPLITUDE = 12.0f; // [V] Charging voltage
            const float VOLTAGE_MARGIN = 0.001;   // [V] Margin for triggering envelope state switches

            //==============================================================================

            float prev_output{0.0}; // Previous output sample
            float time{0.0};        // Time constant of current segment
            float seg_start{0.0};   // Start value for linear segments
            float counter{0.0};     // Counter for the linear segments
            float delta{0.0};       // Increment per sample for the linear segments
        };

    } // namespace env
} // namespace bdsp

#endif // __ENV_A_R_H__V