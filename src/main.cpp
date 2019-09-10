#include <Arduino.h>
#include <Wire.h>

#include <FastLED.h>
#include <LiquidCrystal_PCF8574.h>

#include "states.hpp"


const int LED_COUNT = 84;
const int SEG_A = 20;
const int SEG_B = LED_COUNT - SEG_A;
CRGB leds[LED_COUNT];

const int STATE_COUNT = 1;
state::State* states[STATE_COUNT] = {
  new state::Fill()
};
state::StateManager state_manager(Serial, STATE_COUNT, states);

void parse_command() {
  String line = Serial.readStringUntil('\n');
  auto iter = line.begin();
  //auto cmd_end = strutils::get_token_end(iter, line.end(), ' ');

  while (iter != line.end()) {

  }
}

void setup() {
  Serial.begin(38400);
}

void loop() {
  state_manager.update();
}
