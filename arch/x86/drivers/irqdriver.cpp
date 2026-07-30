#include "irqdriver.h"
#include "arch/x86/core/portIO/port.h"
#include "portIO/commands/commands.h"
#include "lib/data/bit_ops/bitset.hpp"

IRQDriver::IRQDriver(uint8_t irqVector)
    :m_irqVector(irqVector)
{}

void IRQDriver::enableLine()
{
    irqInfo info = getIrqInfo(m_irqVector);
    if(!info.isValid)
        return;
    bitset<8> mask(Port::read_port(info.port));
    mask.set(info.irqLine, false);

    Port::write_port(info.port, static_cast<uint8_t>(mask.data()));

    if (info.isSlave) {
        constexpr uint8_t cascadeLine = 2;
        const uint16_t masterPort = static_cast<uint16_t>(Command::PIC::Port::MASTER_DATA);
        bitset<8> masterMask(Port::read_port(masterPort));
        masterMask.set(cascadeLine, false);

        Port::write_port(masterPort, static_cast<uint8_t>(masterMask.data()));
    }
}

void IRQDriver::disableLine()
{
    irqInfo info = getIrqInfo(m_irqVector);
    if(!info.isValid)
        return;

    bitset<8> mask(Port::read_port(info.port));
    mask.set(info.irqLine, true);

    Port::write_port(info.port, static_cast<uint8_t>(mask.data()));
}

irqInfo IRQDriver::getIrqInfo(const uint8_t vector) const
{
    if (vector >= 0x20 && vector <= 0x27) {
        return {
            static_cast<uint8_t>(vector - 0x20),
            static_cast<uint16_t>(Command::PIC::Port::MASTER_DATA),
            false,
            true
        };
    }

    if (vector >= 0x28 && vector <= 0x2F) {
        return {
            static_cast<uint8_t>(vector - 0x28),
            static_cast<uint16_t>(Command::PIC::Port::SLAVE_DATA),
            true,
            true
        };
    }
    return {0,0, false, false};
}
