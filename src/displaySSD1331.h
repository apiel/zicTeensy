#ifndef UI_DISPLAY_H_
#define UI_DISPLAY_H_

#include <Adafruit_GFX.h>
#include <SPI.h>

#include <Adafruit_SSD1331.h>

#include "../lib/zicTracker/app_display.h"

#define sclk 32 // 9 -> SCL
#define mosi 26 // 11 -> SDA
#define rst 27 // 13 -> RES
#define dc 31 // 22 -> DC
#define cs 30 // 23 -> CS

// #define sclk 9 //-> SCL
// #define mosi 11 //-> SDA
// #define rst 13 //-> RES
// #define dc 22 //-> DC
// #define cs 23 //-> CS

#define SCREEN_W 96
#define SCREEN_H 64

Adafruit_SSD1331 tft = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);

class UI_Display : public App_Display {
protected:
    uint16_t fontColor = 0;

    void drawPixel(int16_t x, int16_t y)
    {
        if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H) {
            return;
        }

        tft.drawPixel(x, y, fontColor);
    }

    void drawCursor(int16_t x, int16_t y)
    {
        tft.fillRect(x, y, FONT_W, FONT_H, rgb565(UI_COLOR_CURSOR));
    }

    uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b)
    {
        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }

    void setColor(uint8_t r, uint8_t g, uint8_t b)
    {
        fontColor = rgb565(r, g, b);
    }

public:
    void init()
    {
        tft.begin();
        clearScreen();

        setColor(UI_COLOR_FONT);
        tft.setTextColor(fontColor);
        tft.setCursor(0, 10);
        tft.print("Zic Tracker");
    }

    void clearScreen()
    {
        tft.fillScreen(rgb565(UI_COLOR_BG));
    }
};

#endif