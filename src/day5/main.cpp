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

    int modifyValuesAndRun(const std::vector<int>& intcodePrgm, const int noun, const int verb)
    {
        std::vector<int> intcodePrgmTest = intcodePrgm;
        intcodePrgmTest.at(1) = noun;
        intcodePrgmTest.at(2) = verb;
        Intcode::calculate(intcodePrgmTest);

        const int desiredRes = 19690720;
        if (intcodePrgmTest.at(0) == desiredRes) {
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
            std::cout << "Found desired res with 100*noun+verb: " << 100 * noun + verb << ", noun: " << noun
                      << ", verb: " << verb << "\n";
        }

        return intcodePrgmTest.at(0);
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
        const std::vector<int> intcodePrgm = getInput(argv[1]);

        if (!intcodePrgm.empty()) {
            std::cout << "Task 1:\n";
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
            std::cout << "Result pos 0: " << modifyValuesAndRun(intcodePrgm, 12, 2) << "\n";

            std::cout << "Task 2:\n";
            // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
            for (auto noun = 0; noun <= 99; noun++) {
                // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
                for (auto verb = 0; verb <= 99; verb++) {
                    modifyValuesAndRun(intcodePrgm, noun, verb);
                }
            }
        }
    }
    return 0;
}
