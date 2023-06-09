#ifndef __DECIBELS_H__
#define __DECIBELS_H__

#include <cmath>

namespace bdsp::decibels
{
    /**
     * @brief Converts decibel (relative to 1.0) value to raw gain coefficient
     *
     * @param db_val
     * @return double
     */
    inline double db_to_raw_gain(const double db_val)
    {
        return pow(10.0, db_val / 20.0);
    }

    /**
     * @brief Converts decibel (relative to 1.0) value to raw gain coefficient
     *
     * @param db_val
     * @return float
     */
    inline float db_to_raw_gain(const float db_val)
    {
        return powf(10.0f, db_val / 20.0f);
    }

    /**
     * @brief Converts decibel (relative to 1.0) value to raw gain coefficient
     *        If value lies below given threshold, this function returns 0
     *
     * @param db_val
     * @param db_threshold
     * @return double
     */
    inline double db_to_raw_gain_off(const double db_val, const double db_threshold)
    {
        if (db_val <= db_threshold)
        {
            return 0.0;
        }
        else
        {
            return db_to_raw_gain(db_val);
        }
    }

    /**
     * @brief Converts decibel (relative to 1.0) value to raw gain coefficient
     *        If value lies below given threshold, this function returns 0
     *
     * @param db_val
     * @param db_threshold
     * @return float
     */
    inline float db_to_raw_gain_off(const float db_val, const double db_threshold)
    {
        if (db_val <= db_threshold)
        {
            return 0.0f;
        }
        else
        {
            return db_to_raw_gain(db_val);
        }
    }

    /**
     * @brief Converts raw gain coefficient to decibel (relative to 1.0) value
     *
     * @param raw_gain
     * @return double
     */
    inline double raw_gain_to_db(const double raw_gain)
    {
        return 20.0 * log10(raw_gain);
    }

    /**
     * @brief Converts raw gain coefficient to decibel (relative to 1.0) value
     *
     * @param raw_gain
     * @return float
     */
    inline float raw_gain_to_db(const float raw_gain)
    {
        return 20.0f * log10f(raw_gain);
    }
} // namespace bdsp::decibels

#endif // __DECIBELS_H__