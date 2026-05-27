#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H
#include "types/data_types.h"
#define OCW2 0x20

struct Registers
{
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};
using isr_t = void (*)(Registers);

class InterruptHandler
{
public:
    InterruptHandler() = default;
    static isr_t getHandler(uint8_t num);
    static void registerHandlers(const uint8_t num, const isr_t handler);

private:
    static isr_t m_handlers[256];
};

extern "C" void isr_handler(Registers reg);
extern "C" void irq_handler(Registers reg);

#endif // INTERRUPT_HANDLER_H
