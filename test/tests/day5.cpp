#include "intcode.hpp"
#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("Intcode calculator", "[woot]")
{

    SECTION("Test with Advents example 1")
    {
        std::vector<int> input{ 1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50 }; // NOLINT
        const std::vector<int> expected = { 3500, 9, 10, 70, 2, 3, 11, 0, 99, 30, 40, 50 };
        Intcode::calculate(input);
        REQUIRE(input == expected);
    }

    SECTION("Test with Advents example 2")
    {
        std::vector<int> input{ 1, 0, 0, 0, 99 }; // NOLINT
        const std::vector<int> expected = { 2, 0, 0, 0, 99 };
        Intcode::calculate(input);
        REQUIRE(input == expected);
    }
    SECTION("Test with Advents example 2, immediate instead of pos")
    {
        std::vector<int> input{ 11101, 1, 2, 0, 99 };
        const std::vector<int> expected = { 11101, 1, 2, 3, 99 };
        Intcode::calculate(input);
        REQUIRE(input == expected);
    }
    SECTION("Test with Advents example 2, some immediate instead of pos")
    {
        std::vector<int> input{ 10101, 0, 0, 0, 99 };
        const std::vector<int> expected = { 10101, 0, 0, 10101, 99 };
        Intcode::calculate(input);
        REQUIRE(input == expected);
    }

    SECTION("Test with Advents example 3")
    {
        std::vector<int> input{ 2, 3, 0, 3, 99 }; // NOLINT
        const std::vector<int> expected = { 2, 3, 0, 6, 99 };
        Intcode::calculate(input);
        REQUIRE(input == expected);
    }

    SECTION("Test with Advents example 4")
    {
        std::vector<int> input{ 2, 4, 4, 5, 99, 0 }; // NOLINT
        const std::vector<int> expected = { 2, 4, 4, 5, 99, 9801 };
        Intcode::calculate(input);
        REQUIRE(input == expected);
    }

    SECTION("Test with Advents example 5")
    {
        std::vector<int> input{ 1, 1, 1, 4, 99, 5, 6, 0, 99 }; // NOLINT
        const std::vector<int> expected = { 30, 1, 1, 4, 2, 5, 6, 0, 99 };
        Intcode::calculate(input);
        REQUIRE(input == expected);
    }

    SECTION("Test with Advents example 6")
    {
        std::vector<int> input{ 1002, 4, 3, 4, 33 };
        const std::vector<int> expected = { 1002, 4, 3, 4, 99 };
        Intcode::calculate(input);
        REQUIRE(input == expected);
    }
}
