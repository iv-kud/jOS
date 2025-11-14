#include "../arch/x86/VGA/vgadisplay.h"

extern "C" void kernel_main() {
  const char* hello = "Hello JustOS!";
  VGADisplay display;
  for (int i = 0; hello[i] != '\0'; i++) {
      display.printChar(hello[i]);
    }
  while(true);
}
