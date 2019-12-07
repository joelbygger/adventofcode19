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

    void doMath(std::vector<int>& intcodePrgm, const size_t opCodePos, const std::function<int(int, int)>& op)
    {
        const auto a = static_cast<size_t>(intcodePrgm.at(opCodePos + static_cast<size_t>(1)));
        const auto b = static_cast<size_t>(intcodePrgm.at(opCodePos + static_cast<size_t>(2)));
        const auto toPos = static_cast<size_t>(intcodePrgm.at(opCodePos + static_cast<size_t>(3)));
        intcodePrgm.at(toPos) = op(intcodePrgm.at(a), intcodePrgm.at(b));
    }
} // namespace

void Intcode::calculate(std::vector<int>& intcodePrgm)
{
    bool done = false;
    for (size_t i = 0; i < intcodePrgm.size() && !done; i += 4) {
        switch (intcodePrgm.at(i)) {
        case add:
            doMath(intcodePrgm, i, std::plus<>());
            break;
        case mul:
            doMath(intcodePrgm, i, std::multiplies<>());
            break;
        case end:
            done = true;
            break;
        default:
            std::cout << "Terrible failure, invalid opcode at pos: " << i << "\n";
            done = true;
            break;
        }
    }
}
