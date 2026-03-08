#include "Slider.h"
#include "Button.h"
#include "Config.h"
#include "HID-Project.h"

#define COUNT_OF(x) (sizeof(x) / sizeof((x)[0]))

static uint8_t outBuf[REPORT_SIZE];  // host->device buffer required by this RawHID API

int _loopsSinceLastWrite = LOOPS_PER_WRITE;



Slider sliders[] = {
  Slider(A3),
  Slider(A2),
  Slider(A1),
  Slider(A0),
  Slider(10)
};

Button buttons[] = {
  Button(2),
  Button(3),
  Button(4),
  Button(5),
  Button(6),
  Button(14),
  Button(15),
  Button(16)
};

const uint8_t sliderCount = COUNT_OF(sliders);
const uint8_t buttonCount = COUNT_OF(buttons);

void setup()
{
  RawHID.begin(outBuf, sizeof(outBuf));

  for (uint8_t i = 0; i < sliderCount; i++) {
    sliders[i].Init();
  }

  for (uint8_t i = 0; i < buttonCount; i++) {
    buttons[i].Init();
  }
}

void loop()
{
  _loopsSinceLastWrite--;

  for (uint8_t i = 0; i < buttonCount; i++) {
    buttons[i].Update();
  }

  for (uint8_t i = 0; i < sliderCount; i++) {
    sliders[i].Update();
  }

  if (_loopsSinceLastWrite <= 0)
  {
    uint8_t report[REPORT_SIZE] = {0};
    uint8_t offset = 0;
    bool hasAnyChange = false;

    // Layout:
    // [0,1]                                              = slider count | button count
    // [2..(sliderCount+1)]                               = 5 channels * (buttonByte, volumeByte)
    // [(sliderCount+2)..(sliderCount + buttonCount + 1)] = 3 extra buttons (1 byte each)
    // rest                                               = unused (0)

    report[0] = sliderCount;
    report[1] = buttonCount;

    // Keeps track on where the next byte should be set in the send buffer
    int continuousIndex = 2;    

    for (uint8_t i = 0; i < sliderCount; i++)
    {
      uint8_t volumeByte = sliders[i].Read();
      hasAnyChange |= Slider::HasChange(volumeByte);

      report[continuousIndex] = volumeByte;
      continuousIndex++;
    }

    for (uint8_t i = 0; i < buttonCount; i++)
    {
      uint8_t buttonByte = buttons[i].Read();

      hasAnyChange |= Button::HasChange(buttonByte);

      report[continuousIndex] = buttonByte;
      continuousIndex++;
    }

    if (hasAnyChange) {
      RawHID.write(report, REPORT_SIZE);
    }

    _loopsSinceLastWrite = LOOPS_PER_WRITE;
  }

  delay(LOOP_DELAY_MS);
}