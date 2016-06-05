#include "group.hpp"
#include <iostream>


int main(){
    std::cout << "Praktikum 2\n\nLiu Kin\nWombacher Sascha" << std::endl;

    auto newGroup = [](const char* str){
        getchar();
        std::system("clear");
        std::cout << str << std::endl << std::endl;
    };

    newGroup("Multiplication");
    Permutation<int, 6> per1 = {1,0,3,2,5,4};
    Permutation<int, 6> per2 = {5,4,1,3,2,0};

    std::cout << "Permutation 1:\n" << per1 << std::endl << std::endl
              << "Permutation 2:\n" << per2 << std::endl << std::endl
              << std::endl << std::endl;

    per1.applyPermutation(per2);
    std::cout << "Apply permutation 2 on permutation 1:\n" << per1 << std::endl << std::endl;

    newGroup("Inverse");
    Permutation<int, 4> ori = {0,2,3,1};
    Permutation<int, 4> inv = ori.insversePermutation();
    std::cout << "Original permutation: " << ori << std::endl
              << "Inverse  permutation: " << inv << std::endl
              << "Original * permutation: " << ori * inv << std::endl
              << std::endl;


/// Group example
    newGroup("simple group example");
    Group<int, 8> simpleExample = {
        {1,2,3,4,5,6,7,0}
    };
    std::cout << "Size:\t" << simpleExample.size() << std::endl << std::endl;
    std::cout << simpleExample << std::endl << std::endl;

/// triangle
    newGroup("Reguläres Dreieck");
    Group<int, 3> triangle = {
        {0,2,1},
        {1,2,0}
    };
    std::cout << "Size:\t" << triangle.size() << std::endl << std::endl;
    std::cout << triangle << std::endl << std::endl;


/// rectangle
    newGroup("Allgemeines Rechteck");
    Group<int, 4> rectangle = {
        {2,3,0,1},
        {1,0,3,2},
        {3,2,1,0}
    };
    std::cout << "Size:\t" << rectangle.size() << std::endl << std::endl;
    std::cout << rectangle << std::endl << std::endl;


/// tetraeder
    newGroup("Tetraeder");
    Group<int, 4> tetraeder = {
        {0,2,3,1},
        {1,0,2,3}
    };
    std::cout << "Size:\t" << tetraeder.size() << std::endl << std::endl;
    std::cout << tetraeder << std::endl << std::endl;


/// dice
    newGroup("Würfel");
    Group<int, 8> dice = {
        {1,2,3,0,5,6,7,4}, // face rotation x axis
        {4,5,1,0,7,6,2,3}, // face rotation y axis
        {1,5,6,2,0,4,7,3}, // face rotation z axis

        {1,0,3,2,5,4,7,6}, // mirror x axis
        {4,5,6,7,0,1,2,3}, // mirror y axis
        {3,2,1,0,7,6,5,4}  // mirror z axis
    };
    std::cout << "Size:\t" << dice.size() << std::endl << std::endl;
    std::cout << dice << std::endl << std::endl;


/// ikosaeders
    newGroup("Ikosaeders");
    Group<int, 12> ikosaeders = {
        {0,2,3,4,5,1,7,8,9,10,6,11}, // rotation on vertices 0 and 11
        {2,7,8,3,0,1,6,11,9,4,5,10}, // rotation on vertices 3 and 6
        {0,3,2,1,5,4,9,8,7,6,10,11}  // mirror on plain 0, 2, 10, 11
    };
    std::cout << "Size:\t" << ikosaeders.size() << std::endl << std::endl;
    std::cout << ikosaeders << std::endl << std::endl;

    getchar();
    return 0;
}
