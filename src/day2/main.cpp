/**
 *
 * Program reads a file. A bit of error checking is applied.
 *
 */
#include "intcode.hpp"
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
    std::vector<int> getInput(const char* path)
    {
        std::vector<int> intcodePrgm;

        std::ifstream ifs(path, std::ios_base::in);
        if (!ifs) {
            std::cout << "Failed to open file.\n";
        }
        else {
            // Read the file.
            std::string str;
            while (std::getline(ifs, str, ',')) {
                intcodePrgm.emplace_back(std::stoi(str));
            }
        }

        return intcodePrgm;
    }

} // namespace

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "This program can only be run with a file name as an input. File is expected to contains ASCII chars only.\n" << argc << "\n";
    }
    else {
        std::cout << "Received path: " << argv[1] << "\n";

        // Read the file.
        std::vector<int> intcodePrgm = getInput(argv[1]);
        if (!intcodePrgm.empty()) {
            Intcode::calculate(intcodePrgm);
            std::cout << "Intcode program result pos 0: " << intcodePrgm.at(0) << "\n";
        }
    }
    return 0;
}
