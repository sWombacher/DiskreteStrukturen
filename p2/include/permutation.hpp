#ifndef HPP_HPP_PERMUTATION_HPP_HPP
#define HPP_HPP_PERMUTATION_HPP_HPP

#include <array>
#include <string>
#include <vector>

template<typename IntegerType, long long SIZE>
class Permutation final{
    typedef Permutation<IntegerType, SIZE> MY_TYPE;
public:
    Permutation() = default;
    Permutation(const Permutation&) = default;
    Permutation(Permutation&&) = default;
    ~Permutation()= default;

    Permutation& operator= (const Permutation&) = default;
    Permutation& operator= (Permutation&&) = default;
    bool operator==(const Permutation& rhs) const { return this->m_Data == rhs.m_Data; }

    Permutation(std::initializer_list<IntegerType> list) {
        int idx = 0;
        for (auto& e : list)
            this->m_Data[idx++] = e;
    }

    Permutation& operator*=(const Permutation& rhs){
        this->applyPermutation(rhs.m_Data);
        return *this;
    }
    Permutation  operator* (const Permutation& rhs) const{
        MY_TYPE cpy = *this;
        cpy *= rhs;
        return cpy;
    }

    void applyPermutation  (const MY_TYPE& rhs) { this->applyPermutation(rhs.m_Data); }
    void applyPermutation  (const std::array<IntegerType, SIZE>& per){
        std::array<IntegerType, SIZE> cpy = this->m_Data;
        for (size_t i = 0; i < per.size(); ++i)
            this->m_Data[i] = cpy[per[i]];
    }
    void undoPermutation(const MY_TYPE& rhs) { this->undoPermutation(rhs.m_Data); }
    void undoPermutation(const std::array<int, SIZE>& per){
        std::array<IntegerType, SIZE> cpy = this->m_Data;
        for (size_t i = 0; i < per.size(); ++i)
            this->m_Data[per[i]] = cpy[i];
    }

    friend std::ostream& operator<< (std::ostream& os, const MY_TYPE& per){
        std::array<bool, SIZE> usedIndices;
        std::fill(std::begin(usedIndices), std::end(usedIndices), false);

        std::string str;
        for (size_t i = 0; i < per.m_Data.size(); ++i){
            if (usedIndices[i])
                continue;

            IntegerType perIter = per.m_Data[i];
            std::vector<IntegerType> cycle;
            while (perIter != IntegerType(i)){
                if (usedIndices[perIter])
                    throw std::runtime_error("Error: not a valid permutation");
                usedIndices[perIter] = true;
                cycle.push_back(perIter);
                perIter = per.m_Data[perIter];
            }
            usedIndices[perIter] = true;
            cycle.push_back(perIter);

            // move smallest element to front
            perIter = 0;
            IntegerType currentLowest = cycle[0];
            for (size_t i = 1; i < cycle.size(); ++i){
                if (currentLowest > cycle[i]){
                    perIter = i;
                    currentLowest = cycle[i];
                }
            }

            if (perIter){
                std::vector<IntegerType> tmpCycle(cycle.size());
                for (size_t i = 0; i < cycle.size(); ++i)
                    tmpCycle[i] = cycle[(i + perIter) % cycle.size()];
                cycle = std::move(tmpCycle);
            }

            if (cycle.size() > 1){
                str += '(';
                for (auto& e : cycle)
                    str += std::to_string(e) + ' ';
                str[str.size() - 1] = ')';
            }
        }
        if (!str.size())
            str = "id";
        os << str;
        return os;
    }



private:
    std::array<IntegerType, SIZE> m_Data;
};


#endif // HPP_HPP_PERMUTATION_HPP_HPP
