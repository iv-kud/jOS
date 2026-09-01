#include "keyboarddriver.h"
#include "arch/x86/core/portIO/port.h"
#include "display.h"

KeyboardDriver::KeyboardDriver()
    : IRQDriver(KEYBOARD_IRQ_VECTOR)
{}

void KeyboardDriver::init()
{
    InterruptHandler::instance().registerHandlers(KEYBOARD_IRQ_VECTOR, this);
    enableLine();
}

void KeyboardDriver::handleInterrupt(const Registers &reg)
{
    uint8_t status = Port::read_port(KEYBOARD_STATUS_PORT);

    if (!(status & KEYBOARD_STATUS_OUTPUT_FULL))
        return;

    uint8_t scancode = Port::read_port(KEYBOARD_DATA_PORT);

    if (scancode & KEYBOARD_SCANCODE_RELEASE)
        return;

    jDebug() << "Keyboard scancode: " << NumberBase::Hex << static_cast<uint64_t>(scancode);
}
