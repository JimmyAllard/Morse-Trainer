/**
 * @file lcd_smoke_test.cpp
 * @brief Standalone LCD wiring test. Build with `pio run -e lcd_test`.
 *
 * Prints a static line plus a live counter, so you can confirm both that
 * the 4-bit wiring is correct (text is readable) and that the LCD is
 * actually refreshing (the counter increments).
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "pins.h"

LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

void setup()
{
    lcd.begin(16, 2);
    lcd.print("LCD OK");
}

void loop()
{
    static uint16_t counter = 0;
    lcd.setCursor(0, 1);
    lcd.print("tick: ");
    lcd.print(counter++);
    lcd.print("   "); // pad to clear leftover digits from a larger number
    delay(500);
}
