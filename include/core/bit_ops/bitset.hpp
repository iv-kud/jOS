#ifndef BITSET_HPP
#define BITSET_HPP
#include <core/types/base.hpp>

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
        uint64_t value = 0;
        for (uint8_t i = 0; i < size; i++)
            value |= (uint64_t)m_data[i] << (8 * i); 
        return value;
    }

    bool setToRange(uint8_t start, uint8_t end, uint64_t data) {
        if (start > end)
            return false;
        uint8_t startBlock = start / 8;
        uint8_t endBlock = end / 8;
        uint8_t startBit = start % 8;
        uint8_t endBit = end % 8;
        if (startBlock != endBlock)
        {
            
            uint8_t firstBits = 8 - startBit;
            uint8_t firstMask = ((1 << firstBits) - 1) << startBit;
            m_data[startBlock] = (m_data[startBlock] & ~firstMask) | ((data << startBit) & firstMask);
            data >>= firstBits;

            for (uint8_t i = startBlock + 1; i < endBlock; i++)
            {
                m_data[i] = data & 0xFF;
                data >>= 8; 
            }

            uint8_t lastBits = endBit + 1;
            uint8_t lastMask = (1 << lastBits) - 1;
            m_data[endBlock] = (m_data[endBlock] & ~lastMask) | (data & lastMask);

            return true;
        }
        /*Save value in block and overwriting in the correct position*/
        else if ((end - start + 1) <= 8) {
            uint8_t mask = ((1 << (endBit - startBit + 1)) - 1) << startBit;
            m_data[startBlock] = (m_data[startBlock] & ~mask) | ((data << startBit) & mask);
            return true;
        }

        return false;
    }

    uint64_t getValueFromRange(uint8_t start, uint8_t end) {
        uint64_t value = 0;
        uint8_t startBlock = start / 8;
        uint8_t endBlock = end / 8;
        if (start > end)
            return ~0ULL;///< MAX VALUE 
        
        for (uint8_t i = startBlock; i <= endBlock; i++)
            value |= m_data[i] << (8 * i); 
        return value;
    }
};

#endif