#include "grayCode.hpp"
#include <iostream>

char translate(int val) {
    if (val < 0)
        return '-';
    return char(val) + '0';
}

int main() {
    constexpr int q = 2;
    constexpr int symbolCount = 4;
    typedef GrayCode<q, symbolCount, decltype(translate(0))> GRAY;

    GRAY gray(translate);
    auto rank0 = gray.unrank(GRAY::vectorCount());

    auto iter_begin = gray.begin();
    std::cout << "Rank: " << gray.rank(iter_begin) << std::endl;

    for (const auto& e : rank0)
        std::cout << e << ' ';
    std::cout << std::endl;

    return 0;
}
