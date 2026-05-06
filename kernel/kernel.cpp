#include "display/display.h"
#include "table/GDT/global_descriptor.h"

extern "C" void main() {
  jInfo() << "Welcome to jOS: " << 0 <<'.'<< 0 <<'.' << 1 ;
  GlobalDescriptor gdt;

  while(true);
}
