#ifndef BITSET_HPP
#define BITSET_HPP
#include "types/data_types.h"

template <uint8_t N>
class bitset
{
public:
  void set(uint8_t position, bool val = true);
  bool test(uint8_t position);
  uint64_t data();
  bool setToRange(uint8_t start, uint8_t end, uint64_t data);
  uint64_t getValueFromRange(uint8_t start, uint8_t end);
private:
  uint8_t m_data[(N + 7) / 8];
};
#endif
