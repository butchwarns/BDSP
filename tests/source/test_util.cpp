#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <numeric>

#include "../../source/util.h"

using Catch::Matchers::WithinAbs;
typedef std::numeric_limits<float> flt;
typedef std::numeric_limits<double> dbl;

using namespace bdsp::util;

TEST_CASE("Float underflow", "[util]")
{
    SECTION("Positive underflow")
    {
        double under = static_cast<double>(flt::min()) / 2.0;
        float denorm = static_cast<float>(under);

        REQUIRE(((denorm > 0.0f) && (denorm < flt::min())));

        fixUnderflow(under);
        float fixed = static_cast<float>(under);

        REQUIRE(fixed == 0.0f);
    }
    SECTION("Negative underflow")
    {
        double under = static_cast<double>(-flt::min()) / 2.0;
        float denorm = static_cast<float>(under);

        REQUIRE(((denorm < 0.0f) && (denorm > -flt::min())));

        fixUnderflow(under);
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