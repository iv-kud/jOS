#include "arch/x86/core/portIO/port.h"
#include "display/display.h"
#include "drivers/keyboarddriver.h"
#include "table/GDT/global_descriptor.h"
#include "table/IDT/interrupt_descriptor.h"

extern "C" void main()
{
    GlobalDescriptor gdt;
    InterruptDescriptor idt;

    static KeyboardDriver keyboard;
    keyboard.init();

    Port::write_port(0x21, 0xFD);
    Port::write_port(0xA1, 0xFF);

    asm volatile("sti");

    while (true)
        ;
}
