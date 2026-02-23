#ifndef BITSET_HPP
#define BITSET_HPP
#include "types/data_types.h"

template <uint8_t N>
class bitset
{
public:
  bitset() {
    for (int i = 0; i < (N + 7) / 8; ++i) {
        m_data[i] = 0;
      }
  }

  void set(uint8_t position, bool val = true){
    uint8_t block = position / 8;
    uint8_t bit = position % 8;
    if (val) {
        m_data[block] |= (1U << bit);
      } else {
        m_data[block] &= ~(1U << bit);
      }
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

  void setRange(const uint8_t start, const uint8_t end, uint64_t data);
  uint64_t getValueFromRange(uint8_t start, uint8_t end);
private:
  uint8_t m_data[(N + 7) / 8];

  uint8_t fillStart(const uint8_t block, const uint8_t bit, uint64_t &data) const
  {
    uint8_t lBits = 8 - bit;
    uint8_t mask = ((1U << lBits) - 1) << bit;
    uint8_t result = (m_data[block] & ~mask) | ((data << bit) & mask);
    data >>= lBits;
    return result;
  }

  uint8_t fillEnd(const uint8_t block, const uint8_t bit, uint64_t data) const {
    uint8_t rBits = bit + 1;
    uint8_t mask = (1U << rBits) - 1;
    uint8_t result = (m_data[block] & ~mask) | (data & mask);
    return result;
  }
};
#endif

template<uint8_t N>
inline void bitset<N>::setRange(const uint8_t start, const uint8_t end, uint64_t data)
{
  if (start > end)
    return;
  uint8_t startBlock = start / 8;
  uint8_t endBlock = end / 8;
  uint8_t startBit = start % 8;
  uint8_t endBit = end % 8;
  if (startBlock != endBlock)
    {
      m_data[startBlock] = fillStart(startBlock, startBit, data);
      for (uint8_t i = startBlock + 1; i < endBlock; ++i)
        {
          m_data[i] = data & 0xFF;
          data >>= 8;
        }
      m_data[endBlock] = fillEnd(endBlock, endBit, data);
    }  else if ((end - start + 1) <= 8) {
      uint8_t mask = ((1U << (endBit - startBit + 1)) - 1) << startBit;
      m_data[startBlock] = (m_data[startBlock] & ~mask) | ((data << startBit) & mask);
    }
}

template <uint8_t N>
inline uint64_t bitset<N>::getValueFromRange(uint8_t start, uint8_t end) {
  uint64_t value = 0;
  uint8_t startBlock = start / 8;
  uint8_t endBlock = end / 8;
  if (start > end)
    return ~0ULL;

  for (uint8_t i = startBlock; i <= endBlock; i++)
    value |= m_data[i] << (8 * i);
  return value;
}
