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

static_assert(
    sizeof(Segment_Descriptor) == 8,
    "GDT segment descriptor must be 8 bytes");
} // namespace GDT

namespace IDT {
struct Segment_Descriptor
{
    uint16_t low_offset;
    uint16_t segment_selector;
    uint8_t zero;
    uint8_t gate_type;
    uint16_t high_offset;
}__attribute__((packed));

static_assert(
    sizeof(Segment_Descriptor) == 8,
    "IDT gate descriptor must be 8 bytes");
} // namespace IDT

struct Descriptor
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static_assert(
    sizeof(Descriptor) == 6,
    "GDTR/IDTR descriptor must be 6 bytes");
} // namespace Table
