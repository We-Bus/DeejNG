#include "Button.h"

Button::Button(int pin) {
  _pin = pin;
}

void Button::Init() {
  pinMode(_pin, INPUT_PULLUP);
  _buttonCommand = ButtonCommand::IDLE;
}

void Button::Update() {
  _pressedThisUpdate = (digitalRead(_pin) == LOW);

  if (_pressedThisUpdate) {
    _timePressed += LOOP_DELAY_MS;
  } else {
    if (_timePressed >= LONG_PRESS_TIME_MS) {
      _buttonCommand = ButtonCommand::LONG;
    } else if (_timePressed > 0) {
      _buttonCommand = ButtonCommand::SHORT;
    }
    _timePressed = 0;
  }
}

// This reads the button and if its not pressed, it resets it to idle.
uint8_t Button::Read() {
  if (_pressedThisUpdate) {
    return ButtonCommand::IDLE;
  }

  auto updateCommand = _buttonCommand;
  _buttonCommand = ButtonCommand::IDLE;

  return static_cast<uint8_t>(updateCommand);
}


bool Button::HasChange(uint8_t buttonByte){
  return (buttonByte != 0);
}
