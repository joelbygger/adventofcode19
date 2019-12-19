/**
 *
 * Program reads a file. A bit of error checking is applied.
 *
 */
#include "password.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{

} // namespace

int main()
{
    int validCnt = 0;
    for(int i = 273025; i <= 767253; i++) {
        validCnt += static_cast<int>(password::isValid(i));
    }

    std::cout << "Possible password cnt: " << validCnt << "\n";
    
    return 0;
}
