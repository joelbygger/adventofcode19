#include "password.hpp"
#include <string>
#include <vector>


namespace
{
    bool atLeastOneAdjacentSame(const std::string& passStr)
    {
        char prev = passStr.at(0);
        for (size_t i = 1; i < passStr.size(); i++) {
            if (prev == passStr.at(i)) {
                return true;
            }
            prev = passStr.at(i);
        }
        return false;
    }

    bool onlyIncrementOrEqual(const std::string& passStr)
    {
        int prev = 0;
        for (const auto c : passStr) {
            int i = static_cast<int>(c);
            if (i < prev) {
                return false;
            }
            prev = i;
        }
        return true;
    }
} // namespace

bool password::isValid(const int pass)
{
    if (pass > 999999 || pass < 111111) {
        return false;
    }

    const auto passStr = std::to_string(pass);

    if (atLeastOneAdjacentSame(passStr)) {
        return onlyIncrementOrEqual(passStr);
    }
    return false;
}
