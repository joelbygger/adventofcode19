#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
/*
namespace Planets
{
    using storage = std::vector<std::pair<std::string, std::string>>;
} // namespace Planets */

class Orbits
{
public:
    using rawStorage = std::vector<std::pair<std::string, std::string>>;
    explicit Orbits(const rawStorage& inOrbits);
    int totOrbits() const;

private:
    int totOrbits(const std::string& orbiter, const int sum) const;

    std::unordered_map<std::string, std::string> m_orbits;
    const std::string m_centerPlanet = "COM";
};
