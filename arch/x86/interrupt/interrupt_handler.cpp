#include "interrupt_handler.h"
#include "arch/x86/drivers/irqdriver.h"
#include "lib/display/display.h"
#include "portIO/commands/commands.h"
#include "portIO/port.h"
#include "core/panic.h"

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

void isr_handler(const Registers *reg)
{
  jError() << "Exception: " << NumberBase::Hex << static_cast<uint64_t> (reg->int_no);
  jError() << "Error code: " << NumberBase::Hex << static_cast<uint64_t>(reg->err_code);
  /// For now, treat every CPU exception as fatal
  panic("Unhandled CPU exception");
}

void irq_handler(const Registers *reg)
{
    IRQDriver *driver = InterruptHandler::instance().getHandler(reg->int_no);
    if (driver)
        driver->handleInterrupt(*reg);

    if (reg->int_no >= 40)
        Port::write_port(static_cast<uint16_t>(Command::PIC::Port::SLAVE_COMMAND), static_cast<uint8_t>(Command::PIC::Value::EOI));

    Port::write_port(static_cast<uint16_t>(Command::PIC::Port::MASTER_COMMAND), static_cast<uint8_t>(Command::PIC::Value::EOI));
}
