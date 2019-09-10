#pragma once

#include "state.hpp"

namespace state {
  class Fill : public State {
    public:
      Fill() : State(0, "fill") {}

      virtual void init(Stream& stream, int parsed_args, String* cmds) {
        
      }
  };
}
