#include "keyboarddriver.h"
#include "arch/x86/core/portIO/port.h"
#include "display.h"

void KeyboardDriver::init()
{
    InterruptHandler::instance().registerHandlers(0x21, this);
}

void KeyboardDriver::handleInterrupt(Registers reg)
{
    uint8_t scancode = Port::read_port(0x60);

    jDebug() << "Keyboard scancode: " << NumberBase::Hex << (uint64_t) scancode;
}
