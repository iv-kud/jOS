#ifndef DISPLAY_H
#define DISPLAY_H
#include "VGA/vgadriver.h"
#include "display_types.h"
#include "types/data_types.h"

class Display
{
public:
    Display(LogLevel level, CHARS::CHAR_COLOR color);
    ~Display();
    Display &operator<<(const char &ch);
    Display &operator<<(const char *ch);
    Display &operator<<(int val);
    Display &operator<<(uint64_t val);
    Display &operator<<(NumberBase base);
    static void setThreshold(LogLevel level);

private:
    void printHex(uint64_t val);
    void printDec(uint64_t val);

    static LogLevel m_thresholdLevel;
    LogLevel m_currentLevel;
    CHARS::CHAR_COLOR m_color;
    bool m_used = false;
    VGADriver &m_vga;
    NumberBase m_base;
};

Display jDebug();
Display jInfo();
Display jWarning();
Display jError();

#endif // DISPLAY_H
