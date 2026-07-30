#ifndef COMMANDS_H
#define COMMANDS_H
#include "types/data_types.h"

namespace Command::CRTC {
enum class Port : uint16_t {
    INDEX = 0x3D4,
    DATA  = 0x3D5,
};
} // namespace Command::CRTC

namespace Command::PIC {
enum class Port {
    /*Master and Slave Pic`s*/
    MASTER_COMMAND = 0x20,
    SLAVE_COMMAND  = 0xA0,
    MASTER_DATA    = 0x21,
    SLAVE_DATA     = 0xA1,
};

enum class Value {
    /*ICW*/
    ICW_1        = 0x11,
    ICW_2_MASTER = 0x20,
    ICW_2_SLAVE  = 0x28,
    ICW_3_MASTER = 0x04,
    ICW_3_SLAVE  = 0x02,
    ICW_4        = 0x01,
    /*OCW*/
    OCW_1_UNMASK_ALL = 0x00,
    OCW_1_MASK_ALL   = 0xFF,
    /*End of interrupt*/
    EOI = 0x20,
};
} // namespace Command::PIC
#endif // COMMANDS_H
