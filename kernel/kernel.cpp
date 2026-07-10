#include "arch/x86/core/portIO/port.h"
#include "drivers/keyboarddriver.h"
#include "drivers/pitdriver.h"
#include "portIO/commands/commands.h"
#include "table/GDT/global_descriptor.h"
#include "table/IDT/interrupt_descriptor.h"

extern "C" void main()
{
    GlobalDescriptor gdt;
    InterruptDescriptor idt;

    static KeyboardDriver keyboard;
    static PITDriver pit;
    keyboard.init();
    pit.init();
    Port::write_port(static_cast<uint16_t>(Command::PIC::MASTER_DATA), 0xFC);
    Port::write_port(static_cast<uint16_t>(Command::PIC::SLAVE_DATA), 0xFF);

    asm volatile("sti");

    while (true)
        ;
}
