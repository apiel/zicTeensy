#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <SPI.h>

#include <Adafruit_SSD1331.h>
#include <SPI.h>

#include <Audio.h>

#define SAMPLE_RATE 48000
// #define CHANNELS 1
#define CHANNELS 2 // to be fixed
#define APP_AUDIO_FORMAT AUDIO_S16LSB
#define APP_AUDIO_CHUNK 4096

#include "./app_file.h"
// #include <app.h>
#include "../lib/zicTracker/app.h"
#include "../lib/zicTracker/app_def.h"
#include "../lib/zicTracker/app_display.h"
#include "../lib/zicTracker/app_patterns.h"

AudioOutputMQS audioOut;

AudioSynthWaveform waveform1; // xy=188,240
AudioEffectEnvelope envelope1; // xy=371,237
AudioConnection patchCordMixerKick(waveform1, audioOut);

#define sclk 9
#define mosi 11
#define rst 13
#define dc 22 
#define cs 23

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

Adafruit_SSD1331 d = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);

App_Patterns patterns;
App app(&patterns);

void render(App_Display* display)
{
    d.fillScreen(UI_COLOR_BG);
    d.setTextColor(UI_COLOR_FONT);
    d.setCursor(0, 0);
    d.print(display->text);
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Start teensy zic tracker");

    d.begin();
    d.fillScreen(UI_COLOR_BG);

    d.setTextColor(UI_COLOR_FONT);
    d.setCursor(0, 0);
    d.print("Zic Tracker");

    AudioMemory(25);

    waveform1.pulseWidth(0.5);
    waveform1.begin(0.4, 220, WAVEFORM_PULSE);

    envelope1.attack(50);
    envelope1.decay(50);
    envelope1.release(250);

    app.start();
    render(app.render());
}

void loop()
{
    // put your main code here, to run repeatedly:
    // delay(1000);
    // Serial.println("Hello teensy zic tracker");

    waveform1.pulseWidth(400);
    envelope1.noteOn();
    delay(800);
    envelope1.noteOff();
    delay(600);
}