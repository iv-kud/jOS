#ifndef GLOBAL_DESCRIPTOR_H
#define GLOBAL_DESCRIPTOR_H
#include "arch/x86/table/segment_descriptor.h"

class GlobalDescriptor
{
public:
    GlobalDescriptor();

private:
    bool initTable();
    void setTable();
    uint64_t makeSegment(const uint8_t access) const;
    uint64_t kernelCodeSegment() const;
    uint64_t kernelDataSegment() const;
    uint64_t userCodeSegment() const;
    uint64_t userdataSegment() const;
    uint64_t taskStateSegment() const;

    Table::GDT::Segment_Descriptor m_table[5];
};
extern "C" void flush_gdt(Table::Descriptor *gdt_ptr);
#endif // GLOBAL_DESCRIPTOR_H
