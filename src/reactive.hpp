#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "constants.hpp"
#include "state.hpp"

template <int led_count>
class ReactiveState : public state::State {
  private:
    CRGB* leds;
  public:
    ReactiveState(CRGB* leds) : state::State(0, "reactive"), leds(leds) {}

    virtual bool parse_args(int parsed_args, String* cmds) override {
      return true;
    }

    virtual void update() override {
      int level = analogRead(pin::PHOTORESISTOR);
      byte value = 255 - (level / 4);
      fill_solid(leds, led_count, CHSV(0, 0, value));
      FastLED.show();
    }
};
