#ifndef SLIDER_H
#define SLIDER_H

#include <Arduino.h>
#include "Config.h"

static const int VALUE_CHANGE_THRESHOLD = 3;

class Slider
{
private:
  int _pin;
  int _lastAnalogValue = -50;

  bool _hasNewAnalogValue = false;

public:
    Slider(int pin);

    void Init();
    void Update();
    uint8_t Read();

    static bool HasChange(uint8_t volumeByte);
};

#endif