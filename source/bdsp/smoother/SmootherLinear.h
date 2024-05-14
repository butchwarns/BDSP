#ifndef SMOOTHER_LINEAR
#define SMOOTHER_LINEAR

namespace bdsp::smoother
{

    template <typename FloatType>
    class SmootherLinear
    {
    public:
        SmootherLinear();
        ~SmootherLinear() = default;

        void reset(FloatType _sample_rate);
        void set_time_constant(FloatType time_constant);

        void set_target_val(FloatType _target_val);
        FloatType next();

    private:
        FloatType sample_rate;
        FloatType num_frames;
        FloatType target_val;
        FloatType state;
        FloatType delta;
    };

} // namespace bdsp::smoother

#endif // SMOOTHER_LINEAR