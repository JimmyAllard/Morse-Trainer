/**
 * @file main.cpp
 * @brief Morse Trainer — Arduino UNO R3 sketch.
 *
 * Reads Morse code keyed on a push button, decodes it using the
 * hardware-independent logic in lib/morse_core and lib/morse_timing,
 * shows the decoded text on a 16x2 LCD (4-bit mode), and sounds a
 * passive buzzer while the key is held.
 *
 * Buzzer volume is controlled by a potentiometer wired in series with the
 * buzzer in hardware (see include/pins.h) — no software volume logic here.
 */

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "pins.h"

void setup()
{
}

void loop()
{
}
