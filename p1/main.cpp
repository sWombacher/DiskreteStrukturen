#include "grayCode.hpp"
#include <iostream>

char translate(int val) {
    if (val < 0)
        return '-';
    return char(val) + 'a';
}

int main() {
    constexpr int q_1 = 2;
    constexpr int q_2 = 2;
    constexpr int q_3 = 3;
    constexpr int symbolCount_1 = 4;
    constexpr int symbolCount_2 = 4;
    constexpr int symbolCount_3 = 3;
    GrayCode<q_1, symbolCount_1, decltype(translate(0))> gray_1(translate);
    GrayCode<q_2, symbolCount_2, decltype(translate(0))> gray_2(translate);
    GrayCode<q_3, symbolCount_3, decltype(translate(0))> gray_3(translate);

    int example_counter = 1;
    auto next_example = [&example_counter](const char* str) {
        std::cout << std::endl;
        getchar();
        std::system("clear");
        printf("Example: %d\n%s\n\n", example_counter, str);
        int q = q_1;
        int sc = symbolCount_1;
        if (example_counter == 2) {
            q = q_2;
            sc = symbolCount_2;
        } else if (example_counter == 3) {
            q = q_3;
            sc = symbolCount_3;
        }
        printf("Parameter: q= %d, bits= %d\n\n\n", q, sc);
        ++example_counter;
    };
    std::cout << "Praktikum 1\n\nLiu Kin\nWombacher Sascha" << std::endl;

    auto iteration_function = [](const auto& gray, bool forward_iteration) {
        auto iter = forward_iteration ? gray.begin() : gray.rbegin();
        auto end = forward_iteration ? gray.end() : gray.rend();
        int idx = forward_iteration ? 0 : gray.vectorCount() - 1;

        while (iter != end) {
            std::cout << idx << ":\r\t" << iter;
            if (forward_iteration) {
                ++iter;
                ++idx;
            } else {
                --iter;
                --idx;
            }
        }
    };

    next_example("Direct rank/unrank access");
    constexpr int hard_coded_symbol = 8;
    auto iter_start = gray_1.begin(hard_coded_symbol);

    std::cout << iter_start << std::endl;
    std::cout << "value: " << gray_1.rank(iter_start) << std::endl << std::endl;

    std::cout << "Character translated:\n";
    auto charArray = gray_1.unrank(gray_1.rank(iter_start));
    for (auto& e : charArray)
        std::cout << e;

    next_example("Forward Iteration");
    iteration_function(gray_2, true);

    next_example("Backward Iteration");
    iteration_function(gray_3, false);

    getchar();
    return 0;
}
