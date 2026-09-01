#include "global_descriptor.h"
#include "bitset.hpp"
#include "display/display.h"
#include "core/panic.h"

GlobalDescriptor::GlobalDescriptor()
{
  if (!initTable())
    panic("Failed to initialize GDT");

  jInfo() << "[GDT] The table structure is correct";
  setTable();
}

bool GlobalDescriptor::initTable()
{
    uint64_t nullSegment = 0;
    setSegment(0, nullSegment);
    setSegment(1, kernelCodeSegment());
    setSegment(2, kernelDataSegment());
    setSegment(3, userCodeSegment());
    setSegment(4, userDataSegment());

    constexpr uint64_t expected[5] = {0x0000000000000000, 0x00CF9A000000FFFF, 0x00CF92000000FFFF, 0x00CFFA000000FFFF, 0x00CFF2000000FFFF};

    for (int i = 0; i < 5; ++i) {
        if (reinterpret_cast<uint64_t &>(m_table[i]) != expected[i])
            return false;
    }
    return true;
}

uint64_t GlobalDescriptor::kernelCodeSegment() const
{
    return makeSegment(0x9A);
}

uint64_t GlobalDescriptor::kernelDataSegment() const
{
    return makeSegment(0x92);
}

uint64_t GlobalDescriptor::userCodeSegment() const
{
    return makeSegment(0xFA);
}

uint64_t GlobalDescriptor::userDataSegment() const
{
    return makeSegment(0xF2);
}

uint64_t GlobalDescriptor::taskStateSegment() const
{
    ///TODO: Implement the TSS structure
    return 0;
}

void GlobalDescriptor::setTable()
{
    Table::Descriptor gdtr;
    gdtr.limit = 5 * sizeof(uint64_t) - 1;
    gdtr.base  = (uint32_t) m_table;

    flush_gdt(&gdtr);
}
///TODO: It is better to use the usual structure assignment.
///But I'm too lazy ;)
void GlobalDescriptor::setSegment(const uint8_t index, const uint64_t value)
{
  memcpy(&m_table[index], &value, sizeof(value));
}

uint64_t GlobalDescriptor::makeSegment(const uint8_t access) const
{
    bitset<64> segment;

    segment.setRange(0, 15, 0xFFFF);
    segment.setRange(16, 39, 0);
    segment.setRange(40, 47, access);
    segment.setRange(48, 51, 0xF);
    segment.setRange(52, 55, 0xC);
    segment.setRange(56, 63, 0);

    return segment.data();
}
