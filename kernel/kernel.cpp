#include "../lib/display/display.h"

extern "C" void main() {
  jDebug() << "Debug";                   // Серый
  jInfo() << "Information";              // Зеленый
  jWarning() << "Warning";               // Желтый
  jError() << "Error!";                  // Красный
  while(true);
}
