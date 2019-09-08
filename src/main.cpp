#include <Arduino.h>
#include <Wire.h>

#include <FastLED.h>
#include <LiquidCrystal_PCF8574.h>


const int LED_COUNT = 84;
CRGB leds[LED_COUNT];

void setup() {
  Serial.begin(38400);
  
  FastLED.addLeds<WS2812B, 2, BRG>(leds, LED_COUNT);
}

void loop() {
  fill_solid(leds, LED_COUNT, CRGB::Red);
  FastLED.show();
  delay(500);
  fill_solid(leds, LED_COUNT, CRGB::Blue);
  FastLED.show();
  delay(500);
}
