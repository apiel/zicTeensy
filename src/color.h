#ifndef UI_COLOR_H_
#define UI_COLOR_H_

uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

#define UI_COLOR_BG rgb565(0, 0, 0)
#define UI_COLOR_FONT rgb565(0xFF, 0xFF, 0xFF)
#define UI_COLOR_LABEL rgb565(150, 150, 150)
#define UI_COLOR_HEADER rgb565(100, 100, 100)
#define UI_COLOR_PLAY rgb565(122, 255, 0)
#define UI_COLOR_STAR rgb565(255, 255, 0)
#define UI_COLOR_CURSOR rgb565(0, 122, 255)

#endif