#ifndef VGADISPLAY_H
#define VGADISPLAY_H

#include "types/data_types.h"
#include "chars/chars_code.h"
#include "chars/vga_modecolor.h"

class VGADisplay
{
public:
  VGADisplay ();
  uint8_t getX();
  uint8_t getY();
  void setX(uint8_t newX);
  void setY(uint8_t newY);
  void printChar(const char ch);
private:
  void newLine();
  void horizontalTab();
  uint8_t nextTabPosition(const uint8_t cur_pos) const;
private:
  const uint8_t m_width = 80;
  const uint8_t m_height = 25;
  uint8_t m_x,m_y;
  uint16_t* m_video_memory;
  chars::char_color m_color;
};

#endif // VGADISPLAY_H
