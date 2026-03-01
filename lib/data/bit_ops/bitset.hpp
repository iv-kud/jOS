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

  bool test(uint8_t position) const {
    uint8_t block = position / 8;
    uint8_t bit = position % 8;
    return (m_data[block] >> bit) & 1U;
  }

  uint64_t data() const {
    uint8_t size = (N + 7) / 8;
    uint64_t value = 0;
    for (uint8_t i = 0; i < size; i++)
      value |= (uint64_t)m_data[i] << (8 * i);
    return value;
  }

  void setRange(const uint8_t start, const uint8_t end, uint64_t data);
  uint64_t valueRange(uint8_t start, uint8_t end) const;
private:
  uint8_t m_data[(N + 7) / 8];

  uint8_t fillStart(const uint8_t block, const uint8_t bit, uint64_t data) const
  {
    uint8_t rBits = 8 - bit;
    uint8_t mask = ((1U << rBits) - 1) << bit;
    uint8_t result = (m_data[block] & ~mask) | ((data << bit) & mask);
    return result;
  }

  uint8_t fillEnd(const uint8_t block, const uint8_t bit, uint64_t data) const {
    uint8_t lBits = bit + 1;
    uint8_t mask = (1U << lBits) - 1;
    uint8_t result = (m_data[block] & ~mask) | (data & mask);
    return result;
  }
};

template<uint8_t N>
inline void bitset<N>::setRange(const uint8_t start, const uint8_t end, uint64_t data)
{
  if (start > end || end >= N)
    return;
  uint8_t startBlock = start / 8;
  uint8_t endBlock = end / 8;
  uint8_t startBit = start % 8;
  uint8_t endBit = end % 8;
  if (startBlock == endBlock) {
      uint8_t mask = ((1U << (endBit - startBit + 1)) - 1) << startBit;
      m_data[startBlock] = (m_data[startBlock] & ~mask) | ((data << startBit) & mask);
    } else {
      m_data[startBlock] = fillStart(startBlock, startBit, data);
      data >>=(8 - startBit);
      for (uint8_t i = startBlock + 1; i < endBlock; ++i)
        {
          m_data[i] = uint8_t(data & 0xFF);
          data >>= 8;
        }
      m_data[endBlock] = fillEnd(endBlock, endBit, data);
    }
}

template <uint8_t N>
inline uint64_t bitset<N>::valueRange(uint8_t start, uint8_t end) const {
  if (start > end || end >= N)
    return 0;
  uint8_t size = end - start + 1;
  uint64_t value = 0;
  for (int i = 0; i < size; ++i) {
      uint8_t numBits = start + i;
      uint8_t startBlock = numBits / 8;
      uint8_t startBit = numBits % 8;
      uint64_t bit = (m_data[startBlock] >> startBit) & 1U;
      value |= (bit << i);
  }
  return value;
}

#endif
