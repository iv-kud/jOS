#include "../lib/display/display.h"

extern "C" void kernel_main() {
  jDebug() << "Debug";                   // Серый
  jInfo() << "Information";              // Зеленый
  jWarning() << "Warning";               // Желтый
  jError() << "Error!";                  // Красный
  while(true);
}
