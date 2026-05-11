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
    uint8_t flags_limit;
    uint8_t high_base;
} __attribute__((packed));
} // namespace GDT

namespace IDT {
struct Segment_Descriptor
{
    uint16_t low_offset;
    uint16_t segment_selector;
    uint8_t zero;
    uint8_t gate_type;
    uint16_t high_offset;
};
} // namespace IDT

struct Descriptor
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
} // namespace Table
