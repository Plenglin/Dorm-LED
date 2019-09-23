#pragma once

#include <Arduino.h>

#include "segment.hpp"

namespace state {
  String read_next_token(char* &iter, char* end) {
    String token;
    while (iter != end) {
      char c = *iter;
      iter++;
      if ((c == '\n') || (c == ' ')) {
        return token;
      }
      token += c;
    }
    return token;
  }

  class State {
    private:
      int arg_count;
      String cmd_name;
      Segment* segment;
    public:
      State(int arg_count, String cmd_name) : arg_count(arg_count), cmd_name(cmd_name) {

      }

      Segment* get_segment() {
        return segment;
      }

      void set_segment(Segment* segment) {
        this->segment = segment;
      }

      String get_cmd_name() { 
        return cmd_name; 
      }

      State* process_arguments(char* iter, char* end, State* current_state) {
        String args[arg_count];
        int i = 0;
        while (iter != end && i < arg_count) {
          args[i] = read_next_token(iter, end);
          i++;
        }
        if (parse_args(i, args)) {
          if (current_state != this) {
            current_state->terminate();
          }
          this->init();
          return this;
        }
        return current_state;
      }

      virtual bool parse_args(int arg_count, String* args) {
        return false;
      }
      virtual void init() {}
      virtual void update() {}
      virtual void terminate() {}
  };

  class StateManager {
    private:
      int count;
      State** states;
      state::State* current_state;
      Segment* current_segment;
    public:
      StateManager(int count, State** states) : count(count), states(states) {
        current_state = states[0];
      }

      void init(Segment* segment) {
        for (int i = 0; i < count; i++) {
          states[i]->set_segment(segment);
        }
        current_state->init();
      }

      State* read_commands(char* iter, char* end) {
        auto command = read_next_token(iter, end);
        for (int i = 0; i < count; i++) {
          if (states[i]->get_cmd_name() == command) {
            current_state = states[i]->process_arguments(iter, end, current_state);
            break;
          }
        }
        return current_state;
      }

      void update() {
        current_state->update();
      }
  };

}