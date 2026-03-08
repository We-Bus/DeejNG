#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

static const uint16_t LONG_PRESS_TIME_MS = 600;

// how many loops between a write to the mixer
static const uint8_t LOOPS_PER_WRITE = 2;
static const int LOOP_DELAY_MS = 25;

// Leave this as it as RAW-HID reports usually don't work unless 64 bytes
static const uint8_t REPORT_SIZE = 64;
#endif