#include "orbits.hpp"
#include <algorithm>
#include <iostream>

Orbits::Orbits(const rawStorage& inOrbits)
{
    for (const auto& p : inOrbits) {
        const auto& [center, orbiter] = p;
        // std::cout << center << " : " << orbiter << "\n";

        // Sanity check.
        if (m_orbits.find(orbiter) != m_orbits.end()) {
            std::cout << "This orbiter already exists: \"" << orbiter << "\" and it has value: \"" << m_orbits[orbiter]
                      << "\" and new value is: \"" << center << "\" old value will be overwritten.\n";
        }

        m_orbits[orbiter] = center;
    }
}

int Orbits::totOrbits() const
{
    int sum = 0;

    for (const auto& [orbiter, center] : m_orbits) {
        sum = totOrbits(orbiter, sum + 1);
    }

    return sum;
}

int Orbits::minDist(const std::string& start, const std::string& dest) const
{
    std::vector<std::string> startToCom;
    startToCom = createRouteToCenter(start, startToCom);

    std::vector<std::string> destToCom;
    destToCom = createRouteToCenter(dest, destToCom);

    for(size_t i = 0; i < startToCom.size(); i++) {
        auto it = std::find(destToCom.begin(), destToCom.end(), startToCom.at(i));
        if(it != destToCom.end())
        {
            return static_cast<int>(i) + static_cast<int>(std::distance(destToCom.begin(), it));
        }
    }

    return 0;
}

/***********************************************************************************
 *
 * Private functions
 *
 **********************************************************************************/

int Orbits::totOrbits(const std::string& orbiter, const int sum) const
{
    int totSum = sum;

    // Sanity check.
    if (m_orbits.find(orbiter) == m_orbits.end()) {
        std::cout << "This orbiter does not exist in the list: \"" << orbiter
                  << "\", an exception will soon be thrown. Sum is now: " << sum << "\n";
    }

    if (m_orbits.at(orbiter) != m_centerPlanet) {
        totSum = totOrbits(m_orbits.at(orbiter), sum + 1);
    }

    return totSum;
}

std::vector<std::string> Orbits::createRouteToCenter(const std::string& orbiter, std::vector<std::string>& route) const
{
    // Sanity check.
    if (m_orbits.find(orbiter) == m_orbits.end()) {
        std::cout << "This orbiter does not exist in the list: \"" << orbiter << "\"\n";
        return route;
    }

    auto& center = m_orbits.at(orbiter);
    route.emplace_back(center);

    if (center != m_centerPlanet) {
        route = createRouteToCenter(center, route);
    }

    return route;
}
