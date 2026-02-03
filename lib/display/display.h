#ifndef DISPLAY_H
#define DISPLAY_H
#include "types/data_types.h"
#include "../../arch/x86/VGA/vgadriver.h"
#include "log_level.h"

class Display
{
public:
  Display(LogLevel level, CHARS::CHAR_COLOR color);
  ~Display();
  Display& operator<<(const char& ch);
  Display& operator<<(const char* ch);
  Display& operator<<(int val);
  static void setThreshold(LogLevel level);
private:
  static LogLevel m_thresholdLevel;
  static uint8_t s_currentLine;

  LogLevel m_currentLevel;
  CHARS::CHAR_COLOR m_color;
  bool m_used = false;
  VGADriver &m_vga;
};

Display jDebug();
Display jInfo();
Display jWarning();
Display jError();

#endif // DISPLAY_H
