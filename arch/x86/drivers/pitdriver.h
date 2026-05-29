#ifndef PITDRIVER_H
#define PITDRIVER_H

#include "irqdriver.h"

class PITDriver : public IRQDriver
{
public:
    explicit PITDriver(uint32_t frequency = 50);

    void init() override;
    void handleInterrupt(Registers reg) override;

    uint64_t ticks() const;
    uint32_t frequency() const;

private:
    static constexpr uint32_t PIT_BASE_FREQUENCY = 1193182;
    static constexpr uint8_t PIT_CHANNEL0_PORT   = 0x40;
    static constexpr uint8_t PIT_COMMAND_PORT    = 0x43;
    static constexpr uint8_t PIT_COMMAND_MODE3   = 0x36;
    static constexpr uint8_t PIT_IRQ_VECTOR      = 0x20;

    uint32_t m_frequency;
    uint64_t m_ticks = 0;
};

#endif
