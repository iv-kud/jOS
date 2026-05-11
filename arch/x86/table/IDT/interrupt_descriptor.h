#ifndef INTERRUPT_DESCRIPTOR_H
#define INTERRUPT_DESCRIPTOR_H
#include "arch/x86/table/segment_descriptor.h"

#define CODE_SEGMENT 0x08
#define INTERRUPT_GATE 0x8E
class InterruptDescriptor
{
public:
    InterruptDescriptor();
    bool initTable();

private:
    void setGate(const uint8_t offset, const uint32_t handler, const uint8_t type);
    bool checkGate(const uint8_t offset, const uint32_t handler, const uint8_t type) const;
    void setTable();
    Table::IDT::Segment_Descriptor m_table[256];
};
extern "C" void flush_idt(Table::Descriptor *idt_ptr);

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

using InterruptHandler                  = void (*)();
static InterruptHandler isrHandlers[32] = {isr0,  isr1,  isr2,  isr3,  isr4,  isr5,  isr6,  isr7,  isr8,  isr9,  isr10, isr11, isr12, isr13, isr14, isr15,
                                           isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23, isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31};
#endif // INTERRUPT_DESCRIPTOR_H
