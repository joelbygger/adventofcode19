#include "manhattanDist.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Manhattan distance calculator", "[woot]")
{
    SECTION("Test with Advents example 1")
    {
        std::vector<std::string> data{ "U1", "D12", "R12345678", "L00998" }; // NOLINT
        //std::vector<std::string> data{ "D12", "R12345678", "L00998" }; // NOLINT
        ManhattanDist tmp;
        REQUIRE(tmp.addRoute(data) == 1);
    }
}
