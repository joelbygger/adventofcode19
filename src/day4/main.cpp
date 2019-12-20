/**
 *
 * Program reads a file. A bit of error checking is applied.
 *
 */
#include "password.hpp"
#include <iostream>

namespace
{

} // namespace

int main()
{
    int validCntSimple = 0;
    int validCntComplex = 0;
    for (int i = 273025; i <= 767253; i++) {
        validCntSimple += static_cast<int>(password::isValidSimple(i));
        validCntComplex += static_cast<int>(password::isValidComplex(i));
    }

    std::cout << "Task 1: possible password cnt: " << validCntSimple << "\n";
    std::cout << "Task 2: possible password cnt: " << validCntComplex << "\n";

    return 0;
}
