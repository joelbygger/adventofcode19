#include "password.hpp"
#include <algorithm>
#include <map>
#include <string>
#include <utility>
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
        int prev = static_cast<int>('0');
        for (const auto c : passStr) {
            int i = static_cast<int>(c);
            if (i < prev) {
                return false;
            }
            prev = i;
        }
        return true;
    }

    bool adjacentEqualsAlwaysPairs(const std::string& passStr)
    {
        std::map<char, int> nums;

        for (const auto& c : passStr) {

            if (nums.find(c) != nums.end()) {
                nums.at(c) += 1;
            }
            else {
                nums.emplace(std::make_pair(c, 1));
            }
        }

        return std::any_of(nums.cbegin(), nums.cend(), [](const auto& p) { return p.second == 2; });
    }
} // namespace

bool password::isValidSimple(const int pass)
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

bool password::isValidComplex(const int pass)
{
    if (pass > 999999 || pass < 111111) {
        return false;
    }

    if (isValidSimple(pass)) {
        const auto passStr = std::to_string(pass);
        return adjacentEqualsAlwaysPairs(passStr);
    }
    return false;
}
