#ifndef DECIBEL_H
#define DECIBEL_H

#include <cmath>

namespace bdsp::decibel
{

    /**
     * @brief Converts decibel (relative to 1.0) value to linear gain factor
     *
     * @param val_db
     * @return double
     */
    inline double db_to_linear(const double val_db)
    {
        return pow(10.0, val_db / 20.0);
    }

    /**
     * @brief Converts decibel (relative to 1.0) value to linear gain factor
     *
     * @param val_db
     * @return float
     */
    inline float db_to_linear(const float val_db)
    {
        return powf(10.0f, val_db / 20.0f);
    }

    /**
     * @brief Converts decibel (relative to 1.0) value to linear gain factor
     *        If value lies below given threshold, this function returns 0
     *
     * @param val_db
     * @param threshold_db
     * @return double
     */
    inline double db_to_linear_off(const double val_db, const double threshold_db)
    {
        if (val_db <= threshold_db)
        {
            return 0.0;
        }
        else
        {
            return db_to_linear(val_db);
        }
    }

    /**
     * @brief Converts decibel (relative to 1.0) value to linear gain factor
     *        If value lies below given threshold, this function returns 0
     *
     * @param val_db
     * @param threshold_db
     * @return float
     */
    inline float db_to_linear_off(const float val_db, const double threshold_db)
    {
        if (val_db <= threshold_db)
        {
            return 0.0f;
        }
        else
        {
            return db_to_linear(val_db);
        }
    }

    /**
     * @brief Converts linear gain factor to decibel (relative to 1.0) value
     *
     * @param gain_linear
     * @return double
     */
    inline double linear_to_db(const double gain_linear)
    {
        return 20.0 * log10(gain_linear);
    }

    /**
     * @brief Converts linear gain factor to decibel (relative to 1.0) value
     *
     * @param gain_linear
     * @return float
     */
    inline float linear_to_db(const float gain_linear)
    {
        return 20.0f * log10f(gain_linear);
    }

} // namespace bdsp::decibel

#endif // DECIBEL_H