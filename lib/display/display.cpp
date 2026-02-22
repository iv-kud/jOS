#include "display.h"
LogLevel Display::m_thresholdLevel = LogLevel::Debug;
uint8_t Display::s_currentLine = 0;

Display::Display(LogLevel level, CHARS::CHAR_COLOR color)
    : m_currentLevel(level)
    , m_color(color)
    , m_vga(VGADriver::instance())
{
  m_vga.setX(0);
  m_vga.setY(s_currentLine);
  m_vga.setColor(m_color);
}

Display::~Display() {
  if (m_used) {
      s_currentLine++;
      if (s_currentLine >= m_vga.getBuffHeight()) {
          s_currentLine = 24;
        }
    }
}

void Display::setThreshold(LogLevel level)
{
  if (m_thresholdLevel != level) {
      m_thresholdLevel = level;
    }
}

Display &Display::operator<<(const char &ch)
{
  if (m_currentLevel >= m_thresholdLevel) {
      m_used = true;
      m_vga.print(ch);
    }
  return *this;
}

Display &Display::operator<<(const char *ch)
{
  for (int var = 0; ch[var] != '\0'; ++var) {
      *this << ch[var];
  }
  return *this;
}

Display &Display::operator<<(int val)
{
  if (val < 0) {
    *this << '-';
    val = -val;
  }
  *this << static_cast<uint64_t>(val);
}

Display &Display::operator<<(uint64_t val)
{
  if(val == 0)
    return *this;
  uint64_t next = val / 10;
  uint64_t digit = val % 10;

  if(next != 0)
    *this << next;
  *this << static_cast<char>('0' + digit);
  return *this;
}

Display jDebug() {
  return Display(LogLevel::Debug, CHARS::CHAR_COLOR::COLOR_DARK_GRAY);
}

Display jInfo() {
  return Display(LogLevel::Info, CHARS::CHAR_COLOR::COLOR_WHITE);
}

Display jWarning() {
  return Display(LogLevel::Warning, CHARS::CHAR_COLOR::COLOR_YELLOW);
}

Display jError() {
  return Display(LogLevel::Error, CHARS::CHAR_COLOR::COLOR_RED);
}
