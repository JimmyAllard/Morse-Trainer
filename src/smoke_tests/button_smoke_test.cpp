/**
 * @file button_smoke_test.cpp
 * @brief Standalone button wiring test. Build with `pio run -e button_test`.
 *
 * Logs press/release events over Serial and mirrors the state on the
 * onboard LED, so you can confirm the button and its pull-up wiring
 * without needing the LCD or buzzer connected at all.
 */

#include <Arduino.h>
#include "pins.h"

void setup()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    static bool wasPressed = false;
    const bool isPressed = (digitalRead(BUTTON_PIN) == LOW);

    digitalWrite(LED_BUILTIN, isPressed ? HIGH : LOW);

    if (isPressed != wasPressed)
    {
        Serial.println(isPressed ? "PRESSED" : "RELEASED");
        wasPressed = isPressed;
    }
}
