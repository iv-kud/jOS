#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H

#include "irqdriver.h"

class KeyboardDriver : public IRQDriver
{
public:
    KeyboardDriver() = default;
    void init() override;
    void handleInterrupt(Registers reg) override;
};

#endif // KEYBOARDDRIVER_H
