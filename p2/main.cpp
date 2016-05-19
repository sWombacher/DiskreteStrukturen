#include "group.hpp"
#include <iostream>

int main(){
    //Permutation<int, 8> per = {1,2,3,0,5,6,7,4};
    Permutation<int, 6> per1 = {1,0,3,2,5,4};
    Permutation<int, 6> per2 = {5,4,1,3,2,0};

    std::cout << "Permutation 1:\n" << per1 << std::endl << std::endl
              << "Permutation 2:\n" << per2 << std::endl << std::endl
              << std::endl << std::endl;

    per1.applyPermutation(per2);
    std::cout << "Apply permutation 2 on permutation 1:\n" << per1 << std::endl << std::endl;

    per1.inversePermutation(per2);
    std::cout << "Inverse permutation:\n" << per1 << std::endl << std::endl;

    auto newGroup = [](const char* str){
        getchar();
        std::system("clear");
        std::cout << str << std::endl << std::endl;
    };

/// example
    newGroup("simple example");
    Group<int, 8> simpleExample = {
        {1,2,3,4,5,6,7,0}
    };
    std::cout << "Size:\t" << simpleExample.size() << std::endl << std::endl;
    std::cout << simpleExample << std::endl << std::endl;


/// triangle
    newGroup("Reguläres Dreieck");
    Group<int, 3> triangle = {
        {0,2,1}, {1,2,0}
    };
    std::cout << "Size:\t" << triangle.size() << std::endl << std::endl;
    std::cout << triangle << std::endl << std::endl;


/// rectangle
    newGroup("Allgemeines Rechteck");
    Group<int, 4> rectangle = {
        {2,3,0,1}, {1,0,3,2}, {3,2,1,0}
    };
    std::cout << "Size:\t" << rectangle.size() << std::endl << std::endl;
    std::cout << rectangle << std::endl << std::endl;


/// tetraeder
    newGroup("Tetraeder");
    Group<int, 4> tetraeder = {
        {0,2,3,1}, {1,0,2,3}
    };
    std::cout << "Size:\t" << tetraeder.size() << std::endl << std::endl;
    std::cout << tetraeder << std::endl << std::endl;


/// dice
    newGroup("Würfel");
    Group<int, 8> dice = {
        {1,2,3,0,4,5,6,7}, {1,0,2,3,4,5,6,7}, {4,1,2,3,0,5,6,7}, {3,1,2,0,4,5,6,7}
    };
    std::cout << "Size:\t" << dice.size() << std::endl << std::endl;
    std::cout << dice << std::endl << std::endl;


/// ikosaeders
    newGroup("Ikosaeders");
    Group<int, 3> ikosaeders = {

    };
    std::cout << "Size:\t" << ikosaeders.size() << std::endl << std::endl;
    std::cout << ikosaeders << std::endl << std::endl;

    getchar();
    return 0;
}
