#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <SPI.h>

#include <Adafruit_SSD1331.h>
#include <SPI.h>

// #include <Audio.h>

// AudioOutputMQS audioOut;

// AudioSynthWaveform waveform1; // xy=188,240
// AudioEffectEnvelope envelope1; // xy=371,237
// AudioConnection patchCordMixerKick(waveform1, audioOut);

#define sclk 9
#define mosi 11
#define rst 13
#define dc 22 
#define cs 23

#define BLACK 0x0000
#define BLUE 0x001F

Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Start teensy zic tracker");

    display.begin();
    display.fillScreen(BLACK);

    display.setTextColor(BLUE);
    display.setCursor(0, 0);
    display.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa");

    // AudioMemory(25);

    // waveform1.pulseWidth(0.5);
    // waveform1.begin(0.4, 220, WAVEFORM_PULSE);

    // envelope1.attack(50);
    // envelope1.decay(50);
    // envelope1.release(250);
}

void loop()
{
    // put your main code here, to run repeatedly:
    // delay(1000);
    // Serial.println("Hello teensy zic tracker");

    // waveform1.pulseWidth(400);
    // envelope1.noteOn();
    // delay(800);
    // envelope1.noteOff();
    // delay(600);
}