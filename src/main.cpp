#include <Arduino.h>
#include <Wire.h>

#include <FastLED.h>
#include <LiquidCrystal_PCF8574.h>

#include "constants.hpp"
#include "fill.hpp"
#include "reactive.hpp"


const int LED_COUNT = 84;
const int SEG_A = 20;
const int SEG_B = LED_COUNT - SEG_A;
CRGB leds[LED_COUNT];

const int STATE_COUNT = 2;
state::State* states[STATE_COUNT] = {
  new FillState<LED_COUNT>(leds),
  new ReactiveState<LED_COUNT>(leds)
};
state::StateManager state_manager(Serial, STATE_COUNT, states);

void setup() {
  Serial.begin(38400);
  Serial.println("Initializing");
  FastLED.addLeds<WS2812B, pin::LED_DATA, BRG>(leds, LED_COUNT);
  fill_solid(leds, LED_COUNT, CRGB::Black);
  FastLED.show();
  state_manager.init();
}

void loop() {
  state_manager.read_commands();
  state_manager.update();
}
