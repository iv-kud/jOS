#include <arch/x86/VGADisplay/Display.hpp>

Display::Display() {
    x = 0;
    y = 0;
    video_memory = (uint16_t*)0xB8000;
    color = 0x0A;
}

void Display::newLine() {
    x = 0;
    y++;
}

void Display::horizontalTab() {
    const uint8_t TAB_WIDTH = 8;
    x = (x / TAB_WIDTH + 1) * TAB_WIDTH;
    if (x > 80)
        newLine();    
}

void Display::printChar(const char ch) {
    switch (ch)
    {
    case chars::escapeChars::N_LINE:newLine();break;
    case chars::escapeChars::H_TAB: horizontalTab();break;
    default:
        uint16_t *charPos = (uint16_t*)video_memory + (y * 80 + x);
        *charPos = (color << 8) | ch;
        x++;
    break;
    }
}

void Display::intToString(const uint32_t val,char* buff) {
    uint32_t number = val;
    uint32_t i = 0;
    while (number != 0)
        buff[i++] = intToChar(number);
    
    buff[i] = '\0';
    swap(buff, i - 1);
}

uint32_t Display::intToChar(uint32_t &number)
{
    uint32_t numberChar = (number % 10) + '0';
    number /= 10;
    return numberChar;
}

void Display::printChars(const uint32_t ch)
{
    char valueStr[32];
    intToString(ch,valueStr);
    printChars(valueStr);
}

void Display::swap(char *buff, const uint32_t size) {
    for (uint32_t i = 0; i < size/2; i++)
    {
        int tmp =  buff[i];
        buff[i] = buff[size - i];
        buff[size - i] = tmp;
    }    
}


void Display::printChars(const char *ch)
{
    for (uint8_t i = 0; ch[i] != chars::escapeChars::END_LINE; i++)
        printChar(ch[i]);
}

