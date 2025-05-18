#include <arch/x86/VGADisplay/Display.hpp>

extern "C" void kernel_main() {
    Display display;

    display.printChar('H');
    display.printChar('e');
    display.printChar('l');
    display.printChar('l');
    display.printChar('o');
    display.printChar(' ');
    display.printChar('j');
    display.printChar('O');
    display.printChar('S');
    display.printChar('\n');
    display.printChars("This is just string");
    while(true);
}