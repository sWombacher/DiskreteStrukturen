#include "Orbit.hpp"
#include <iostream>

int main(){
    std::cout << "Praktikum 3\n\nLiu Kin\nWombacher Sascha" << std::endl;
    auto newGroup = [](const char* str){
        getchar();
        std::system("clear");
        std::cout << str << std::endl << std::endl;
    };

    newGroup("Test a: Example from lesson");
    std::cout << "n = 4, k = 2\n"
                 "γ0 = (0 1 2 3)"
              << "\nResult:\n\n\n";

    OrbitGroup<int, 4, 2> groupA = { {1, 2, 3, 0} };
    std::cout << groupA;


/*
    newGroup("Test b: Example from lesson");
    std::cout << "n = 4, k = 3\n"
                 "γ0 = (0 3 1 2)\n"
                 "γ1 = (0 1)"
              << "\nResult:\n\n\n";

    OrbitGroup<int, 4, 3> groupB = { {1, 0, 2, 3}, {3, 1, 2, 0} };
    std::cout << groupB;
*/


    newGroup("Test c: Example from lesson");
    std::cout << "n = 4, k = 2\n"
                 "γ0 = (0 2 3)\n"
                 "γ1 = (2 3)"
              << "\nResult:\n\n\n";

    OrbitGroup<int, 4, 2> groupC = { {0, 1, 3, 2}, {2, 1, 3, 0} };
    std::cout << groupC;



    newGroup("Test 1");
    std::cout << "n = 6, k = 3\n\n"
                 "γ0 = (1, 3)(2, 4)\n"
                 "γ1 = (0, 3, 5, 2)(1, 4)" << std::endl << std::endl
              << "\nResult:\n\n\n";

    OrbitGroup<int, 6, 3> group1 = { {0, 3, 4, 1, 2, 5}, {3, 4, 0, 5, 1, 2} };
    std::cout << group1;



    newGroup("Test 2");
    std::cout << "n = 8, k = 4\n\n"
                 "γ0 = (0, 5)(1, 4)(2, 3)(7, 6)\n"
                 "γ1 = (0, 1)(2, 7)(3, 6)(4, 5)"
              << std::endl << std::endl
              << "\nResult:\n\n\n";

    OrbitGroup<int, 8, 4> group2 = { {5, 4, 3, 2, 1, 0, 7, 6}, {1, 0, 7, 6, 5, 4, 3, 2} };
    std::cout << group2;



    newGroup("Test 3");
    std::cout << "n = 14, k = 5\n\n"
                 "γ0 = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13)\n"
                 "γ1 = (0, 13)(1, 12)(2, 11)(3, 10)(4, 9)(5, 8)(6, 7)"
              << std::endl << std::endl
              << "Result: " << std::endl;

    OrbitGroup<int, 14, 5> group3 = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0},
        {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}
    };
    std::cout << group3;



    newGroup("Test 4");
    std::cout << "n = 31, k = 5\n\n"
                 "γ0 = \t( 0, 19,  9,  4, 21, 10, 16, 27, 13,  6, 22, 30, 26, 24, 23,\n\t 11,  5,  2, 20, 29, 14, 18, 28, 25, 12, 17,  8, 15,  7,  3,  1)\n\n"
                 "γ1 = \t( 0, 21, 26,  7,  3)\n\t( 1,  9, 13, 14, 24)\n\t( 2, 27, 20,  6, 28)\n\t( 4, 22, 12, 18, 11)\n\t( 5, 10, 23, 19, 16)\n\t( 8, 17, 25, 29, 30)"
              << std::endl << std::endl
              << "\nResult:\n\n\n";

    OrbitGroup<int, 31, 5> group4 = {
        {19, 0, 20, 1, 21, 2, 22, 3, 15, 4, 16, 5, 17, 6, 18, 7, 27, 8, 28, 9, 29, 10, 30, 11, 24, 12, 24, 13, 25, 14, 26},
        {21, 9, 27, 0, 22, 10, 28, 3, 17, 13, 23, 4, 18, 14, 24, 15, 5, 25, 11, 16, 6, 26, 12, 19, 1, 29, 7, 20, 2, 30, 8}
    };
    std::cout << group4;



    newGroup("\n\n\n\n\nDanke für die Aufmerksamkeit\n\n\n\n\n\n\n");
    getchar();
    return 0;
}
