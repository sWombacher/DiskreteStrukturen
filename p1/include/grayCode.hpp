#ifndef HPP_HPP_GRAY_CODE_HPP_HPP
#define HPP_HPP_GRAY_CODE_HPP_HPP
#pragma once

#include <functional>
#include <inttypes.h>
#include <algorithm>
#include <array>

template <int q, int _SymbolCount, typename _AlphabetType> struct GrayCode {

    template <typename _AlphabetTranslatorFunction>
    GrayCode(const _AlphabetTranslatorFunction& translaterFuntion)
        : m_AlphabetTranslator(translaterFuntion) {
        if (!this->m_AlphabetTranslator)
            throw std::runtime_error(
                "ERROR: Alphabet translator function not set!");
    }
    ~GrayCode() = default;

    struct Iterator {
        Iterator& operator++() {
            /// TODO
        }
        Iterator& operator++(int) { return ++(*this); }
        Iterator& succ() { return ++(*this); }

        bool operator==(const Iterator& rhs) const {
            return this->m_Data == rhs.m_Data;
        }
        bool operator!=(const Iterator& rhs) const {
            return this->m_Data != rhs.m_Data;
        }
        const std::array<_AlphabetType, _SymbolCount>& getRawData() const {
            return this->m_Data;
        }

      private:
        friend GrayCode;
        Iterator() = default;
        std::array<_AlphabetType, _SymbolCount> m_Data;
    };

    int rank(const Iterator& iter) const {
        const auto& data = iter.m_Data;
        return this->_rank(data);
    }
    std::array<_AlphabetType, _SymbolCount> unrank(int rank) const {
        std::array<_AlphabetType, _SymbolCount> toReturn;
        const Iterator iter = this->begin(rank);
        for (std::size_t i = 0; i < toReturn.size(); ++i)
            toReturn[i] = this->m_AlphabetTranslator(iter.m_Data[i]);
        return toReturn;
    }

    Iterator begin(size_t idx = 0) const {
        if (idx >= COUNT)
            return this->end();

        Iterator toReturn;

        /// TODO

        return toReturn;
    }
    Iterator end() const {
        Iterator toReturn;
        for (auto& e : toReturn.m_Data)
            e = -1;
        return toReturn;
    }

    static constexpr size_t vectorCount() { return MY_TYPE::COUNT; }

  private:
    int _rank(const decltype(Iterator::m_Data)& data, int recursionDepth = 0) const {
        if (recursionDepth == data.size())
            return 0;

        int myValue = data[data.size() - 1 - recursionDepth];
        int skipRatio = COUNT / q;
        for (int i = 0; i < recursionDepth; ++i)
            skipRatio /= q;

        int recVal = this->_rank(data, recursionDepth + 1);
        bool revertOrder = myValue & 1;
        return skipRatio * myValue +
               (revertOrder ? skipRatio - recVal - 1
                            : recVal);
    }

    static constexpr bool _validate_parameter() {
        for (int start = _SymbolCount; start > q; start /= q) {
            if (start % q)
                return false;
        }
        return true;
    }
    typedef GrayCode<q, _SymbolCount, _AlphabetType> MY_TYPE;
    constexpr static size_t _calculateCount() {
        size_t toReturn = 1;
        for (int i = 0; i < _SymbolCount; ++i)
            toReturn *= q;
        return toReturn;
    }
    static constexpr size_t COUNT = MY_TYPE::_calculateCount();

    const std::function<_AlphabetType(int)> m_AlphabetTranslator;
};

#endif
