#ifndef BITSET_HPP
#define BITSET_HPP
#include "../types/base.hpp"
template <uint8_t N>
struct bitset
{
private:
    uint8_t m_data[(N + 7) / 8];
public:
    void set(uint8_t position, bool val = true) {
        uint8_t block = position / 8;
        uint8_t bit = position % 8;
        if (val)
            m_data[block] |= (1U << bit);
        else
            m_data[block] &= ~(1U << bit);
    } 

    bool test(uint8_t position) {
        uint8_t block = position / 8;
        uint8_t bit = position % 8;
        return (m_data[block] >> bit) & 1U;        
    }

    uint64_t data() {
        uint8_t size = (N + 7) / 8;
        uint64_t result = 0;
        for (uint8_t i = 0; i < size; i++)
            result |= m_data[i] << (8 * i); 
        return result;
    }
};

#endif