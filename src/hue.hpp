#pragma once

#include "state.hpp"
#include "util.hpp"

class HueState : public state::State {
 private:
  byte hue_delta = 0;
  byte hue_start = 0;
  byte hue_add_delta = 1;

  AdaptiveSleeper sleeper = AdaptiveSleeper(0);

 public:
  HueState() : state::State(3, "hue") {}
  virtual bool parse_args(int parsed_args, String* cmds) { 
    if (parsed_args != 3) {
      return false;
    }
    hue_delta = cmds[0].toInt();
    hue_add_delta = cmds[1].toInt();
    unsigned long sleep_period = cmds[2].toInt();
    sleeper = AdaptiveSleeper(sleep_period);

    Serial.print("delta=");
    Serial.print(hue_delta);
    Serial.print(" rate=");
    Serial.print(hue_add_delta);
    Serial.print("/");
    Serial.print(sleep_period);
    Serial.println("ms");
    return true; 
  }
  virtual void update() {
    auto segment = get_segment();
    fill_rainbow(segment->get_leds(), segment->get_led_count(), hue_start, hue_delta);
    FastLED.show();
    hue_start += hue_add_delta;
    sleeper.sleep();
  }
  virtual void terminate() {
    auto segment = get_segment();
    fill_solid(segment->get_leds(), segment->get_led_count(), CRGB::Black);
  }
};
