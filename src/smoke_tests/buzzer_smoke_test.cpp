/**
 * @file buzzer_smoke_test.cpp
 * @brief Standalone buzzer wiring test. Build with `pio run -e buzzer_test`.
 *
 * Beeps at two different pitches on a loop, so you can confirm the buzzer
 * is wired correctly and that tone()/noTone() work as expected. If a
 * volume potentiometer is wired in series (hardware-only), turning it
 * should audibly change the loudness of these beeps.
 */

#include <Arduino.h>
#include "pins.h"

void setup()
{
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
    tone(BUZZER_PIN, 1000);
    delay(200);
    noTone(BUZZER_PIN);
    delay(200);

    tone(BUZZER_PIN, 1500);
    delay(200);
    noTone(BUZZER_PIN);
    delay(600);
}
