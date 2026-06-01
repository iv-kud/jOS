#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H

#include "irqdriver.h"

class KeyboardDriver : public IRQDriver
{
public:
    KeyboardDriver() = default;

    void init() override;
    void handleInterrupt(Registers reg) override;

private:
    static constexpr uint8_t KEYBOARD_DATA_PORT   = 0x60;
    static constexpr uint8_t KEYBOARD_STATUS_PORT = 0x64;
    static constexpr uint8_t KEYBOARD_IRQ_VECTOR  = 0x21;

    static constexpr uint8_t KEYBOARD_STATUS_OUTPUT_FULL = 0x01;
    static constexpr uint8_t KEYBOARD_SCANCODE_RELEASE   = 0x80;
};

#endif // KEYBOARDDRIVER_H
