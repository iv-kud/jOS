#ifndef IRQDRIVER_H
#define IRQDRIVER_H
#include "arch/x86/interrupt/interrupt_handler.h"

struct irqInfo
{
    uint8_t irqLine;
    uint16_t port;
    bool isSlave;
    bool isValid;
};

class IRQDriver
{
public:
    explicit IRQDriver(uint8_t irqVector);
    virtual void init()                         = 0;
    virtual void handleInterrupt(Registers reg) = 0;
    void enableLine();
    void disableLine();

private:
    irqInfo getIrqInfo(const uint8_t vector) const;
    uint8_t m_irqVector;

protected:
    ~IRQDriver() = default;
};

#endif // IRQDRIVER_H
