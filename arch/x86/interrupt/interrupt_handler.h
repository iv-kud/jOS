#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H
#include "types/data_types.h"

#define MASTER_PIC_COMMAND 0x20
#define SLAVE_PIC_COMMAND 0xA0
#define PIC_EOI 0x20

struct Registers
{
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

class IRQDriver;

class InterruptHandler
{
public:
    static InterruptHandler &instance();
    IRQDriver *getHandler(uint8_t num) const;
    void registerHandlers(const uint8_t num, IRQDriver *driver);

    InterruptHandler(const InterruptHandler &)            = delete;
    InterruptHandler &operator=(const InterruptHandler &) = delete;

private:
    InterruptHandler()        = default;
    IRQDriver *m_drivers[256] = {nullptr};
};

extern "C" void isr_handler(Registers reg);
extern "C" void irq_handler(Registers reg);

#endif // INTERRUPT_HANDLER_H
