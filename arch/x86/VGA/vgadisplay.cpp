#include "vgadisplay.h"

VGADisplay::VGADisplay () {
  m_x = 0;
  m_y = 0;
  m_video_memory = (uint16_t *)0xB8000;
  m_color = chars::char_color::COLOR_WHITE;
}

uint8_t VGADisplay::getX()
{
  return m_x;
}

void VGADisplay::newLine()
{
  m_x = 0;
  ++m_y;
}

void VGADisplay::horizontalTab()
{
  m_x = nextTabPosition(m_x);
  if(m_x >= m_width)
    newLine();
}

void VGADisplay::printChar(const char ch)
{
  switch (ch)
  {
  case (uint8_t)chars::escapeChars::N_LINE:newLine();break;
  case (uint8_t)chars::escapeChars::H_TAB: horizontalTab();break;
  default:
    uint16_t *charPos = m_video_memory + (m_y * m_width  + m_x);
    *charPos = ((uint8_t)m_color << (uint8_t)8) | ch;
    m_x++;
    break;
  }
}

uint8_t VGADisplay::nextTabPosition(const uint8_t cur_pos) const
{
  uint8_t tab_size = 4;
  return cur_pos + tab_size - (cur_pos % tab_size);
}
