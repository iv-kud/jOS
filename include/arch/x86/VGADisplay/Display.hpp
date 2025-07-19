#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <core/types/base.hpp>
#include <core/chars/chars.hpp>

class Display
{    
public:
    Display();
    void printChars(const char* ch);
    void printChars(const uint64_t ch);
    void newLine();
    void horizontalTab();
    void printChar(const char ch);
    ~Display() = default;
private:
    void intToString(const uint64_t val, char*);

    uint8_t intToChar(uint64_t &);
    void swap(char* buff, const uint32_t size);
private:
    uint16_t* video_memory;
    uint8_t color;
    uint8_t x;
    uint8_t y;
};

#endif