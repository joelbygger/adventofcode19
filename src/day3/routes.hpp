#include <list>
#include <map>
#include <string>
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
    //[[nodiscard]] int32_t getSmallestManhattanDist() const;

private:
    struct point
    {
        uint64_t xy;
        uint32_t totDist;
    };
    using aRoute = std::vector<struct point>;

    static aRoute calcRoute(const Routes::rawRoute& inRoute);

    std::vector<aRoute> m_routes;
};
