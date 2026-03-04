#include "global_descriptor.h"
#include "display/display.h"
#include "data/bit_ops/bitset.hpp"

GlobalDescriptor::GlobalDescriptor () {
  if (initTable()) {
    jInfo() << "The table structure is correct";
    setTable();
  }
  else {
    jError() << "the table structure is incorrect";
  }
}

bool GlobalDescriptor::initTable()
{
  bitset<64> nullSegment;
  reinterpret_cast<uint64_t&>(m_table[0]) = nullSegment.data();
  reinterpret_cast<uint64_t&>(m_table[1]) = kernelCodeSegment();
  reinterpret_cast<uint64_t&>(m_table[2]) = kernelDataSegment();
  reinterpret_cast<uint64_t&>(m_table[3]) = userCodeSegment();
  reinterpret_cast<uint64_t&>(m_table[4]) = userdataSegment();

  constexpr uint64_t expected[5] = {
    0x0000000000000000, // null
    0x00CF9A000000FFFF, // kernel Code
    0x00CF92000000FFFF, // kernel Data
    0x00CFFA000000FFFF, // user Code
    0x00CFF2000000FFFF  // user Data
  };

  for (int i = 0; i < 5; ++i) {
      if (reinterpret_cast<uint64_t&>(m_table[i]) != expected[i]) {
          return false;
      }
    }
  return true;
}

/*
Base = 0
Limit = 0xFFFFF
Access Byte = 0x9A
Flags = 0xC
 */
uint64_t GlobalDescriptor::kernelCodeSegment() const
{
  bitset<64> codeSegment;
  /*Base*/
  codeSegment.setRange(16, 39, 0);
  codeSegment.setRange(56, 63, 0);
  /*Limit*/
  codeSegment.setRange(0, 15, 0xFFFF);
  codeSegment.setRange(48, 51, 0xF);
  /*Access Byte*/
  codeSegment.setRange(40, 47, 0x9A);
  /*Flags*/
  codeSegment.setRange(52, 55, 0xC);

  return codeSegment.data();
}
/*
Base = 0
Limit = 0xFFFFF
Access Byte = 0x92
Flags = 0xC
*/
uint64_t GlobalDescriptor::kernelDataSegment() const
{
  bitset<64> dataSegment;
  /*Base*/
  dataSegment.setRange(16, 39, 0);
  dataSegment.setRange(56, 63, 0);
  /*Limit*/
  dataSegment.setRange(0, 15, 0xFFFF);
  dataSegment.setRange(48, 51, 0xF);
  /*Access Byte*/
  dataSegment.setRange(40, 47, 0x92);
  /*Flags*/
  dataSegment.setRange(52, 55, 0xC);

  return dataSegment.data();
}
/*
Base = 0
Limit = 0xFFFFF
Access Byte = 0xFA
Flags = 0xC
*/
uint64_t GlobalDescriptor::userCodeSegment() const
{
  bitset<64> codeSegment;
  /*Base*/
  codeSegment.setRange(16, 39, 0);
  codeSegment.setRange(56, 63, 0);
  /*Limit*/
  codeSegment.setRange(0, 15, 0xFFFF);
  codeSegment.setRange(48, 51, 0xF);
  /*Access Byte*/
  codeSegment.setRange(40, 47, 0xFA);
  /*Flags*/
  codeSegment.setRange(52, 55, 0xC);

  return codeSegment.data();
}
/*
Base = 0
Limit = 0xFFFFF
Access Byte = 0xF2
Flags = 0xC
 */
uint64_t GlobalDescriptor::userdataSegment() const
{
  bitset<64> dataSegment;
  /*Base*/
  dataSegment.setRange(16, 39, 0);
  dataSegment.setRange(56, 63, 0);
  /*Limit*/
  dataSegment.setRange(0, 15, 0xFFFF);
  dataSegment.setRange(48, 51, 0xF);
  /*Access Byte*/
  dataSegment.setRange(40, 47, 0xF2);
  /*Flags*/
  dataSegment.setRange(52, 55, 0xC);

  return dataSegment.data();
}
/*
Base = &TSS
Limit = sizeof(TSS)-1
Access Byte = 0x89
Flags = 0x0
*/
uint64_t GlobalDescriptor::taskStateSegment() const
{
  ///TODO: Implement the TSS structure
  return 0;
}

void GlobalDescriptor::setTable()
{
  Table::Descriptor gdtr;
  gdtr.limit = 5 * sizeof(uint64_t) - 1;
  gdtr.base = (uint32_t)m_table;

  flush_gdt(&gdtr);
}
