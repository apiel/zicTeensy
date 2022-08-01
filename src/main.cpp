#include <Arduino.h>

#include <Audio.h>

// #define FONT_FILE "./fonts/fontData8x8.h"

// #define SAMPLE_RATE 48000
// // #define CHANNELS 1
// #define CHANNELS 2 // to be fixed
// #define APP_AUDIO_FORMAT AUDIO_S16LSB
// #define APP_AUDIO_CHUNK 4096

#include "./app_file.h"
// #include <app.h>
#include "../lib/zicTracker/app.h"
#include "../lib/zicTracker/app_def.h"
#include "../lib/zicTracker/app_display.h"
#include "../lib/zicTracker/app_patterns.h"

#ifdef DISPLAY_SSD1331
#include "./displaySSD1331.h"
#else
#include "./displaySSD1306.h"
#endif

AudioOutputMQS audioOut;
// AudioOutputUSB audioOut;
// AudioOutputI2S audioOut;

AudioSynthWaveform waveform1; // xy=188,240
AudioEffectEnvelope envelope1; // xy=371,237
AudioConnection patchCordMixerKick(waveform1, audioOut);

UI_Display display;
App_Patterns patterns;
App app(&patterns, &display);

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Start teensy zic tracker");

    display.init();

    AudioMemory(25);

    waveform1.pulseWidth(0.5);
    // waveform1.pulseWidth(400);
    waveform1.begin(0.4, 220, WAVEFORM_PULSE);

    envelope1.attack(50);
    envelope1.decay(50);
    envelope1.release(250);

    app.start();
    app.render();

    // // analogReadResolution(12);
    // analogReadResolution(8);
    // analogReadAveraging(1);
}

uint8_t previousKeys = 0;

void loop()
{
    // put your main code here, to run repeatedly:
    // delay(1000);
    // Serial.println("Hello teensy zic tracker");

    // envelope1.noteOn();
    // delay(100);
    // envelope1.noteOff();
    // delay(100);


    // TOFO use external usb keyboard

    // uint8_t keys = 0;
    // uint8_t bit = 0;
    // uint8_t a7 = analogRead(7);
    // uint8_t a6 = analogRead(6);
    // // Serial.printf("A7 %d\n", a7);
    // // Serial.printf("A6 %d\n", a6);
    // if (a7 < 60) {
    //     bit = UI_KEY_UP;
    //     keys |= 1 << bit;
    // } else if (a7 > 200) {
    //     bit = UI_KEY_DOWN;
    //     keys |= 1 << bit;
    // }

    // if (a6 < 60) {
    //     bit = UI_KEY_LEFT;
    //     keys |= 1 << bit;
    // } else if (a6 > 200) {
    //     bit = UI_KEY_RIGHT;
    //     keys |= 1 << bit;
    // }

    // if (previousKeys != keys) {
    //     previousKeys = keys;
    //     app.handleUi(keys);
    // }

    delay(10);
}