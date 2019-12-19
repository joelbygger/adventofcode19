#include "routes.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>

Routes::aRoute Routes::calcRoute(const Routes::rawRoute& inRoute)
{
    int32_t dx = 0;
    int32_t dy = 0;
    bool ok = false;
    std::pair<int32_t, int32_t> currPos{ 0, 0 };
    aRoute outRoute;
    struct point tmp = { 0, 0 };
    outRoute.emplace_back(tmp); // Start at pos 0.

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
            // struct point p{0,0};
            struct point p = { 0, 0 };
            // A lot of casting to make sure signedbits are not travelling around etc.
            p.xy = static_cast<uint64_t>(currPos.first) << 32U
                | static_cast<uint64_t>(static_cast<uint32_t>(currPos.second));
            p.totDist += outRoute.back().totDist + abs(dx) + abs(dy);
            outRoute.push_back(p);
        }
    }
    return outRoute;
}

std::vector<Routes::aRoute> Routes::sortIntersections(const std::vector<Routes::aRoute>& inRoutes)
{
    auto routes = inRoutes; // Don't fiddle with storage.
    auto comp = [](const point& a, const point& b) { return a.xy < b.xy; };

    // For set_intersections to work routes must be sorted.
    for (auto& route : routes) {
        std::sort(route.begin(), route.end(), comp);
    }

    return routes;
}

Routes::aRoute Routes::onlyDuplicates(const std::vector<Routes::aRoute>& inRoutes)
{
    auto routes = inRoutes; // Don't fiddle with storage.
    auto comp = [](const point& a, const point& b) { return a.xy < b.xy; };

    // All crossings transferred to one array. Here we assume there are only two routes.
    aRoute crossings;
    std::set_intersection(routes.at(0).begin(),
                          routes.at(0).end(),
                          routes.at(1).begin(),
                          routes.at(1).end(),
                          std::back_inserter(crossings),
                          comp);

    return crossings;
}

Routes::aRoute Routes::onlyDuplicatesCombineDist(const std::vector<Routes::aRoute>& inRoutes)
{
    auto routes = inRoutes; // Don't fiddle with storage.

    // All crossings transferred to one array. Here we assume there are only two routes.
    aRoute crossings;
    for (auto pos : routes.at(0)) {
        auto it = std::find_if(routes.at(1).begin(), routes.at(1).end(), [&](const auto& a) { return a.xy == pos.xy; });

        if (it != routes.at(1).end()) {
            pos.totDist += it->totDist;
            crossings.emplace_back(pos);
        }
    }

    return crossings;
}

void Routes::addRoutes(const rawRoutes& inRoutes)
{
    for (const auto& inRoute : inRoutes) {
        m_routes.push_back(calcRoute(inRoute));
    }
}

int32_t Routes::getClosestIntersectionManhattanDist() const
{
    const auto crossings = onlyDuplicates(sortIntersections(m_routes));

    int32_t minDist = INT32_MAX;
    for (const auto& pos : crossings) {
        if (pos.xy > 0) {
            auto x = static_cast<int32_t>(pos.xy >> 32U);
            auto y = static_cast<int32_t>(pos.xy & 0xFFFFFFFFU);
            // std::cout << "x: " << x << ", y: " << y << "\n";
            minDist = std::min(minDist, abs(x) + abs(y));
        }
    }

    return minDist;
}

int32_t Routes::getSmallestManhattanDist() const
{
    auto crossings = onlyDuplicatesCombineDist(sortIntersections(m_routes));
    auto comp = [](const point& a, const point& b) { return a.totDist < b.totDist; };

    std::sort(crossings.begin(), crossings.end(), comp);

    // First elem is 0, I know that...
    return crossings.at(1).totDist;
}
