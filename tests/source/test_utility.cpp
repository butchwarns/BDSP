#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <numeric>

#include "../../source/utility.h"

using Catch::Matchers::WithinAbs;
typedef std::numeric_limits<float> flt;
typedef std::numeric_limits<double> dbl;

using namespace bdsp::utility;

TEST_CASE("Float underflow", "[util]")
{
    SECTION("Positive underflow")
    {
        double under = static_cast<double>(flt::min()) / 2.0;
        float denorm = static_cast<float>(under);

        REQUIRE(((denorm > 0.0f) && (denorm < flt::min())));

        fix_underflow(under);
        float fixed = static_cast<float>(under);

        REQUIRE(fixed == 0.0f);
    }
    SECTION("Negative underflow")
    {
        double under = static_cast<double>(-flt::min()) / 2.0;
        float denorm = static_cast<float>(under);

        REQUIRE(((denorm < 0.0f) && (denorm > -flt::min())));

        fix_underflow(under);
        float fixed = static_cast<float>(under);

        REQUIRE(fixed == 0.0f);
    }
}

TEST_CASE("Signum function", "[util]")
{
    SECTION("sgn(x)")
    {
        // int
        REQUIRE(sgn(5) == 1);
        REQUIRE(sgn(-42) == -1);
        REQUIRE(sgn(0) == 0);

        // float
        REQUIRE(sgn(5.0f) == 1.0f);
        REQUIRE(sgn(-42.0f) == -1.0f);
        REQUIRE(sgn(0.0f) == 0.0f);

        // double
        REQUIRE(sgn(5.0) == 1.0);
        REQUIRE(sgn(-42.0) == -1.0);
        REQUIRE(sgn(0.0) == 0.0);
    }
}

TEST_CASE("Clamp", "[util]")
{
    SECTION("Clamp flaot values")
    {
        REQUIRE(clamp(5.0f, -1.0f, 1.0f) == 1.0f);
        REQUIRE(clamp(-5.0f, -1.0f, 1.0f) == -1.0f);
        REQUIRE(clamp(-0.2f, -1.0f, 1.0f) == -0.2f);
    }
    SECTION("Clamp double values")
    {
        REQUIRE(clamp(5.0, -1.0, 1.0) == 1.0);
        REQUIRE(clamp(-5.0, -1.0, 1.0) == -1.0);
        REQUIRE(clamp(-0.2, -1.0, 1.0) == -0.2);
    }
}