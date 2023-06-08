#ifndef __DECIBELS_H__
#define __DECIBELS_H__

#include <cmath>

namespace decibels
{
    inline double db_to_raw_gain(const double db_val)
    {
        return pow(10.0, db_val / 20.0);
    }

    inline float db_to_raw_gain(const float db_val)
    {
        return powf(10.0f, db_val / 20.0f);
    }

    inline double db_to_raw_gain_off(const double db_val, const double db_threshold)
    {
        if (db_val <= db_threshold)
        {
            return 0.0;
        }
        else
        {
            db_to_raw_gain(db_val);
        }
    }

    inline float db_to_raw_gain_off(const float db_val, const double db_threshold)
    {
        if (db_val <= db_threshold)
        {
            return 0.0f;
        }
        else
        {
            db_to_raw_gain(db_val);
        }
    }

    inline double raw_gain_to_db(const double raw_gain)
    {
        return 20.0 * log10(raw_gain);
    }

    inline float raw_gain_to_db(const float raw_gain)
    {
        return 20.0f * log10f(raw_gain);
    }
} // namespace decibels

#endif // __DECIBELS_H__