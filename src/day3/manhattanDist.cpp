#include "manhattanDist.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>

ManhattanDist::aRoute ManhattanDist::calcRoute(const ManhattanDist::rawRoute& inRoute)
{
    int32_t dx = 0;
    int32_t dy = 0;
    bool ok = false;
    std::pair<int32_t, int32_t> currPos{ 0, 0 };
    aRoute outRoute;
    outRoute.emplace_back(0); // Start at pos 0.

    for (const auto& move : inRoute) {
        // std::cout << "Dir: "<< move.first << ", steps: " << move.second << "\n";
        switch (move.first) {
        case 'U': {
            dx = 0;
            dy = 1;
            ok = true;
            break;
        }
        case 'D': {
            dx = 0;
            dy = -1;
            ok = true;
            break;
        }
        case 'R': {
            dx = 1;
            dy = 0;
            ok = true;
            break;
        }
        case 'L': {
            dx = -1;
            dy = 0;
            ok = true;
            break;
        }
        default:
            std::cout << "Terrible, received an unparseable character: " << move.first << "\n";
            ok = false;
            break;
        }

        // Mark route.
        auto steps = move.second;
        while (ok && steps-- > 0) {
            currPos.first += dx;
            currPos.second += dy;
            // A lot of casting to make sure signedbits are not travelling around etc.
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
            outRoute.push_back(static_cast<uint64_t>(currPos.first) << 32U
                               | static_cast<uint64_t>(static_cast<uint32_t>(currPos.second)));
        }
    }
    return outRoute;
}

int32_t ManhattanDist::addRoutes(const rawRoutes& inRoutes)
{
    for (const auto& inRoute : inRoutes) {
        m_routes.push_back(calcRoute(inRoute));
    }

    // For set_intersections to work routes must be sorted.
    for (auto& route : m_routes) {
        std::sort(route.begin(), route.end());
    }

    // All crossings transferred to one array. Here we assume there are only two routes.
    aRoute crossings;
    std::set_intersection(m_routes.at(0).begin(),
                          m_routes.at(0).end(),
                          m_routes.at(1).begin(),
                          m_routes.at(1).end(),
                          std::back_inserter(crossings));

    int32_t minDist = INT32_MAX;
    for (const auto& point : crossings) {
        if (point > 0) {
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
            auto x = static_cast<int32_t>(point >> 32U);
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
            auto y = static_cast<int32_t>(point & 0xFFFFFFFFU);
            // std::cout << "x: " << x << ", y: " << y << "\n";
            minDist = std::min(minDist, abs(x) + abs(y));
        }
    }

    return minDist;
}
