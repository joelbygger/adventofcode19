#include "password.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Password calculator test", "[woot]")
{
    SECTION("Advent example 1")
    {
        REQUIRE(password::isValid(111111));
    }

    SECTION("Advent example 2")
    {
        REQUIRE(!password::isValid(223450));
    }

    SECTION("Advent example 3")
    {
        REQUIRE(!password::isValid(123789));
    }
}
