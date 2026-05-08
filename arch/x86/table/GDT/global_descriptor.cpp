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
    bitset<64> codeSegment;

    codeSegment.setRange(16, 39, 0);
    codeSegment.setRange(56, 63, 0);
    codeSegment.setRange(0, 15, 0xFFFF);
    codeSegment.setRange(48, 51, 0xF);
    codeSegment.setRange(40, 47, 0x9A);
    codeSegment.setRange(52, 55, 0xC);

    return codeSegment.data();
}

uint64_t GlobalDescriptor::kernelDataSegment() const
{
    bitset<64> dataSegment;

    dataSegment.setRange(16, 39, 0);
    dataSegment.setRange(56, 63, 0);
    dataSegment.setRange(0, 15, 0xFFFF);
    dataSegment.setRange(48, 51, 0xF);
    dataSegment.setRange(40, 47, 0x92);
    dataSegment.setRange(52, 55, 0xC);

    return dataSegment.data();
}

uint64_t GlobalDescriptor::userCodeSegment() const
{
    bitset<64> codeSegment;

    codeSegment.setRange(16, 39, 0);
    codeSegment.setRange(56, 63, 0);
    codeSegment.setRange(0, 15, 0xFFFF);
    codeSegment.setRange(48, 51, 0xF);
    codeSegment.setRange(40, 47, 0xFA);
    codeSegment.setRange(52, 55, 0xC);

    return codeSegment.data();
}

uint64_t GlobalDescriptor::userdataSegment() const
{
    bitset<64> dataSegment;

    dataSegment.setRange(16, 39, 0);
    dataSegment.setRange(56, 63, 0);
    dataSegment.setRange(0, 15, 0xFFFF);
    dataSegment.setRange(48, 51, 0xF);
    dataSegment.setRange(40, 47, 0xF2);
    dataSegment.setRange(52, 55, 0xC);

    return dataSegment.data();
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
