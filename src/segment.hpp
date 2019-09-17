#pragma once

#include <FastLED.h>


class Segment {
  private:
    const int led_count;
    CRGB* leds;
  public:
    Segment(int led_count, CRGB* leds) : led_count(led_count), leds(leds) {}
    CRGB* get_leds() {
      return leds;
    }
    int get_led_count() {
      return led_count;
    }
};
