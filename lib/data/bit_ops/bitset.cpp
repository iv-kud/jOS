#include "bitset.h"
template <uint8_t N>
inline bool bitset<N>::setToRange(uint8_t start, uint8_t end, uint64_t data) {
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
    }  else if ((end - start + 1) <= 8) {
      uint8_t mask = ((1 << (endBit - startBit + 1)) - 1) << startBit;
      m_data[startBlock] = (m_data[startBlock] & ~mask) | ((data << startBit) & mask);
      return true;
    }

  return false;
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
