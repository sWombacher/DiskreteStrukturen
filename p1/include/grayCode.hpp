#ifndef HPP_HPP_GRAY_CODE_HPP_HPP
#define HPP_HPP_GRAY_CODE_HPP_HPP
#pragma once

#include <functional>
#include <inttypes.h>
#include <algorithm>
#include <iostream>
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
            if (!this->_successor()) {
                // increase not possible
                // -> last empty element
                for (auto& e : this->m_Data)
                    e = -1;
            }
            return *this;
        }
        Iterator& operator++(int) { return ++(*this); }
        Iterator& successor() { return ++(*this); }

        Iterator& operator--() {
            if (!this->_successor(0, false)) {
                // increase not possible
                // -> last empty element
                for (auto& e : this->m_Data)
                    e = -1;
            }
            return *this;
        }
        Iterator& operator--(int) { return --(*this); }
        Iterator& predecessor() { return ++(*this); }

        const Iterator& operator*() { return *this; }

        bool operator==(const Iterator& rhs) const {
            return this->m_Data == rhs.m_Data;
        }
        bool operator!=(const Iterator& rhs) const {
            return this->m_Data != rhs.m_Data;
        }
        const std::array<int, _SymbolCount>& getRawData() const {
            return this->m_Data;
        }

        friend std::ostream& operator<<(std::ostream& os, const Iterator& rhs) {
            for (const auto& e : rhs.m_Data)
                os << e << ' ';
            os << std::endl;
            return os;
        }

      private:
        friend GrayCode;
        Iterator() = default;

        bool _successor(size_t recursionDepth = 0, bool increase = true) {
            if (recursionDepth >= this->m_Data.size())
                return false;

            const int myIdx = this->m_Data.size() - 1 - recursionDepth;
            const int myValue = this->m_Data[myIdx];

            const bool rec_increase = myValue & 1 ? !increase : increase;
            bool ret = this->_successor(recursionDepth + 1, rec_increase);

            if (!ret) {
                // try in-/de-creasing own value
                if (increase) {
                    if (myValue < q - 1)
                        ++this->m_Data[myIdx];
                    else
                        return false;
                } else {
                    if (myValue > 0)
                        --this->m_Data[myIdx];
                    else
                        return false;
                }
            }
            return true;
        }
        std::array<int, _SymbolCount> m_Data;
    };

    int rank(const Iterator& iter) const {
        const auto& data = iter.m_Data;
        return this->_rank(data);
    }
    std::array<_AlphabetType, _SymbolCount> unrank(int rank) const {
        std::array<_AlphabetType, _SymbolCount> toReturn;
        decltype(Iterator::m_Data) data;
        this->_unrank(rank, data);
        for (std::size_t i = 0; i < toReturn.size(); ++i)
            toReturn[i] = this->m_AlphabetTranslator(data[i]);
        return toReturn;
    }

    Iterator begin(size_t rank = 0) const {
        if (rank >= COUNT)
            return this->end();

        Iterator toReturn;
        this->_unrank(rank, toReturn.m_Data);
        return toReturn;
    }
    Iterator end() const {
        Iterator toReturn;
        for (auto& e : toReturn.m_Data)
            e = -1;
        return toReturn;
    }

    Iterator rbegin(size_t reverse_rank = 0) const {
        return this->begin(MY_TYPE::COUNT - 1 - reverse_rank);
    }
    Iterator rend() const { return this->end(); }

    static constexpr size_t vectorCount() { return MY_TYPE::COUNT; }

  private:
    int _rank(const decltype(Iterator::m_Data)& data,
              size_t recursionDepth = 0) const {
        if (recursionDepth >= data.size())
            return 0;

        int myValue = data[data.size() - 1 - recursionDepth];
        int skipRatio = COUNT / q;
        for (size_t i = 0; i < recursionDepth; ++i)
            skipRatio /= q;

        int recVal = this->_rank(data, recursionDepth + 1);
        bool revertOrder = myValue & 1;
        return skipRatio * myValue +
               (revertOrder ? skipRatio - recVal - 1 : recVal);
    }
    void _unrank(int rank, decltype(Iterator::m_Data)& dataOut,
                 size_t recursionDepth = 0, bool invert_value = false) const {
        if (recursionDepth >= dataOut.size())
            return;

        int skipRatio = MY_TYPE::COUNT / q;
        for (size_t i = 0; i < recursionDepth; ++i)
            skipRatio /= q;

        int myValue = 0;

        // calculate value to set
        // and adjust rank value for recursive call
        while (rank >= skipRatio) {
            ++myValue;
            rank -= skipRatio;
        }

        // value invert requried?
        if (invert_value)
            myValue = q - 1 - myValue;

        // on odd myValue invert switch_value
        if (myValue & 1)
            invert_value = !invert_value;

        dataOut[dataOut.size() - 1 - recursionDepth] = myValue;
        this->_unrank(rank, dataOut, recursionDepth + 1, invert_value);
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
