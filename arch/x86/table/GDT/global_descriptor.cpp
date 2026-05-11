#include "global_descriptor.h"
#include "bitset.hpp"
#include "display/display.h"

GlobalDescriptor::GlobalDescriptor()
{
    if (initTable()) {
        jInfo() << "The table structure is correct";
        setTable();
    } else
        jError() << "the table structure is incorrect";
}

bool GlobalDescriptor::initTable()
{
    bitset<64> nullSegment;
    reinterpret_cast<uint64_t &>(m_table[0]) = nullSegment.data();
    reinterpret_cast<uint64_t &>(m_table[1]) = kernelCodeSegment();
    reinterpret_cast<uint64_t &>(m_table[2]) = kernelDataSegment();
    reinterpret_cast<uint64_t &>(m_table[3]) = userCodeSegment();
    reinterpret_cast<uint64_t &>(m_table[4]) = userdataSegment();

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

uint64_t GlobalDescriptor::userdataSegment() const
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
