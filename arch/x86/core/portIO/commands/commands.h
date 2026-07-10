#ifndef COMMANDS_H
#define COMMANDS_H
namespace Command {
enum class CRTC {
    INDEX_PORT = 0x3D4,
    DATA_PORT  = 0x3D5,
};

enum class PIC {
    /*Master and Slave Pic`s*/
    MASTER_COMMAND = 0x20,
    SLAVE_COMMAND  = 0xA0,
    MASTER_DATA    = 0x21,
    SLAVE_DATA     = 0xA1,
    /*ICW*/
    ICW_1        = 0x11,
    ICW_2_MASTER = 0x20,
    ICW_2_SLAVE  = 0x28,
    ICW_3_MASTER = 0x04,
    ICW_3_SLAVE  = 0x02,
    ICW_4        = 0x01,
    /*OCW*/
    OCW_1 = 0x00,
    /*End of interrupt*/
    EOI = 0x20,
};
} // namespace Command
#endif // COMMANDS_H
