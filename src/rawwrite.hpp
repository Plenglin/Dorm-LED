#include <Base64.h>

#include "constants.hpp"
#include "state.hpp"


namespace rawwrite {

  CRGB convert_8bit_color(char data) {
    return CRGB(
      (data & 0xe0),
      (data & 0x1c) << 3,
      (data & 0x03) << 6
    );
  }

  class RawWriteState : public state::State {
   public:
    RawWriteState() : state::State(1, "w") {}
    virtual bool parse_args(int arg_count, String* args) override {
      static char buf[constant::LED_COUNT] = {0};

      if (arg_count != 1) {
        return false;
      }

      auto segment = get_segment();
      int led_count = segment->get_led_count();
      auto leds = segment->get_leds();

      int encoded_length = Base64.encodedLength(led_count);

      int read_count = min(encoded_length, Base64.decodedLength(args[0].begin(), args[0].length()));
      int decoded_count = Base64.decode(buf, args[0].begin(), read_count);

      for (int i = 0; i < led_count; i++) {
        leds[i] = convert_8bit_color(buf[i]);
      }
      FastLED.show();

      Serial.print("Read=");
      Serial.print(read_count);
      Serial.print(" decoded=");
      Serial.print(decoded_count);
      Serial.print(" LEDs=");
      Serial.println(led_count);

      return true;
    }
  };

}
