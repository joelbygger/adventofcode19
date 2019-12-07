#include "fuel.hpp"
//#include <iostream>
#include <numeric>

namespace
{
    auto formula(int a, int b) -> int
    {
        // std::cout << "a: " << a << " b: " << b << "\n";
        int ret = 0;
        constexpr int minCalcuableWeight = 8; // 8 / 3 - 2 = 0, smallest number we allow to calculate with.
        if (b < minCalcuableWeight) {
            ret = a;
        }
        else {
            auto tmp = b / 3 - 2;
            // return a + (tmp >= 2 ? tmp - 2 : tmp);
            ret = formula(a + tmp, tmp);
        }
        return ret;
    }
} // namespace

namespace Fuel
{
    int accumulator(const std::vector<int>& weights)
    {

        auto sum = std::accumulate(weights.begin(), weights.end(), 0, formula);
        // std::cout << "woooza: " << sum << "\n";
        return sum;
    }
} // namespace Fuel
