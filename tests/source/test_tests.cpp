#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <string>

TEST_CASE("Check tests can be run", "[meta]")
{
    SECTION("Example test section")
    {
        std::string hello{"Hello"};
        std::string world{"World"};
        REQUIRE(hello.size() == world.size());
    }
}