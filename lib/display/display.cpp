#include "display.h"

LogLevel Display::m_thresholdLevel = LogLevel::Debug;

Display::Display(LogLevel level, CHARS::CHAR_COLOR color)
    : m_currentLevel(level)
    , m_color(color)
    , m_base(NumberBase::Dex)
    , m_vga(VGADriver::instance())
{
    m_vga.setX(0);
    m_vga.setY(m_vga.getY());
    m_vga.setColor(m_color);
}

Display::~Display()
{
    if (m_used) {
        m_vga.newLine();
        m_vga.moveCursor();
    }
}

void Display::setThreshold(LogLevel level)
{
    if (m_thresholdLevel == level)
        return;

    m_thresholdLevel = level;
}

void Display::printHex(uint64_t val)
{
    *this << "0x";

    if (val == 0) {
        *this << '0';
        return;
    }

    const char hexDigids[] = "0123456789ABCDEF";
    char buffer[16]        = {};
    int i                  = 0;

    while (val > 0) {
        int remainder = val % 16;
        buffer[i++]   = hexDigids[remainder];
        val           = val / 16;
    }

    while (i > 0) {
        *this << buffer[--i];
    }
}

void Display::printDec(uint64_t val)
{
    if (val == 0) {
        *this << '0';
        return;
    }

    char buffer[20] = {};
    int i           = 0;
    while (val > 0) {
        uint64_t digit = val % 10;
        buffer[i++]    = '0' + digit;
        val            = val / 10;
    }

    while (i > 0) {
        *this << buffer[--i];
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
    for (int var = 0; ch[var] != '\0'; ++var)
        *this << ch[var];

    return *this;
}

Display &Display::operator<<(int val)
{
    if (val < 0) {
        *this << '-';
        val = -val;
    }
    *this << static_cast<uint64_t>(val);
    return *this;
}

Display &Display::operator<<(uint64_t val)
{
    if (m_base == NumberBase::Hex) {
        printHex(val);
    } else {
        printDec(val);
    }

    return *this;
}

Display &Display::operator<<(NumberBase base)
{
    if (m_base != base)
        m_base = base;

    return *this;
}

Display jDebug()
{
    return Display(LogLevel::Debug, CHARS::CHAR_COLOR::COLOR_DARK_GRAY);
}

Display jInfo()
{
    return Display(LogLevel::Info, CHARS::CHAR_COLOR::COLOR_WHITE);
}

Display jWarning()
{
    return Display(LogLevel::Warning, CHARS::CHAR_COLOR::COLOR_YELLOW);
}

Display jError()
{
    return Display(LogLevel::Error, CHARS::CHAR_COLOR::COLOR_RED);
}
