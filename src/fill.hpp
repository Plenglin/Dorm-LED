#pragma once

#include <FastLED.h>

#include "state.hpp"

template <int led_count>
class FillState : public state::State {
  private:
    CRGB* leds;
    CRGB color = CRGB::Black;
  public:
    FillState(CRGB* leds) : state::State(3, "fill"), leds(leds) {}

    virtual bool parse_args(int parsed_args, String* cmds) override {
      if (parsed_args == 1) {
        byte value = cmds[0].toInt();
        color = CHSV(0, 0, value);

        Serial.print("Fill Value ");
        Serial.println(value);
        return true;
      } else if (parsed_args == 3) {
        int r = cmds[0].toInt();
        int g = cmds[1].toInt();
        int b = cmds[2].toInt();

        color = CRGB(cmds[0].toInt(), cmds[1].toInt(), cmds[2].toInt());

        Serial.print("Fill RGB ");
        Serial.print(r);
        Serial.print(" ");
        Serial.print(g);
        Serial.print(" ");
        Serial.print(b);
        Serial.print("\n");
        return true;
      }
      return false;
    }

    virtual void init() override {
      fill_solid(leds, led_count, color);
      FastLED.show();
    }

    virtual void terminate() override {
      fill_solid(leds, led_count, CRGB::Black);
      FastLED.show();
    }
};
