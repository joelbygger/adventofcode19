/**
 *
 * Program reads a file. A bit of error checking is applied.
 *
 */
#include "orbits.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <utility>

namespace
{
    /**
     * Reads from file.
     * @param path Path to file.
     * @return File data to be used.
     */
    Orbits::rawStorage getInput(const char* path)
    {
        Orbits::rawStorage orbits;

        std::ifstream ifs(path, std::ios_base::in);
        if (!ifs) {
            std::cout << "Failed to open file.\n";
        }
        else {
            // Read the file.
            std::string center;
            while (std::getline(ifs, center, ')')) {
                std::string orbiter;
                std::getline(ifs, orbiter);
                orbits.emplace_back(make_pair(center, orbiter));
            }
        }

        return orbits;
    }
} // namespace

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "This program can only be run with a file name as an input. File is expected to contains ASCII "
                     "chars only.\n"
                  << argc << "\n";
    }
    else {
        std::cout << "Received path: " << argv[1] << "\n";

        // Read the file.
        Orbits::rawStorage orbits = getInput(argv[1]);

        if (!orbits.empty()) {
            Orbits orbs(orbits);
            int numOrbits = orbs.totOrbits();
            int dist = orbs.minDist("YOU", "SAN");
            std::cout << "Tot number direct + indirect orbits: " << numOrbits << "\n";
            std::cout << "Disance between the things: " << dist << "\n";
        }
    }
    return 0;
}
