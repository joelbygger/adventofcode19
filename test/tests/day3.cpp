#include "routes.hpp"
#include <catch2/catch.hpp>
#include <utility>
#include <vector>


TEST_CASE("Manhattan distance calculator", "[woot]")
{
    SECTION("My Test 1")
    {
        std::vector<std::pair<char, int>> a{ { 'R', 3 }, { 'D', 2 } };
        std::vector<std::pair<char, int>> b{ { 'U', 2 }, { 'R', 5 }, { 'D', 4 }, { 'L', 7 } };
        std::vector<std::vector<std::pair<char, int>>> data{ a, b };
        Routes tmp;
        tmp.addRoutes(data);
        REQUIRE(tmp.getClosestIntersectionManhattanDist() == 5);
        REQUIRE(tmp.getSmallestManhattanDist() == 18);
    }

    SECTION("Test with Advents example 1")
    {
        std::vector<std::pair<char, int>> a{ { 'R', 75 }, { 'D', 30 }, { 'R', 83 }, { 'U', 83 }, { 'L', 12 },
                                             { 'D', 49 }, { 'R', 71 }, { 'U', 7 },  { 'L', 72 } };
        std::vector<std::pair<char, int>> b{ { 'U', 62 }, { 'R', 66 }, { 'U', 55 }, { 'R', 34 },
                                             { 'D', 71 }, { 'R', 55 }, { 'D', 58 }, { 'R', 83 } };
        std::vector<std::vector<std::pair<char, int>>> data{ a, b };
        Routes tmp;
        tmp.addRoutes(data);
        REQUIRE(tmp.getClosestIntersectionManhattanDist() == 159);
        REQUIRE(tmp.getSmallestManhattanDist() == 610);
    }

    SECTION("Test with Advents example 2")
    {
        std::vector<std::pair<char, int>> a{ { 'R', 98 }, { 'U', 47 }, { 'R', 26 }, { 'D', 63 },
                                             { 'R', 33 }, { 'U', 87 }, { 'L', 62 }, { 'D', 20 },
                                             { 'R', 33 }, { 'U', 53 }, { 'R', 51 } };
        std::vector<std::pair<char, int>> b{ { 'U', 98 }, { 'R', 91 }, { 'D', 20 }, { 'R', 16 }, { 'D', 67 },
                                             { 'R', 40 }, { 'U', 7 },  { 'R', 15 }, { 'U', 6 },  { 'R', 7 } };
        std::vector<std::vector<std::pair<char, int>>> data{ a, b };
        Routes tmp;
        tmp.addRoutes(data);
        REQUIRE(tmp.getClosestIntersectionManhattanDist() == 135);
        REQUIRE(tmp.getSmallestManhattanDist() == 410);
    }
}
