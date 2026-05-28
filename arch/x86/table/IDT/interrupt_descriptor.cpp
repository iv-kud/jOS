#include "interrupt_descriptor.h"
#include "core/portIO/port.h"
#include "display/display.h"
#include "lib/data/memory/memory.h"

InterruptDescriptor::InterruptDescriptor()
{
    if (initTable()) {
        jInfo() << "[IDT] The table structure is correct";
        setTable();
    } else
        jError() << "[IDT] The table structure is incorrect";
}

bool InterruptDescriptor::initTable()
{
    memset(m_table, 0, sizeof(m_table));
    for (uint16_t i = 0; i < 256; ++i) {
        if (m_table[i].low_offset != 0 || m_table[i].segment_selector != 0 || m_table[i].zero != 0 || m_table[i].gate_type != 0 || m_table[i].high_offset != 0) {
            return false;
        }
    }

    for (uint8_t i = 0; i < 32; ++i) {
        setGate(i, (uint32_t) isrStubs[i], INTERRUPT_GATE);
        if (!checkGate(i, (uint32_t) isrStubs[i], INTERRUPT_GATE))
            return false;
    }
    picRemap();
    for (uint8_t i = 0; i < 16; ++i) {
        setGate(32 + i, (uint32_t) irqStubs[i], INTERRUPT_GATE);

        if (!checkGate(32 + i, (uint32_t) irqStubs[i], INTERRUPT_GATE))
            return false;
    }
    return true;
}

void InterruptDescriptor::setGate(const uint8_t offset, const uint32_t handler, const uint8_t type)
{
    m_table[offset].low_offset       = handler & 0xFFFF;
    m_table[offset].segment_selector = CODE_SEGMENT;
    m_table[offset].zero             = 0;
    m_table[offset].gate_type        = type;
    m_table[offset].high_offset      = (handler & 0xFFFF0000) >> 16;
}

bool InterruptDescriptor::checkGate(const uint8_t offset, const uint32_t handler, const uint8_t type) const
{
    return m_table[offset].low_offset == (handler & 0xFFFF) && m_table[offset].segment_selector == CODE_SEGMENT && m_table[offset].zero == 0 && m_table[offset].gate_type == type
           && m_table[offset].high_offset == (handler & 0xFFFF0000) >> 16;
}

void InterruptDescriptor::picRemap()
{
    Port::write_port(MASTER_PIC_COMMAND, ICW1);
    Port::write_port(SLAVE_PIC_COMMAND, ICW1);

    Port::write_port(MASTER_PIC_DATA, MASTER_ICW2);
    Port::write_port(SLAVE_PIC_DATA, SLAVE_ICW2);

    Port::write_port(MASTER_PIC_DATA, MASTER_ICW3);
    Port::write_port(SLAVE_PIC_DATA, SLAVE_ICW3);

    Port::write_port(MASTER_PIC_DATA, ICW4);
    Port::write_port(SLAVE_PIC_DATA, ICW4);

    Port::write_port(MASTER_PIC_DATA, OCW1);
    Port::write_port(SLAVE_PIC_DATA, OCW1);
}

void InterruptDescriptor::setTable()
{
    Table::Descriptor idtr;
    idtr.limit = 256 * sizeof(uint64_t) - 1;
    idtr.base  = (uint32_t) m_table;
    flush_idt(&idtr);
}
