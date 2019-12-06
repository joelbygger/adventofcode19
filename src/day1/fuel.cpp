#include "fuel.hpp"
//#include <iostream>
#include <numeric>

namespace Fuel
{
    int accumulator(const std::vector<int>& weights)
    {
        auto formula = [](int a, int b) {
            // std::cout << "a: " << a << " b: " << b << "\n";
            auto tmp = b / 3;
            return a + (tmp >= 2 ? tmp - 2 : tmp);
        };

        auto sum = std::accumulate(weights.begin(), weights.end(), 0, formula);
        // std::cout << "woooza: " << sum << "\n";
        return sum;
    }
} // namespace Fuel
