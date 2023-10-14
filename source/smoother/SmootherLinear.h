#ifndef SMOOTHER_LINEAR
#define SMOOTHER_LINEAR

namespace bdsp::smoother{

class SmootherLinear
{
public:
    SmootherLinear();
    ~SmootherLinear() = default;

    void reset(double _sample_rate);
    void set_time_constant(float time_constant);

    void set_target_val(float _target_val);
    float next();

private:
    double sample_rate;
    float num_frames;
    float target_val;
    float state;
    float delta;

};

} // namespace bdsp::smoother


#endif // SMOOTHER_LINEAR