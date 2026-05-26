#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H
#include "types/data_types.h"

struct Registers
{
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

class InterruptHandler
{
public:
    InterruptHandler();
};

extern "C" void isr_handler(Registers reg);
extern "C" void irq_handler(Registers reg);

#endif // INTERRUPT_HANDLER_H
