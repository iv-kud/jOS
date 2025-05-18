#include <arch/x86/VGADisplay/Display.hpp>

Display::Display() {
    x = 0;
    y = 0;
    video_memory = (uint16_t*)0xB8000;
    color = 0x0A;
}

void Display::printChar(const char ch) {
    if (ch=='\n')
    {
        x = 0;
        y++;
        return;
    }
    
    uint16_t *setChar = (uint16_t*)video_memory + (y * 80 + x);
    *setChar = (color << 8) | ch;
    x++;
}

void Display::printChars(const char *ch)
{
    for (uint8_t i = 0; ch[i] != '\0'; i++)
        printChar(ch[i]);   
}
