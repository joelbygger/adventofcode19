#include "orbits.hpp"
#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("Orbits", "[woot]")
{
    SECTION("Test with Advents example 1")
    {
        Orbits::rawStorage input
            = { { "COM", "B" }, { "B", "C" }, { "C", "D" }, { "D", "E" }, { "E", "F" }, { "B", "G" },
                { "G", "H" },   { "D", "I" }, { "E", "J" }, { "J", "K" }, { "K", "L" } };
        Orbits orbits(input);
        REQUIRE(orbits.numOrbits() == 42);
    }
}
