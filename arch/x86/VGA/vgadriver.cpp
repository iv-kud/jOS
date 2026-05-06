#include "vgadriver.h"
#include "portIO/port.h"

VGADriver::VGADriver ()
    : m_x(0)
      , m_y(0)
      , m_video_memory((uint16_t*)0xb8000)
      , m_color(CHARS::CHAR_COLOR::COLOR_WHITE)
{}

VGADriver::VGADriver(const CHARS::CHAR_COLOR color)
    : m_x(0)
      , m_y(0)
      , m_video_memory((uint16_t*)0xb8000)
      , m_color(color)
{}

void VGADriver::scroll()
{
  for (int i = 0; i < m_width * (m_height -1); ++i)
    m_video_memory[i] = m_video_memory[i + m_width];

  uint16_t blank = ((uint8_t)m_color << 8) | ' ';

  for (int i = m_width * (m_height - 1); i < m_height * m_width; ++i)
    m_video_memory[i] = blank;

  m_y = m_height - 1;
}

uint16_t VGADriver::cursorPosition() const
{
  return m_y * m_width + m_x;
}

void VGADriver::moveCursor()
{
  Port::write_port(0x3D4, 14);
  Port::write_port(0x3D5, cursorPosition() >> 8);
  Port::write_port(0x3D4, 15);
  Port::write_port(0x3D5, cursorPosition());
}

VGADriver &VGADriver::instance()
{
  static VGADriver driver;
  return driver;
}

uint8_t VGADriver::getX() const
{
  return m_x;
}

uint8_t VGADriver::getY() const
{
  return m_y;
}

void VGADriver::setX(const uint8_t newX)
{
  if (m_x != newX)
    m_x = newX;
}

void VGADriver::setY(const uint8_t newY)
{
  if (m_y != newY)
    m_y = newY;
}

void VGADriver::setColor(const CHARS::CHAR_COLOR color)
{
  if (m_color != color)
    m_color = color;
}

uint8_t VGADriver::getBuffWidth() const
{
  return m_width;
}

uint8_t VGADriver::getBuffHeight() const
{
  return m_height;
}

void VGADriver::newLine()
{
  m_x = 0;
  if (m_y < m_height - 1)
    ++m_y;
  else
    scroll();
}

void VGADriver::horizontalTab()
{
  m_x = nextTabPosition(m_x);
  if(m_x >= m_width)
    newLine();
}

uint8_t VGADriver::nextTabPosition(const uint8_t cur_pos) const
{
  uint8_t tab_size = 4;
  return cur_pos + tab_size - (cur_pos % tab_size);
}

void VGADriver::print(const char ch)
{
  switch (ch)
  {
  case (uint8_t)CHARS::ESCAPE_CHARS::N_LINE:
    newLine();
    break;

  case (uint8_t)CHARS::ESCAPE_CHARS::H_TAB:
    horizontalTab();
    break;

  default:
    uint16_t *charPos = m_video_memory + cursorPosition();
    *charPos = ((uint8_t)m_color << (uint8_t)8) | ch;
    ++m_x;
    break;
  }
}

