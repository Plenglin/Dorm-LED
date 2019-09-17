#pragma once

#include <Arduino.h>

class AdaptiveSleeper {
  unsigned long last_time;
  long target_delta;
  long next_sleep;

 public:
  AdaptiveSleeper(unsigned long target_delta) : target_delta(target_delta), next_sleep(target_delta) {
    last_time = millis();
  }

  void sleep() {
    unsigned long current_time = millis();
    long actual_delta = current_time - last_time;
    next_sleep += target_delta - actual_delta;
    if (next_sleep > 0) {
      delay(next_sleep);
    }
    last_time = current_time;
  }
};
