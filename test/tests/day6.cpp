#include "orbits.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Orbits", "[woot]")
{
    SECTION("Test with Advents example, task 1")
    {
        Orbits::rawStorage input
            = { { "COM", "B" }, { "B", "C" }, { "C", "D" }, { "D", "E" }, { "E", "F" }, { "B", "G" },
                { "G", "H" },   { "D", "I" }, { "E", "J" }, { "J", "K" }, { "K", "L" } };
        Orbits orbits(input);
        REQUIRE(orbits.totOrbits() == 42);
    }

    SECTION("Test with Advents example, task 2")
    {
        Orbits::rawStorage input
            = { { "COM", "B" }, { "B", "C" }, { "C", "D" }, { "D", "E" }, { "E", "F" },   { "B", "G" },  { "G", "H" },
                { "D", "I" },   { "E", "J" }, { "J", "K" }, { "K", "L" }, { "K", "YOU" }, { "I", "SAN" } };
        Orbits orbits(input);
        REQUIRE(orbits.minDist("YOU", "SAN") == 4);
    }
}
