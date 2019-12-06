
//#include "day1.hpp"
#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"
#include "fuel.hpp"
#include <vector>

TEST_CASE("Fuel accumulator", "[woot]")
{
    // std::vector<int> tst {9, 9};
    SECTION("Test with large weights")
    {
        REQUIRE(Fuel::accumulator({ 9, 9 }) == 2);
        REQUIRE(Fuel::accumulator({ 9, 9, 9 }) == 3);
        REQUIRE(Fuel::accumulator({ 99, 99 }) == 62);
    }

    // Can we go below zero or stop at zero?

    SECTION("Test with odd weights")
    {
        REQUIRE(Fuel::accumulator({ 11, 12 }) == 3);
        REQUIRE(Fuel::accumulator({ 13, 13, 13 }) == 6);
        REQUIRE(Fuel::accumulator({ 22, 22 }) == 10);
    }

    SECTION("Test with small weights")
    {
        REQUIRE(Fuel::accumulator({ 3, 3 }) == 2);
    }

    SECTION("Test with Advents examplessmall weights")
    {
        REQUIRE(Fuel::accumulator({ 12, 14, 1969, 100756 }) == 34241);
    }
}
