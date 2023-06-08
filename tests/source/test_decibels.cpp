#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <numeric>

#include "../../source/decibels.h"

using Catch::Matchers::WithinAbs;
typedef std::numeric_limits<float> flt;
typedef std::numeric_limits<double> dbl;

TEST_CASE("Decibel conversions", "[decibels]")
{
    using namespace decibels;

    SECTION("Decibel to raw gain conversion")
    {
        // Some double conversions
        REQUIRE_THAT(db_to_raw_gain(0.0), WithinAbs(1.0, dbl::min()));
        REQUIRE_THAT(db_to_raw_gain(10.5), WithinAbs(3.34965, 0.00001));
        REQUIRE_THAT(db_to_raw_gain(-6.3), WithinAbs(0.48417, 0.00001));

        // Some float conversions
        REQUIRE_THAT(db_to_raw_gain(0.0f), WithinAbs(1.0f, flt::min()));
        REQUIRE_THAT(db_to_raw_gain(10.5f), WithinAbs(3.34965f, 0.00001));
        REQUIRE_THAT(db_to_raw_gain(-6.3f), WithinAbs(0.48417f, 0.00001));
    }
    SECTION("Decibel to raw gain conversion with off threshold")
    {
        // Some double conversions
        REQUIRE_THAT(db_to_raw_gain_off(0.0, -68.0), WithinAbs(1.0, dbl::min()));
        REQUIRE_THAT(db_to_raw_gain_off(-99.9, -99.9), WithinAbs(0.0, dbl::min()));
        REQUIRE_THAT(db_to_raw_gain_off(-100.0, -68.0), WithinAbs(0.0, dbl::min()));

        // Some float conversions
        REQUIRE_THAT(db_to_raw_gain_off(0.0f, -68.0f), WithinAbs(1.0f, flt::min()));
        REQUIRE_THAT(db_to_raw_gain_off(-99.9f, -99.9f), WithinAbs(0.0f, flt::min()));
        REQUIRE_THAT(db_to_raw_gain_off(-100.0f, -68.0f), WithinAbs(0.0f, flt::min()));
    }
    SECTION("Raw gain to decibel conversion")
    {
        // Example double conversions
        REQUIRE_THAT(raw_gain_to_db(1.0), WithinAbs(0.0, dbl::min()));
        REQUIRE_THAT(raw_gain_to_db(2.0), WithinAbs(6.0206, 0.0001));
        REQUIRE_THAT(raw_gain_to_db(0.01), WithinAbs(-40, dbl::min()));

        // Example float conversions
        REQUIRE_THAT(raw_gain_to_db(1.0f), WithinAbs(0.0, dbl::min()));
        REQUIRE_THAT(raw_gain_to_db(2.0f), WithinAbs(6.0206, 0.0001));
        REQUIRE_THAT(raw_gain_to_db(0.01f), WithinAbs(-40, dbl::min()));
    }
}