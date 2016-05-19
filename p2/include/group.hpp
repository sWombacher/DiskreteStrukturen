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
                for (size_t perIter = 0; perIter < lastSize; ++perIter)
                    this->m_Permutations.push_back(this->m_Permutations[perIter] * toMultiply);
            }

            // remove all duplicate permutations
            // Note:
            //      after implementing a "Permutation < Permutation" comparison
            //      a simple sort could create a speed up
            for (size_t lhs = 0      ; lhs < this->m_Permutations.size(); ++lhs){
            for (size_t rhs = lhs + 1; rhs < this->m_Permutations.size(); ++rhs){
                if (this->m_Permutations[lhs] == this->m_Permutations[rhs]){
                    // element is a duplicate
                    // remove it and readjust rhs iterator
                    this->m_Permutations.erase(std::begin(this->m_Permutations) + rhs);
                    --rhs;
                }
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
