#pragma once

#include <Arduino.h>

namespace state {
  String read_token(Stream &stream, bool &reached_end) {
    String arg;
    reached_end = false;
    while (stream.available()) {
      char c = stream.read();
      reached_end = (c == '\n');
      if (reached_end || c == ' ') {
        return arg;
      }
      arg += c;
    }
    reached_end = true;
    return arg;
  }

  class State {
    private:
      int arg_count;
      String cmd_name;
    public:
      State(int arg_count, String cmd_name) : arg_count(arg_count), cmd_name(cmd_name) {

      }

      String get_cmd_name() { 
        return cmd_name; 
      }

      State* process_arguments(Stream& stream, State* current_state) {
        String args[arg_count];
        bool reached_end = false;
        int i = 0;
        while (i < arg_count && !reached_end) {
          args[i] = read_token(stream, reached_end);
          i++;
        }
        if (parse_args(stream, i, args)) {
          current_state->terminate();
          this->init();
          return this;
        }
        return current_state;
      }

      virtual bool parse_args(Stream& stream, int parsed_args, String* cmds) {
        return false;
      }
      virtual void init() {}
      virtual void update() {}
      virtual void terminate() {}
  };

  class StateManager {
    private:
      Stream& stream;
      int count;
      State** states;
      state::State* current_state;
    public:
      StateManager(Stream &stream, int count, State** states) : stream(stream), count(count), states(states) {
        current_state = states[0];
      }

      void init() {
        current_state->init();
      }

      void read_commands() {
        if (!stream.available()) {
          return;
        }
        delay(10);
        bool flag = false;
        auto command = read_token(stream, flag);
        for (int i = 0; i < count; i++) {
          if (states[i]->get_cmd_name() == command) {
            current_state = states[i]->process_arguments(stream, current_state);
            break;
          }
        }
      }

      void update() {
        current_state->update();
      }
  };

}