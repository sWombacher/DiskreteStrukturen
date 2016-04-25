#include "grayCode.hpp"
#include <iostream>

char translate(int val) {
    if (val < 0)
        return '-';
    return char(val) + 'a';
}

int main() {
    constexpr int q[] = { 2, 2, 3, 10 };
    constexpr int symbolCount[] = { 4, 4, 3, 4 };
    GrayCode<q[0], symbolCount[0], decltype(translate(0))> gray_0(translate);
    GrayCode<q[1], symbolCount[1], decltype(translate(0))> gray_1(translate);
    GrayCode<q[2], symbolCount[2], decltype(translate(0))> gray_2(translate);
    GrayCode<q[3], symbolCount[3], decltype(translate(0))> gray_3(translate);

    int example_counter = 0;
    auto next_example = [&example_counter, &q, &symbolCount](const char* str) {
        std::cout << std::endl;
        getchar();
        std::system("clear");
        printf("Example: %d\n%s\n\n", example_counter, str);
        int _q = q[example_counter];
        int sc = symbolCount[example_counter];
        printf("Parameter: q= %d, bits= %d\n\n\n", _q, sc);
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
    auto iter_start = gray_0.begin(hard_coded_symbol);

    std::cout << iter_start << std::endl;
    std::cout << "value: " << gray_0.rank(iter_start) << std::endl << std::endl;

    std::cout << "Character translated:\n";
    auto charArray = gray_0.unrank(gray_0.rank(iter_start));
    for (auto& e : charArray)
        std::cout << e;

    next_example("Forward Iteration");
    iteration_function(gray_1, true);

    next_example("Backward Iteration");
    iteration_function(gray_2, false);

    next_example("Partial forward iteration");
    constexpr int START_POSITION = 95;
    constexpr int NUM_ITERATIONS = 30;
    printf("Startposition: %d, number of iterations: %d\n\n", START_POSITION, NUM_ITERATIONS);
    decltype (gray_3)::Iterator iter = gray_3.begin(START_POSITION);
    for (int i = 0; i < NUM_ITERATIONS; ++i){
        std::cout << "Rank: " << gray_3.rank(iter) << "\tObjekt: "<< iter;
        ++iter;
    }

    getchar();
    return 0;
}
