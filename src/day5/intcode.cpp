#include "intcode.hpp"
#include <charconv>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <utility>

namespace
{
    enum class opcodes
    {
        add = 1,
        mul = 2,
        input = 3,
        output = 4,
        end = 99
    };

    enum class modeType
    {
        postion = 0,
        immediate = 1
    };

    struct modes
    {
        modeType param1 = modeType::postion;
        modeType param2 = modeType::postion;
        modeType param3 = modeType::postion;
    };

    void doMath(std::vector<int>& intcodePrgm,
                const size_t instrPtr,
                const struct modes& mode,
                const std::function<int(int, int)>& op)
    {
        // First assume everything is immediate mode, it makes implementaiton easier.
        auto noun = intcodePrgm.at(instrPtr + static_cast<size_t>(1));
        auto verb = intcodePrgm.at(instrPtr + static_cast<size_t>(2));
        auto resAddr = static_cast<int>(instrPtr + 3);

        if (mode.param1 == modeType::postion) {
            noun = intcodePrgm.at(static_cast<size_t>(noun));
        }
        if (mode.param2 == modeType::postion) {
            verb = intcodePrgm.at(static_cast<size_t>(verb));
        }
        if (mode.param3 == modeType::postion) {
            resAddr = intcodePrgm.at(static_cast<size_t>(resAddr));
        }

        intcodePrgm.at(static_cast<size_t>(resAddr)) = op(noun, verb);
    }

    void input(std::vector<int>& intcodePrgm, const size_t instrPtr, const struct modes& mode)
    {
        int input = 99;
        std::cout << "Place input: ";
        std::cin >> input;

        auto resAddr = static_cast<int>(instrPtr + 1);
        if (mode.param1 == modeType::postion) {
            resAddr = intcodePrgm.at(static_cast<size_t>(resAddr));
        }

        intcodePrgm.at(static_cast<size_t>(resAddr)) = input;
    }

    void output(std::vector<int>& intcodePrgm, const size_t instrPtr, const struct modes& mode)
    {
        auto out = static_cast<int>(instrPtr + 1);
        if (mode.param1 == modeType::postion) {
            out = intcodePrgm.at(static_cast<size_t>(out));
        }

        std::cout << "Output: " << intcodePrgm.at(static_cast<size_t>(out)) << "\n";
    }

    uint chrToNum(const char* start, const char* end)
    {
        uint tmp = 0;
        uint res = 0;
        auto [p, ec] = std::from_chars(start, end, tmp);
        if (ec != std::errc()) {
            std::cout << "Failed to convert string that begins with: " << *start << " and has this after end_ " << *end
                      << "\n";
        }
        else {
            res = tmp;
        }
        return res;
    }

    std::pair<struct modes, opcodes> getParams(const std::vector<int>& intcodePrgm, const size_t instrPtr) {
        const auto instruction = std::to_string(intcodePrgm.at(instrPtr));
        struct modes mode;
        uint opcodeTmp = 99;
        size_t pos = 0;

        switch (instruction.size()) {
        case 5: {
            uint tmp = chrToNum(instruction.data() + pos, instruction.data() + pos + 1);
            mode.param3 = tmp == 0 ? modeType::postion : modeType::immediate;
            pos++;
        }
            [[fallthrough]];
        case 4: {
            uint tmp = chrToNum(instruction.data() + pos, instruction.data() + pos + 1);
            mode.param2 = tmp == 0 ? modeType::postion : modeType::immediate;
            pos++;
        }
            [[fallthrough]];
        case 3: {
            uint tmp = chrToNum(instruction.data() + pos, instruction.data() + pos + 1);
            mode.param1 = tmp == 0 ? modeType::postion : modeType::immediate;
            pos++;
        }
            [[fallthrough]];

        case 2:
            opcodeTmp = chrToNum(instruction.data() + pos, instruction.data() + pos + 2);
            break;

        case 1:
            opcodeTmp = chrToNum(instruction.data() + instruction.size() - 1, instruction.data() + instruction.size());
            break;

        default:
            std::cout << "Oh terrible destiny, instruction is too long!\n";
            break;
        }

        return std::make_pair(mode, static_cast<opcodes>(opcodeTmp));
    }
} // namespace

void Intcode::calculate(std::vector<int>& intcodePrgm)
{
    bool done = false;
    size_t increment = 0;
    for (size_t instrPtr = 0; instrPtr < intcodePrgm.size() && !done; instrPtr += increment) {
        const auto [mode, opcode] = getParams(intcodePrgm, instrPtr);

        switch (opcode) {
        case opcodes::add:
            doMath(intcodePrgm, instrPtr, mode, std::plus<>());
            increment = 4;
            break;
        case opcodes::mul:
            doMath(intcodePrgm, instrPtr, mode, std::multiplies<>());
            increment = 4;
            break;
        case opcodes::input:
            input(intcodePrgm, instrPtr, mode);
            increment = 2;
            break;
        case opcodes::output:
            output(intcodePrgm, instrPtr, mode);
            increment = 2;
            break;
        case opcodes::end:
            done = true;
            break;
            // No default here, we use enum class and will get warnings from "clang-diagnostic-switch" or "-Wswitch".
        }
    }
}
