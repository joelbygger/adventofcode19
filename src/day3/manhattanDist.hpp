#include <list>
#include <map>
#include <string>
#include <vector>

class ManhattanDist
{
public:
    // ManhattanDist() : m_routes() {};// = default;
    // Returns the ID this route is assigned in the local matrix.
    // Route is expected to be on format Rn or Dn or Un or Ln.
    int addRoute(const std::vector<std::string>& route);

private:
    //using matrixPos = std::vector<int>;
    using matrixPos = std::map<int, int>; // route index, Mahattan distance
    using matrixCol = std::list<matrixPos>;
    using matrixRow = std::list<matrixCol>;

    int m_routeCnt{ 0 };
    // A matrix where each index conatins the route IDs that has passed through said point.
    matrixRow m_matrix;
    //const matrixRow::const_iterator m_centralPortX = m_matrix.begin();
    //const matrixCol::const_iterator m_centralPortY = m_matrix.front().begin();
    const matrixRow::iterator m_centralPortX = m_matrix.begin();
    const matrixCol::iterator m_centralPortY = m_matrix.front().begin();
};
