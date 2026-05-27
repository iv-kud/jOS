#include "interrupt_handler.h"
#include "lib/display/display.h"
#include "portIO/port.h"

isr_t InterruptHandler::m_handlers[256] = {nullptr};

isr_t InterruptHandler::getHandler(uint8_t num)
{
    return m_handlers[num];
}

void InterruptHandler::registerHandlers(const uint8_t num, const isr_t handler)
{
    m_handlers[num] = handler;
}

void isr_handler(Registers reg)
{
    jDebug() << "Exeption: " << NumberBase::Hex << (uint64_t) reg.int_no;
}

void irq_handler(Registers reg)
{
    isr_t handler = InterruptHandler::getHandler(reg.int_no);
    if (handler)
        handler(reg);

    if (reg.int_no >= 0x28)
        Port::write_port(0xA0, 0x20);

    Port::write_port(0x20, 0x20);
}
