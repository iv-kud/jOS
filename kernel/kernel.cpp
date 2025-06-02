#include <arch/x86/VGADisplay/Display.hpp>

extern "C" void kernel_main() {
    Display display;
    display.printChars("Hello JustOS!\n");
    display.printChars("This\t|\tis\t|\tjust\t|\tstring\n");
    display.printChars(228 + 2);
    display.printChar('\n');
    display.printChars(1234567890);
    while(true);
}