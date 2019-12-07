#include "fuel.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Fuel accumulator", "[woot]")
{
    SECTION("Test with small weights")
    {
        REQUIRE(Fuel::accumulator({ 9, 9 }) == 2);
        REQUIRE(Fuel::accumulator({ 9, 9, 9 }) == 3);
    }

    SECTION("Test with Advents example weights")
    {
        REQUIRE(Fuel::accumulator({ 14, 1969, 100756 }) == 51314);
    }
}
