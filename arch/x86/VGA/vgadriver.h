#ifndef VGADRIVER_H
#define VGADRIVER_H

#include "types/data_types.h"
#include "chars/chars_code.h"
#include "chars/vga_modecolor.h"

class VGADriver
{
public:
  static VGADriver& instance();

  uint8_t getX() const;
  uint8_t getY() const;
  void setX(const uint8_t newX);
  void setY(const uint8_t newY);
  void setColor(const CHARS::CHAR_COLOR color);
  uint8_t getBuffWidth() const;
  uint8_t getBuffHeight() const;
  void print(const char ch);
  void newLine();

  VGADriver(const VGADriver&) = delete;
  VGADriver& operator=(const VGADriver&) = delete;

private:
  VGADriver();
  VGADriver(const CHARS::CHAR_COLOR color);
  uint16_t cursorPosition() const;
  void moveCursor();
  void horizontalTab();
  uint8_t nextTabPosition(const uint8_t cur_pos) const;

private:
  const uint8_t m_width = 80;
  const uint8_t m_height = 25;
  uint8_t m_x, m_y;
  uint16_t* m_video_memory;
  CHARS::CHAR_COLOR m_color;
};

#endif // VGADRIVER_H
