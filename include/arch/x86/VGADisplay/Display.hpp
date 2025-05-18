#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <core/types/base.hpp>

class Display
{    
public:
    Display();
    void printChar(const char ch);
    void printChars(const char* ch);
    ~Display() = default;

private:
    uint16_t* video_memory;
    uint8_t color;
    uint8_t x;
    uint8_t y;
};

#endif