#pragma once

#include <Arduino.h>


namespace pin {
  const int LED_DATA = 2;
  const int PHOTORESISTOR = A0;
}

namespace constant {
  const int LED_COUNT = 84;
  const int SEG_A = 20;
  const int SEG_B = LED_COUNT - SEG_A;
}
