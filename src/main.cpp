#include <Arduino.h>
#include <Wire.h>

#include <FastLED.h>
#include <LiquidCrystal_PCF8574.h>

#include "constants.hpp"
#include "fill.hpp"
#include "hue.hpp"
#include "reactive.hpp"

const int LED_COUNT = 84;
const int SEG_A = 20;
const int SEG_B = LED_COUNT - SEG_A;
CRGB leds[LED_COUNT];
Segment full_strand(LED_COUNT, leds);

const int STATE_COUNT = 3;
FillState _fill_state;
ReactiveState _reactive_state;
HueState _hue_state;
state::State* states[STATE_COUNT] = {&_fill_state, &_reactive_state, &_hue_state};
state::StateManager state_manager(STATE_COUNT, states);

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");
  Serial.setTimeout(1000);

  FastLED.addLeds<WS2812B, pin::LED_DATA, BRG>(leds, LED_COUNT);
  fill_solid(leds, LED_COUNT, CRGB::Black);
  FastLED.show();
  state_manager.init(&full_strand);
}

void loop() {
  if (Serial.available()) {
    auto s = Serial.readStringUntil('\n');
    Serial.println(s);
    state_manager.read_commands(s.begin(), s.end())->set_segment(&full_strand);
  }
  state_manager.update();
}
