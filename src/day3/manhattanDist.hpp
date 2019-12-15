#include <list>
#include <map>
#include <string>
#include <vector>

class ManhattanDist
{
public:
    using rawPoint = std::pair<char, int>;
    using rawRoute = std::vector<rawPoint>;
    using rawRoutes = std::vector<rawRoute>;
    // Route is expected to be on format Rn or Dn or Un or Ln.
    int32_t addRoutes(const rawRoutes& inRoutes);

private:
    using aRoute = std::vector<uint64_t>;

    static aRoute calcRoute(const ManhattanDist::rawRoute& inRoute);

    std::vector<aRoute> m_routes;
};
