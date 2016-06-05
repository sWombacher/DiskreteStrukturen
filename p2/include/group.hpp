#ifndef HPP_HPP_GROUP_HPP_HPP
#define HPP_HPP_GROUP_HPP_HPP

#include "permutation.hpp"

#include <iostream>
#include <vector>

template<typename IntegerType, long long SIZE>
class Group{
    typedef Group<IntegerType, SIZE> MY_TYPE;
    typedef Permutation<IntegerType, SIZE> PERMUTATION;
public:
    Group() = default;
    Group(std::initializer_list<PERMUTATION> list) { this->generateGroup(list); }

    /// TODO:
    ///     use constraints
    template<typename _ContainerType = std::vector<Permutation<IntegerType, SIZE>>> // default type for initializer lists
    void generateGroup(const _ContainerType& container){
        for (const auto& e : container)
            this->m_Permutations.push_back(e);

        size_t lastSize;
        do {
            lastSize = this->m_Permutations.size();
            for (const auto& toMultiply : container){
                for (size_t perIter = 0; perIter < lastSize; ++perIter){
                    const PERMUTATION tmp = this->m_Permutations[perIter] * toMultiply;
                    bool alreadyInVector = false;
                    for (const auto& e :this->m_Permutations){
                        if (e == tmp){
                            alreadyInVector = true;
                            break;
                        }
                    }
                    if (!alreadyInVector)
                        this->m_Permutations.push_back(tmp);
                }
            }
        } while (lastSize != this->m_Permutations.size());
    }

    friend std::ostream& operator<< (std::ostream& os, const MY_TYPE& group){
        for (const auto& e : group.m_Permutations)
            os << e << std::endl;
        return os;
    }

    /// TODO:
    ///     implement begin/end


    size_t size() const { return  this->m_Permutations.size(); }

private:
    std::vector<Permutation<IntegerType, SIZE>> m_Permutations;
};

#endif // HPP_HPP_GROUP_HPP_HPP
