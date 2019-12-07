#include "intcode.hpp"
#include <functional>
#include <iostream>

namespace
{
    enum opcode
    {
        add = 1,
        mul = 2,
        end = 99
    };

    void doMath(std::vector<int>& intcodePrgm, const size_t instrPtr, const std::function<int(int, int)>& op)
    {
        const auto noun = static_cast<size_t>(intcodePrgm.at(instrPtr + static_cast<size_t>(1)));
        const auto verb = static_cast<size_t>(intcodePrgm.at(instrPtr + static_cast<size_t>(2)));
        const auto addrParamRes = static_cast<size_t>(intcodePrgm.at(instrPtr + static_cast<size_t>(3)));
        intcodePrgm.at(addrParamRes) = op(intcodePrgm.at(noun), intcodePrgm.at(verb));
    }
} // namespace

void Intcode::calculate(std::vector<int>& intcodePrgm)
{
    bool done = false;
    for (size_t instrPtr = 0; instrPtr < intcodePrgm.size() && !done; instrPtr += 4) {
        switch (intcodePrgm.at(instrPtr)) {
        case add:
            doMath(intcodePrgm, instrPtr, std::plus<>());
            break;
        case mul:
            doMath(intcodePrgm, instrPtr, std::multiplies<>());
            break;
        case end:
            done = true;
            break;
        default:
            std::cout << "Terrible failure, invalid opcode at instrPtr: " << instrPtr << "\n";
            done = true;
            break;
        }
    }
}
