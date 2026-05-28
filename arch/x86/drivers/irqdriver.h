#ifndef IRQDRIVER_H
#define IRQDRIVER_H
#include "arch/x86/interrupt/interrupt_handler.h"

class IRQDriver
{
public:
    virtual void init()                         = 0;
    virtual void handleInterrupt(Registers reg) = 0;

protected:
    ~IRQDriver() = default;
};

#endif // IRQDRIVER_H
