#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <numeric>

#include "../../source/mappings.h"

using Catch::Matchers::WithinAbs;
typedef std::numeric_limits<float> flt;
typedef std::numeric_limits<double> dbl;

using namespace bdsp::mappings;

TEST_CASE("Linear mappings", "[mappings]")
{
    SECTION("Linear map")
    {
        // Some double mappings
        REQUIRE_THAT(map_linear(0.5, -1.0, 1.0, -2.0, 2.0), WithinAbs(1.0, dbl::min()));
        REQUIRE_THAT(map_linear(0.5, 2.0, -2.0, -2.0, 2.0), WithinAbs(-0.5, dbl::min()));

        // Some float mappings
        REQUIRE_THAT(map_linear(0.5f, -1.0f, 1.0f, -2.0f, 2.0f), WithinAbs(1.0f, flt::min()));
        REQUIRE_THAT(map_linear(0.5f, 2.0f, -2.0f, -2.0f, 2.0f), WithinAbs(-0.5f, flt::min()));
    }
    SECTION("Normalized linear map")
    {
        // Some double mappings
        REQUIRE_THAT(map_linear_norm(0.5, -1.0, 1.0), WithinAbs(0.0, dbl::min()));
        REQUIRE_THAT(map_linear_norm(0.75, 1.0, -1.0), WithinAbs(-0.5, dbl::min()));

        // Some float mappings
        REQUIRE_THAT(map_linear_norm(0.5f, -1.0f, 1.0f), WithinAbs(0.0f, flt::min()));
        REQUIRE_THAT(map_linear_norm(0.75f, 1.0f, -1.0f), WithinAbs(-0.5f, flt::min()));
    }
}

TEST_CASE("Signal polarity conversions", "[mappings]")
{

    SECTION("Unipolar to bipolar conversion")
    {
        // Some double conversions
        REQUIRE_THAT(unipolar_to_bipolar(0.25), WithinAbs(-0.5, dbl::min()));
        REQUIRE_THAT(unipolar_to_bipolar(0.5), WithinAbs(0.0, dbl::min()));

        // Some float conversions
        REQUIRE_THAT(unipolar_to_bipolar(0.25f), WithinAbs(-0.5f, flt::min()));
        REQUIRE_THAT(unipolar_to_bipolar(0.5f), WithinAbs(0.0f, flt::min()));
    }
    SECTION("Bipolar to unipolar conversion")
    {
        // Some double conversions
        REQUIRE_THAT(bipolar_to_unipolar(-0.5), WithinAbs(0.25, dbl::min()));
        REQUIRE_THAT(bipolar_to_unipolar(1.0), WithinAbs(1.0, dbl::min()));

        // Some float conversions
        REQUIRE_THAT(bipolar_to_unipolar(-0.5f), WithinAbs(0.25f, flt::min()));
        REQUIRE_THAT(bipolar_to_unipolar(1.0f), WithinAbs(1.0f, flt::min()));
    }
}
