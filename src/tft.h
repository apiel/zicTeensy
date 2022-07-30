#ifndef UI_TFT_H_
#define UI_TFT_H_

#include <Adafruit_GFX.h>
#include <SPI.h>

#include <Adafruit_SSD1331.h>

#include "../lib/zicTracker/app.h"
#include "color.h"

// #include "fontData.h"
// #define LINE_SPACING 8

// #include "fontData2.h"
// #define LINE_SPACING 8

#include "fontData4.h"
#define LINE_SPACING 2

uint16_t fontColor = 0;

#define sclk 9
#define mosi 11
#define rst 13
#define dc 22
#define cs 23

#define SCREEN_W 96
#define SCREEN_H 64

Adafruit_SSD1331 tft = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);

void init_tft()
{
    tft.begin();
    tft.fillScreen(UI_COLOR_BG);

    tft.setTextColor(UI_COLOR_FONT);
    tft.setCursor(0, 10);
    tft.print("Zic Tracker");
}

void draw_pixel(int16_t x, int16_t y, uint16_t color)
{
    if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H) {
        return;
    }

    tft.drawPixel(x, y, color);
}

// TODO use this version in SDL
void draw_char(unsigned char chr, uint16_t x, uint16_t y)
{
    const unsigned char* ptr = fontData + (chr - FONT_ASCII_START) * FONT_H;

    for (int i = 0; i < FONT_H; i++, ptr++) {
        for (int j = 8 - FONT_W; j < 8; j++) { // Support only 8 bits font
            if ((*ptr >> j) & 1) {
                draw_pixel(x + (8 - j), y + i, fontColor);
            }
        }
    }
}

uint8_t getRow(App_Display* display, uint16_t y)
{
    return (y / ((FONT_H + LINE_SPACING))) + display->startRow;
}

void resetColor(App_Display* display, uint16_t y)
{
    uint8_t row = getRow(display, y);
    if (display->coloredHeader[0] == row || display->coloredHeader[1] == row) {
        fontColor = UI_COLOR_HEADER;
    } else {
        fontColor = UI_COLOR_FONT;
    }
}

void draw_string(App_Display* display, uint16_t x, uint16_t y)
{
    uint16_t orig_x = x;
    const char* text = display->text;
    resetColor(display, y);

    while (*text) {
        if (*text == '\n') {
            x = orig_x;
            y += (FONT_H + LINE_SPACING);
            resetColor(display, y);
        } else {
            if (display->isColoredLabel()
                && x == orig_x + (display->coloredLabel * FONT_W)
                && getRow(display, y) >= display->coloredLabelFrom) {
                fontColor = UI_COLOR_LABEL;
            }
            if (*text == '>') {
                fontColor = UI_COLOR_PLAY;
            } else if (*text == '*') {
                fontColor = UI_COLOR_STAR;
            } else if (*text == ' ' || *text == '\n') {
                resetColor(display, y);
            }

// FIXME
            // if (display->cursorLen && text >= display->cursorPos && text < display->cursorPos + display->cursorLen) {
            //     tft.fillRect(x - 2, y, FONT_W, FONT_H, UI_COLOR_CURSOR);
            // }

            draw_char(*text, x, y);
            x += FONT_W; //;
        }
        text++;
    }
}

#endif