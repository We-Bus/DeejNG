#include "Slider.h"

Slider::Slider(int pin)
{
  _pin = pin;
}

void Slider::Init() {
  pinMode(_pin, INPUT);
}

void Slider::Update() {
  int currentAnalogValue = analogRead(_pin);

  // Volume change was big enough to make a change
  if (abs(currentAnalogValue - _lastAnalogValue) > VALUE_CHANGE_THRESHOLD) {
    _hasNewAnalogValue = true;
    _lastAnalogValue = currentAnalogValue;
  }
}

uint8_t Slider::Read() {
  uint8_t volumeByte = 0;

  if (_hasNewAnalogValue) {
    // Convert analog reading to 0..100
    // If _lastAnalogValue is from analogRead(): 0..1023 (or 0..4095 on some boards)
    int volume = _lastAnalogValue;

    // If your ADC is 10-bit (0..1023). If it's different, change 1023 accordingly.
    volume = map(volume, 0, 1023, -3, 103);

    // Clamp (map can overshoot slightly)
    volume = min(max(volume, 0), 100);

    // Pack: MSB=1 means "new volume", lower 7 bits carry the value
    volumeByte = 0b10000000 | static_cast<uint8_t>(volume); // v fits in 0..100
  }

  _hasNewAnalogValue = false;

  return volumeByte;
}

bool Slider::HasChange(uint8_t volumeByte){
  return (volumeByte & 0b10000000);
}