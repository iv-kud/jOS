#pragma once
#include "types/data_types.h"

namespace Table {
  namespace GDT {
    struct Segment_Descriptor
    {
      uint16_t limit;
      uint16_t low_base;
      uint8_t mid_base;
      uint8_t access_byte;
      uint8_t flags_limit; // flags and limit - each 4 bits
      uint8_t high_base;
    }__attribute__((packed));
  }

  struct Descriptor
  {
    uint16_t limit;
    uint32_t base;
  }__attribute__((packed));
}
