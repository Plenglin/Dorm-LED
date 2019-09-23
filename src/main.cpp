#include <Arduino.h>
#include <Wire.h>

#include <FastLED.h>
#include <LiquidCrystal_PCF8574.h>

#include "constants.hpp"
#include "fill.hpp"
#include "hue.hpp"
#include "rawwrite.hpp"
#include "reactive.hpp"

CRGB leds[constant::LED_COUNT];
Segment full_strand(constant::LED_COUNT, leds);

const int STATE_COUNT = 4;
FillState _fill_state;
ReactiveState _reactive_state;
rawwrite::RawWriteState _raw_write_state;
HueState _hue_state;
state::State* states[STATE_COUNT] = {&_fill_state, &_reactive_state,
                                     &_hue_state, &_raw_write_state};
state::StateManager state_manager(STATE_COUNT, states);

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");
  Serial.setTimeout(1000);

  FastLED.addLeds<WS2812B, pin::LED_DATA, BRG>(leds, constant::LED_COUNT);
  fill_solid(leds, constant::LED_COUNT, CRGB::Black);
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
