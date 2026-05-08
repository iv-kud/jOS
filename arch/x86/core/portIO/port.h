#ifndef PORT_H
#define PORT_H
#include "types/data_types.h"

class Port
{
public:
    static void write_port(uint16_t port, uint8_t value);
    static uint8_t read_port(uint16_t port);
};

extern "C" void write_byte(uint16_t port, uint8_t data);
extern "C" char read_byte(uint16_t port);
#endif // PORT_H
