#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "Config.h"

enum ButtonCommand : uint8_t
{
  IDLE  = 0b00000000,
  SHORT = 0b00000001,
  LONG  = 0b00000010,
};

class Button
{
private:
    int _pin;
    int _timePressed;
    bool _pressedThisUpdate;

    ButtonCommand _buttonCommand;

public:
    Button(int pin);

    void Init();
    void Update();
    uint8_t Read();

    static bool HasChange(uint8_t buttonByte);
};

#endif