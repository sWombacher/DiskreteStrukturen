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
    /*
    auto rank0 = gray.unrank(GRAY::vectorCount());

    auto iter_begin = gray.begin();
    std::cout << "Rank: " << gray.rank(iter_begin) << std::endl;

    for (const auto& e : rank0)
        std::cout << e << ' ';
    std::cout << std::endl << std::endl << std::endl;
    */

    auto iter_start = gray.begin(8);
    std::cout << iter_start << std::endl;
    std::cout << "value: " << gray.rank(iter_start) << std::endl << std::endl;

    std::cout << std::endl << std::endl;
    for (GRAY::Iterator iter = gray.begin(), end = gray.end(); iter != end; ++iter)
        std::cout << iter;


    return 0;
}
