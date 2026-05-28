#include "interrupt_handler.h"
#include "arch/x86/drivers/irqdriver.h"
#include "lib/display/display.h"
#include "portIO/port.h"

InterruptHandler &InterruptHandler::instance()
{
    static InterruptHandler handler;
    return handler;
}

IRQDriver *InterruptHandler::getHandler(uint8_t num) const
{
    return m_drivers[num];
}

void InterruptHandler::registerHandlers(const uint8_t num, IRQDriver *driver)
{
    m_drivers[num] = driver;
}

void isr_handler(Registers reg)
{
    jDebug() << "Exeption: " << NumberBase::Hex << (uint64_t) reg.int_no;
}

void irq_handler(Registers reg)
{
    IRQDriver *driver = InterruptHandler::instance().getHandler(reg.int_no);

    jDebug() << "Interrupt vector: " << NumberBase::Hex << (uint64_t) reg.int_no;

    if (driver)
        driver->handleInterrupt(reg);
    else
        jWarning() << "No driver";

    if (reg.int_no >= 40)
        Port::write_port(SLAVE_PIC_COMMAND, PIC_EOI);

    Port::write_port(MASTER_PIC_COMMAND, PIC_EOI);
}
