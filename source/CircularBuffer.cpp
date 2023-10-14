#include "CircularBuffer.h"
#include "mappings.h"

namespace bdsp
{

    template <typename T>
    CircularBuffer<T>::CircularBuffer()
        : index_write(0), len_buffer(1024), wrap_mask(1023)
    {
    }

    template <typename T>
    void CircularBuffer<T>::clear() { memset(&buffer[0], 0, len_buffer * sizeof(T)); }

    template <typename T>
    void CircularBuffer<T>::init(unsigned int num_samples)
    {
        init_power_of_two((unsigned int)(pow(2, ceil(log(num_samples) / log(2)))));
    }

    template <typename T>
    void CircularBuffer<T>::init_power_of_two(unsigned int num_samples_power_of_two)
    {
        index_write = 0;

        len_buffer = num_samples_power_of_two;

        wrap_mask = len_buffer - 1;

        buffer.reset(new T[len_buffer]);

        clear();
    }

    template <typename T>
    void CircularBuffer<T>::push_sample(T input)
    {
        buffer[index_write++] = input;

        index_write &= wrap_mask;
    }

    template <typename T>
    T CircularBuffer<T>::read(int samples_delay)
    {
        int index_read = (index_write - 1) - samples_delay;
        index_read &= wrap_mask;

        return buffer[index_read];
    }

    template <typename T>
    T CircularBuffer<T>::read(double samples_delay_fractional)
    {
        T y1 = read((int)samples_delay_fractional);
        T y2 = read((int)samples_delay_fractional + 1);

        double fraction = samples_delay_fractional - (int)samples_delay_fractional;

        return mappings::map_linear_norm(fraction, y1, y2);
    }

} // namespace bdsp