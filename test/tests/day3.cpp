#include "manhattanDist.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Manhattan distance calculator", "[woot]")
{
    SECTION("My Test 1")
    {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        std::vector<std::pair<char, int>> a {{'R', 3}, {'D', 2}};
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        std::vector<std::pair<char, int>> b {{'U', 2}, {'R', 5}, {'D', 4}, {'L', 7}};
        std::vector<std::vector<std::pair<char, int>>> data{ a, b};
        ManhattanDist tmp;
        REQUIRE(tmp.addRoutes(data) == 5);
    }

    SECTION("Test with Advents example 1")
    {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        std::vector<std::pair<char, int>> a {{'R', 75}, {'D', 30}, {'R', 83} ,{'U', 83}, {'L', 12}, {'D', 49}, {'R', 71}, {'U', 7} ,{'L', 72}};
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        std::vector<std::pair<char, int>> b {{'U', 62}, {'R', 66}, {'U', 55}, {'R', 34}, {'D', 71}, {'R', 55}, {'D', 58}, {'R', 83}};
        std::vector<std::vector<std::pair<char, int>>> data{ a, b};
        ManhattanDist tmp;
        REQUIRE(tmp.addRoutes(data) == 159);
    }

    SECTION("Test with Advents example 2")
    {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        std::vector<std::pair<char, int>> a {{'R', 98}, {'U', 47}, {'R', 26}, {'D', 63}, {'R', 33}, {'U', 87}, {'L', 62}, {'D', 20}, {'R', 33}, {'U', 53}, {'R', 51}};
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
        std::vector<std::pair<char, int>> b {{'U', 98}, {'R', 91}, {'D', 20}, {'R', 16}, {'D', 67}, {'R', 40}, {'U', 7}, {'R', 15}, {'U', 6}, {'R', 7}};
        std::vector<std::vector<std::pair<char, int>>> data{ a, b};
        ManhattanDist tmp;
        REQUIRE(tmp.addRoutes(data) == 135);
    }
}
