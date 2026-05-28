#include "interrupt_handler.h"
#include "lib/display/display.h"
#include "portIO/port.h"

InterruptHandler &InterruptHandler::instance()
{
    static InterruptHandler handler;
    return handler;
}

isr_t InterruptHandler::getHandler(uint8_t num)
{
    if (num < 0 || num > 255) {
        jWarning() << "Invalid interrupt number";
        return nullptr;
    }

    return m_handlers[num];
}

void InterruptHandler::registerHandlers(const uint8_t num, const isr_t handler)
{
    if (num < 0 || num > 255) {
        jWarning() << "Invalid interrupt number";
        return;
    }

    m_handlers[num] = handler;
}

void isr_handler(Registers reg)
{
    jDebug() << "Exeption: " << NumberBase::Hex << (uint64_t) reg.int_no;
    isr_t handler = InterruptHandler::instance().getHandler(reg.int_no);
    if (handler)
        handler(reg);
}

void irq_handler(Registers reg)
{
    jDebug() << "Interrupt: " << NumberBase::Hex << (uint64_t) reg.int_no;
    isr_t handler = InterruptHandler::instance().getHandler(reg.int_no);
    if (handler)
        handler(reg);

    if (reg.int_no >= 0x28)
        Port::write_port(SLAVE_PIC_COMMAND, PIC_EOI);

    Port::write_port(MASTER_PIC_COMMAND, PIC_EOI);
}
