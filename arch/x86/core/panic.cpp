#include "panic.h"
#include "display/display.h"

void panic(const char *message)
{
  asm volatile("cli");

  jError() << "Kernel Panic: " << message;
  while (true)
    asm volatile("hlt");
}
