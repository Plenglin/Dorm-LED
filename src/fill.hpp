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

    virtual bool parse_args(Stream& stream, int parsed_args, String* cmds) override {
      if (parsed_args == 1) {
        byte value = cmds[0].toInt();
        stream.print("Fill Value ");
        stream.println(value);
        color = CHSV(0, 0, value);
        return true;
      } else if (parsed_args == 3) {
        //stream.print("Fill RGB");
        color = CRGB(cmds[0].toInt(), cmds[1].toInt(), cmds[2].toInt());
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
