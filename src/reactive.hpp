#pragma once

#include <Arduino.h>
#include <FastLED.h>

#include "constants.hpp"
#include "state.hpp"

class ReactiveState : public state::State {
  public:
    ReactiveState() : state::State(0, "reactive") {}

    virtual bool parse_args(int parsed_args, String* cmds) override {
      return true;
    }

    virtual void update() override {
      int level = analogRead(pin::PHOTORESISTOR);
      byte value = 255 - (level / 4);
      auto segment = get_segment();
      fill_solid(segment->get_leds(), segment->get_led_count(), CHSV(0, 0, value));
      FastLED.show();
    }
};
