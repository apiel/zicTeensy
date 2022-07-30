#ifndef UI_TFT_H_
#define UI_TFT_H_

#include <Adafruit_GFX.h>
#include <SPI.h>

#include <Adafruit_SSD1331.h>

#include <Fonts/Picopixel.h>

#include "../lib/zicTracker/app.h"
#include "color.h"

// #include "fontData.h"
// #define LINE_SPACING 8

// #include "fontData2.h"
// #define LINE_SPACING 8

#include "fontData4.h"
#define LINE_SPACING 4

#define COLOR_SYMBOL '~'

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
    tft.setFont(&Picopixel);
    tft.fillScreen(UI_COLOR_BG);

    tft.setTextColor(UI_COLOR_FONT);
    tft.setCursor(0, 30);
    tft.print("Zic Tracker");
}

void draw_char(unsigned char chr, uint16_t x, uint16_t y, uint8_t size)
{
    x += FONT_H - 1;
    if (chr > 127) {
        chr -= 128;
    }
    const unsigned char* ptr = fontData + (chr - FONT_ASCII_START) * FONT_H;

    // for (int i = 0, ys = 0; i < FONT_W; i++, ptr++, ys += 1) {
    //     for (int col = FONT_H - FONT_W, xs = x - col; col < FONT_H; col++, xs -= 1) {
    //         if ((*ptr & 1 << col) && y + ys < SCREEN_H && xs < SCREEN_W) {
    //             tft.fillRect(xs * size, y + ys * size, size, size, fontColor);
    //         }
    //     }
    // }

    for (int i = 0; i < FONT_H; i++, ptr++) {
        for (int j = 7; j >= 0; --j) {
            if ((*ptr >> j) & 1) {
                tft.fillRect(x + (7 - j), y + i, size, size, fontColor);
            }

            // if ((*ptr & (1 << j)) && y + i < SCREEN_H && x + j < SCREEN_W) {
            //     tft.fillRect(x + j * size, y + i * size, size, size, fontColor);
            // }
        }
    }

    //     /*
    //  * code=65, hex=0x41, ascii="A"
    //  */
    // 0x00, /* 00000 */
    // 0x00, /* 00000 */
    // 0x60, /* 01100 */
    // 0x90, /* 10010 */
    // 0xF0, /* 11110 */
    // 0x90, /* 10010 */
    // 0x90, /* 10010 */
    // 0x00, /* 00000 */
}

uint8_t getRow(App_Display* display, uint16_t y, uint8_t size)
{
    return (y / ((FONT_H + LINE_SPACING) * size)) + display->startRow;
}

void resetColor(App_Display* display, uint16_t y, uint8_t size)
{
    uint8_t row = getRow(display, y, size);
    if (display->coloredHeader[0] == row || display->coloredHeader[1] == row) {
        fontColor = UI_COLOR_HEADER;
    } else {
        fontColor = UI_COLOR_FONT;
    }
}

void draw_string(App_Display* display, uint16_t x, uint16_t y, uint8_t size = 1)
{
    uint16_t orig_x = x;
    const char* text = display->text;
    resetColor(display, y, size);

    while (*text) {
        if (*text == '\n') {
            x = orig_x;
            y += (FONT_H + LINE_SPACING) * size;
            resetColor(display, y, size);
        } else {
            if (display->isColoredLabel()
                && x == orig_x + (display->coloredLabel * FONT_W)
                && getRow(display, y, size) >= display->coloredLabelFrom) {
                fontColor = UI_COLOR_LABEL;
            }
            if (*text == '>') {
                fontColor = UI_COLOR_PLAY;
            } else if (*text == '*') {
                fontColor = UI_COLOR_STAR;
            } else if (*text == ' ' || *text == '\n') {
                resetColor(display, y, size);
            }

            if (display->cursorLen && text >= display->cursorPos && text < display->cursorPos + display->cursorLen) {
                tft.fillRect(x * size - 2, y, FONT_W * size, FONT_H * size, UI_COLOR_CURSOR);
            }

            draw_char(*text, x, y, size);
            x += FONT_W; // * size;
        }
        text++;
    }
}

#endif