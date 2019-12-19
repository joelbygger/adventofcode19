#pragma once
#include <cstdint>
#include <utility>
#include <vector>

class Routes
{
public:
    using rawPoint = std::pair<char, int32_t>;
    using rawRoute = std::vector<rawPoint>;
    using rawRoutes = std::vector<rawRoute>;
    // Route is expected to be on format Rn or Dn or Un or Ln.
    void addRoutes(const rawRoutes& inRoutes);
    [[nodiscard]] int32_t getClosestIntersectionManhattanDist() const;
    [[nodiscard]] int32_t getSmallestManhattanDist() const;

private:
    struct point
    {
        uint64_t xy;
        int32_t totDist;
    };
    using aRoute = std::vector<struct point>;

    static aRoute calcRoute(const Routes::rawRoute& inRoute);
    static std::vector<aRoute> sortIntersections(const std::vector<Routes::aRoute>& inRoutes);
    static aRoute onlyDuplicates(const std::vector<Routes::aRoute>& inRoutes);
    static aRoute onlyDuplicatesCombineDist(const std::vector<Routes::aRoute>& inRoutes);

    std::vector<aRoute> m_routes;
};
