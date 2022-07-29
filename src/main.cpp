#include <Arduino.h>

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

#include "./tft.h"

AudioOutputMQS audioOut;

AudioSynthWaveform waveform1; // xy=188,240
AudioEffectEnvelope envelope1; // xy=371,237
AudioConnection patchCordMixerKick(waveform1, audioOut);

App_Patterns patterns;
App app(&patterns);

#define TEXT_SIZE 1

void render(App_Display* display)
{
    tft.fillScreen(UI_COLOR_BG);
    tft.setCursor(0, 0);
    // tft.setTextColor(UI_COLOR_FONT);
    // tft.print(display->text);
    draw_string(display, 2, TEXT_SIZE * FONT_H, TEXT_SIZE);
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Start teensy zic tracker");

    init_tft();

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