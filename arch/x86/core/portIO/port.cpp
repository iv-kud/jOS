#include "port.h"

void Port::write_port(uint16_t port, uint8_t value)
{
  write_byte(port, value);
}

uint8_t Port::read_port(uint16_t port)
{
  return read_byte(port);
}
