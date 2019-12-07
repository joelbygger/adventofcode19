#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"
#include "fuel.hpp"
#include <vector>

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
