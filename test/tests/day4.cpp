#include "password.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Password calculator test", "[woot]")
{
    SECTION("Advent example 1")
    {
        REQUIRE(password::isValidSimple(111111));
        REQUIRE(!password::isValidComplex(111111)); // No unique pair
    }

    SECTION("Advent example 2")
    {
        REQUIRE(!password::isValidComplex(223450)); // Decrease
    }

    SECTION("Advent example 3")
    {
        REQUIRE(!password::isValidComplex(123789)); // No pair
    }

    SECTION("Advent example 4")
    {
        REQUIRE(password::isValidComplex(112233));
    }

    SECTION("Advent example 5")
    {
        REQUIRE(password::isValidSimple(123444));
        REQUIRE(!password::isValidComplex(123444)); // No unique pair
    }

    SECTION("Advent example 6")
    {
        REQUIRE(password::isValidComplex(111122));
    }

    SECTION("My example 1")
    {
        REQUIRE(password::isValidComplex(112344));
        REQUIRE(password::isValidComplex(112779));
        REQUIRE(password::isValidComplex(566788));
        REQUIRE(password::isValidComplex(246778));
        REQUIRE(password::isValidComplex(246788));
        REQUIRE(password::isValidComplex(112222));
        REQUIRE(password::isValidComplex(111344));
    }

    SECTION("My example 2")
    {
        REQUIRE(!password::isValidComplex(123444));
        REQUIRE(!password::isValidComplex(127779));
        REQUIRE(!password::isValidComplex(126668));
        REQUIRE(!password::isValidComplex(355567));
        REQUIRE(!password::isValidComplex(128888));
    }
}
