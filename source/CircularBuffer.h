#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <cmath>
#include <memory>

namespace bdsp
{

    template <typename T>
    class CircularBuffer
    {
    public:
        CircularBuffer();
        ~CircularBuffer() = default;

        void init(unsigned int num_samples);
        void init_power_of_two(unsigned int num_samples_power_of_two);

        void clear();

        void push_sample(T input);
        T read(int samples_delay);
        T read(double samples_delay_fractional);

    private:
        std::unique_ptr<T[]> buffer;
        unsigned int index_write;
        unsigned int len_buffer; // Must be nearest power of 2
        unsigned int wrap_mask;  // Must be (len_buffer - 1)
    };

} // namespace bdsp

#endif // CIRCULAR_BUFFER_H