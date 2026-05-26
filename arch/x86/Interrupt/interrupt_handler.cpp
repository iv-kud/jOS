#include "interrupt_handler.h"
#include "lib/display/display.h"

InterruptHandler::InterruptHandler() {}

void isr_handler(Registers reg)
{
    jInfo() << "Exeption: " << NumberBase::Hex << (uint64_t) reg.int_no;
}

void irq_handler(Registers reg)
{
    jInfo() << "Inerrupt: " << NumberBase::Hex << (uint64_t) reg.int_no;
}
