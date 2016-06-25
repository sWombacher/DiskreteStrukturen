#ifndef HPP_HPP_ORBIT_HPP_HPP
#define HPP_HPP_ORBIT_HPP_HPP

#include "../../p2/include/permutation.hpp"

#include <list>
#include <iostream>
#include <algorithm>

template<typename _IntegerType, long long SIZE, long long PARTITION_SIZE_K>
class OrbitGroup{
    typedef OrbitGroup<_IntegerType, SIZE, PARTITION_SIZE_K> MY_TYPE;
    typedef Permutation<_IntegerType, SIZE> MY_PERMUTATION;
    typedef Permutation<_IntegerType, PARTITION_SIZE_K, true> MY_PARTITION_PERMUTATION;
public:

    OrbitGroup(std::initializer_list<MY_PERMUTATION> generators) {
        // queue and omega starting with id of size "partitionSize_k"
        MY_PARTITION_PERMUTATION last;
        for (int i = 0; i < SIZE; ++i)
            last.data()[i] = (SIZE - PARTITION_SIZE_K) + i;

        auto containsPartition = [this](const MY_PARTITION_PERMUTATION& partition) -> bool{
            for (const auto& omega : this->m_Omegas){
                for (const auto& e : omega){
                    if (partition == e)
                        return true;
                }
            }
            return false;
        };
        MY_PARTITION_PERMUTATION unusedPartition = MY_PARTITION_PERMUTATION::GET_IDENTITY();

        for (size_t idx = 0;; ++idx) {
            // get unused permutation
            while (unusedPartition != last){
                if (containsPartition(unusedPartition)){
                    for (int i = PARTITION_SIZE_K - 1; i >= 0 && unusedPartition != last; --i){
                        ++unusedPartition.data()[i];
                        if (unusedPartition.data()[i] == SIZE)
                            unusedPartition.data()[i] = i;
                        else {
                            // validate partition
                            bool valid = true;

                            _IntegerType cur = unusedPartition.data()[0];
                            for (size_t i = 1; i < unusedPartition.data().size(); ++i){
                                if (cur < unusedPartition.data()[i])
                                    cur = unusedPartition.data()[i];
                                else{
                                    valid = false;
                                    break;
                                }
                            }
                            if (valid)
                                break;
                            else
                                i = PARTITION_SIZE_K;
                        }
                    }
                }
                else
                    break;
            }
            if (unusedPartition == last){
                // end reached?
                if (containsPartition(unusedPartition))
                    break;
            }

            // new orbit found
            this->m_Queues.emplace_back();
            this->m_Omegas.emplace_back();
            this->m_Alphas.emplace_back();

            this->m_Queues[idx].push_back(unusedPartition);
            this->m_Omegas[idx].push_back(unusedPartition);
            this->m_Alphas[idx].push_back(MY_PERMUTATION::GET_IDENTITY());

            auto omegaContainsElement = [this, &idx](const MY_PARTITION_PERMUTATION& p){
                for (auto& e : this->m_Omegas[idx]){
                    if (p == e)
                        return true;
                }
                return false;
            };

            while(this->m_Queues[idx].size()){
                MY_PARTITION_PERMUTATION x1 = this->m_Queues[idx].front();
                this->m_Queues[idx].pop_front();

                for (const auto& e : generators){
                    MY_PARTITION_PERMUTATION x2 = this->_adjustedPermutationMultiplication(x1, e);
                    if (!omegaContainsElement(x2)){
                        this->m_Queues[idx].push_back(x2);
                        this->m_Omegas[idx].push_back(x2);

                        MY_PERMUTATION alpha2add = this->m_Alphas[idx][this->m_Alphas[idx].size() - 1] * e;

                        bool addElement = true;
                        for (const auto& e : this->m_Alphas[idx]){
                            if (e == alpha2add){
                                addElement = false;
                                break;
                            }
                        }
                        if (addElement)
                            this->m_Alphas[idx].push_back(alpha2add);
                    }
                }
            }

            //this->m_SubGroupGenerators.emplace_back();
            auto transversals = MY_TYPE::_CALCULATE_TRANSVERSALE(this->m_Alphas[idx]);

            for (const auto& transversal : transversals){
                for (const auto& generator : generators){
                    auto tmp = generator * transversal;
                    tmp = tmp.insversePermutation() * tmp;
                    //this->m_SubGroupGenerators[idx].push_back(tmp);
                    //this->m_SubGroupGenerators[idx].pop_back();
                }
            }

            this->m_SubGroupGenerators.push_back(MY_TYPE::_CALCULATE_TRANSVERSALE(this->m_Alphas[idx]));
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const MY_TYPE& orbit){
        int idx = 0;
        os << "(Omega) Orbits:\n\n";
        for (const auto& omega : orbit.m_Omegas) {
            os << "Orbit representant: " << ++idx << std::endl;
            for (const auto& e : omega)
                os << e << "   ";
            os << std::endl << std::endl;
        }

        /*
        idx = 0;
        os << "\n\nAlphas:\n" << std::endl;
        for (const auto& alpha : orbit.m_Alphas) {
            os << "Alpha: " << ++idx << std::endl;
            for (const auto& e : alpha)
               os << e << std::endl;
            os << std::endl << std::endl << std::endl;
        }
        */

        idx = 0;
        os << "\n\nTransverstals:\n" << std::endl;
        for (const auto& generator : orbit.m_SubGroupGenerators) {
            os << "Transverstal: " << ++idx << std::endl;
            for (const auto& e : generator)
               os << e << std::endl;
            os << std::endl << std::endl << std::endl;
        }
        return os;
    }

private:
    std::vector<std::vector<MY_PERMUTATION>> m_SubGroupGenerators;

    struct Alpha{
        MY_PERMUTATION usedPermutation;
        MY_PARTITION_PERMUTATION object;
    };
    std::vector<std::vector<MY_PERMUTATION>> m_Alphas;
    std::vector<std::list  <MY_PARTITION_PERMUTATION>> m_Queues;
    std::vector<std::vector<MY_PARTITION_PERMUTATION>> m_Omegas;


    template<typename _ContainerType1, typename _ContainerType2>
    _ContainerType1 _adjustedPermutationMultiplication(const _ContainerType1& original, const _ContainerType2& toApply) {
        _ContainerType1 container;

        const auto& originalData = original.data();
        const auto& toApplyData = toApply.data();
        auto& containerData = container.data();

        for (size_t i = 0; i < containerData.size(); ++i)
            containerData[i] = toApplyData[originalData[i]];

        std::sort(std::begin(containerData), std::end(containerData));
        return container;
    }

    template<typename _ConteinerType>
    static std::vector<typename _ConteinerType::value_type> _CALCULATE_TRANSVERSALE(const _ConteinerType& generators){
        typedef typename _ConteinerType::value_type type;
        _ConteinerType delta = generators;
        std::vector<type> t;

        while (delta.size()){
            type x = delta[delta.size() - 1];
            delta.pop_back();

            std::list<type> queue;
            queue.push_back(x);
            t.push_back(x);

            while (queue.size()){
                type x1 = queue.front();
                queue.pop_front();

                for (const auto& e : generators){
                    type x2 = x1 * e;

                    for (auto iter = delta.begin(); iter != delta.end(); ++iter){
                        if (*iter == x2){
                            queue.push_back(x2);
                            delta.erase(iter);
                            break;
                        }
                    }
                }
            }
        }
        return t;
    }
};

#endif // HPP_HPP_ORBIT_HPP_HPP
