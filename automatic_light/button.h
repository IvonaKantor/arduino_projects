#pragma once

struct Button {
  int pin;
  int pressCount;
  bool lastState;
  int ledPin;
};
