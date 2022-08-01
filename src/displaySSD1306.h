#ifndef UI_DISPLAY_H_
#define UI_DISPLAY_H_

#include <Adafruit_GFX.h>
#include <SPI.h>

#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "../lib/zicTracker/app_display.h"

#define SCREEN_W 128 // OLED display width, in pixels
#define SCREEN_H 64 // OLED display height, in pixels

#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 tft(SCREEN_W, SCREEN_H, &Wire, OLED_RESET);

#define DRAW_PIXEL_VERSION 1

#ifndef DRAW_PIXEL_VERSION
#define FONT_DEFAULT_H 8
#define FONT_DEFAULT_W 6
#endif

class UI_Display : public App_Display {
protected:
    void drawPixel(int16_t x, int16_t y)
    {
#ifdef DRAW_PIXEL_VERSION
        if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H) {
            return;
        }

        tft.drawPixel(x, y, tft.getPixel(x, y) ? BLACK : WHITE);
#endif
    }

    void drawCursor(int16_t x, int16_t y)
    {
#ifdef DRAW_PIXEL_VERSION
        tft.fillRect(x, y, FONT_W, FONT_H, WHITE);
#endif
    }

    void setColor(uint8_t r, uint8_t g, uint8_t b)
    {
        // There is no color on SSD1306
    }

public:
    void init()
    {
        if (!tft.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
            Serial.println(F("SSD1306 allocation failed"));
            for (;;)
                ; // Don't proceed, loop forever
        }

        tft.clearDisplay();
        tft.setTextColor(INVERSE);
        tft.setTextSize(1);
        tft.setCursor(0, 10);
        tft.print("Zic Tracker");
        tft.display();
    }

    void clearScreen()
    {
        tft.clearDisplay();
    }

    void drawText() override
    {
#ifdef DRAW_PIXEL_VERSION
        App_Display::drawText();
#else
        uint16_t x = 0;
        uint16_t y = 0;
        tft.setCursor(x, y);
        const char* txt = text;
        while (*txt) {
            if (*txt == '\n') {
                x = 0;
                y += (FONT_DEFAULT_H);
            } else {
                if (cursorLen && txt >= cursorPos && txt < cursorPos + cursorLen) {
                    tft.fillRect(x - 2, y - 1, FONT_DEFAULT_W + 2, FONT_DEFAULT_H + 1, WHITE);
                }
                x += FONT_DEFAULT_W;
            }
            txt++;
        }
        tft.print(text);
#endif
        tft.display();
    }
};

#endif