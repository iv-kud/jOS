#include "pitdriver.h"
#include "arch/x86/core/portIO/port.h"
#include "display.h"

PITDriver::PITDriver(uint32_t frequency)
    : m_frequency(frequency)
{}

void PITDriver::init()
{
    InterruptHandler::instance().registerHandlers(PIT_IRQ_VECTOR, this);
    uint32_t divisor = PIT_BASE_FREQUENCY / m_frequency;

    Port::write_port(PIT_COMMAND_PORT, PIT_COMMAND_MODE3);

    uint8_t low  = static_cast<uint8_t>(divisor & 0xFF);
    uint8_t high = static_cast<uint8_t>((divisor >> 8) & 0xFF);

    Port::write_port(PIT_CHANNEL0_PORT, low);
    Port::write_port(PIT_CHANNEL0_PORT, high);
}

void PITDriver::handleInterrupt(Registers)
{
    ++m_ticks;

    if ((m_ticks % m_frequency) == 0)
        jDebug() << "Tick: " << m_ticks;
}

uint64_t PITDriver::ticks() const
{
    return m_ticks;
}

uint32_t PITDriver::frequency() const
{
    return m_frequency;
}
