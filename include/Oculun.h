#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>

class Oculun {
public:
  Oculun(uint8_t sda, uint8_t scl);

  void begin();
  void centerText(const String& text, uint8_t size);
  void writeText(const String& text, uint8_t size = 2, uint8_t x = 0, uint8_t y = 0);
  void flash(uint8_t times = 2, uint16_t duration = 150);

private:
  Adafruit_SSD1306 display;
  int SDA_PIN, SCL_PIN;
};
