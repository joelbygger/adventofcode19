#include "orbits.hpp"
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

int Orbits::numOrbits() const
{
    int sum = 0;

    for (const auto& [orbiter, center] : m_orbits) {
        sum = numOrbits(orbiter, sum + 1);
    }

    return sum;
}

/***********************************************************************************
 *
 * Private functions
 *
 **********************************************************************************/
int Orbits::numOrbits(const std::string& orbiter, const int sum) const
{
    int totSum = sum;

    //std::cout << "numOrbits priv: " << orbiter << "\n" << std::flush;
    // Sanity check.
    if (m_orbits.find(orbiter) == m_orbits.end()) {
        std::cout << "This orbiter does not exist in the list: \"" << orbiter
                  << "\", an exception will soon be thrown. Sum is now: " << sum << "\n";
    }

    if (m_orbits.at(orbiter) != m_centerPlanet) {
        totSum = numOrbits(m_orbits.at(orbiter), sum + 1);
    }

    return totSum;
}
