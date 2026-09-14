/**
 * @file pins.h
 * @brief Single source of truth for the Morse Trainer's Arduino UNO R3 wiring.
 *
 * LCD1602 is wired in 4-bit direct mode (no I2C backpack):
 *   LCD RS -> D12      LCD D4 -> D5
 *   LCD E  -> D11      LCD D5 -> D4
 *   LCD RW -> GND      LCD D6 -> D3
 *                      LCD D7 -> D2
 *   LCD VSS -> GND, LCD VDD -> 5V, LCD A -> 5V (backlight), LCD K -> GND
 *   LCD V0  -> contrast pot wiper (separate trim pot, hardware-only —
 *              not driven by the Arduino)
 *
 * Buzzer volume potentiometer: wired in series between the buzzer and GND
 * as a hardware volume control (no Arduino pin involved). If you'd rather
 * read it in software instead (e.g. to drive a PWM duty cycle), wire its
 * wiper to POT_PIN below and adjust main.cpp accordingly.
 */

#ifndef PINS_H
#define PINS_H

// --- LCD1602 (4-bit mode) ---------------------------------------------------
#define LCD_RS_PIN 12
#define LCD_EN_PIN 11
#define LCD_D4_PIN 5
#define LCD_D5_PIN 4
#define LCD_D6_PIN 3
#define LCD_D7_PIN 2

// --- Buzzer ------------------------------------------------------------------
#define BUZZER_PIN 9 // PWM-capable pin, used with tone()/noTone()

// --- Button (Morse key) -------------------------------------------------------
#define BUTTON_PIN 8 // wired to GND, uses INPUT_PULLUP (active LOW)

// --- Potentiometer -------------------------------------------------------------
// Reserved analog pin if the pot is ever read in software (see note above).
#define POT_PIN A0

#endif // PINS_H
