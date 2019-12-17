/**
 *
 * Program reads a file. A bit of error checking is applied.
 *
 */
#include "manhattanDist.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    /**
     * Reads from file.
     * @param path Path to file.
     * @return File data to be used.
     */
    ManhattanDist::rawRoutes getInput(const char* path)
    {
        ManhattanDist::rawRoute route;
        ManhattanDist::rawRoutes routes;

        std::ifstream ifs(path, std::ios_base::in);
        if (!ifs) {
            std::cout << "Failed to open file.\n";
        }
        else {
            while(!ifs.eof()) {
                // Read the file.
                char dir;
                int32_t dist;
                ifs >> dir >> dist;
                route.push_back({ dir, dist });

                if (ifs.peek() == ',') {
                    char delim;
                    ifs >> delim;
                }
                else {
                    routes.push_back(route);
                    route.clear();
                }
            }
        }

        return routes;
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
        const ManhattanDist::rawRoutes routes = getInput(argv[1]);
        ManhattanDist manhattan;
        manhattan.addRoutes(routes);
        const auto dist = manhattan.getClosetsIntersectionDist();
        std::cout << "Part1: Manhattan dist: " << dist << "\n";
    }

    return 0;
}
