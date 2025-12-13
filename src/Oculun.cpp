#include "Oculun.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDR 0x3C

Oculun::Oculun(uint8_t sda, uint8_t scl)
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire), SDA_PIN(sda), SCL_PIN(scl) {}

void Oculun::begin() {
  Wire.begin(SDA_PIN, SCL_PIN);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR);
}

void Oculun::flash(uint8_t times, uint16_t duration) {
  for (uint8_t t = 0; t < times; t++) {
    display.invertDisplay(true);
    delay(duration);
    display.invertDisplay(false);
    delay(duration);
  }
}

void Oculun::writeText(const String& text, uint8_t size, uint8_t x, uint8_t y) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(size);
  display.setCursor(x, y);
  display.print(text);
  display.display();
}

void Oculun::centerText(const String& text, uint8_t size) {
  uint16_t w = display.width();
  uint16_t h = display.height();

  uint16_t charW = 6 * size;
  uint16_t charH = 8 * size;

  uint8_t lines = 1;
  for (char c : text) {
    if (c == '\n') {
      lines++;
    }
  }

  uint8_t totalH = lines * charH;
  uint8_t yStart = (h - totalH) / 2;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(size);

  uint8_t y = yStart;
  String line = "";

  for (uint8_t i = 0; i <= text.length(); i++) {
    if (i == text.length() || text[i] == '\n') {
      uint8_t textWidth = line.length() * charW;
      uint8_t x = (w - textWidth) / 2;
      display.setCursor(x, y);
      display.print(line);
      y += charH;
      line = "";
    } else {
      line += text[i];
    }
  }

  display.display();
}
