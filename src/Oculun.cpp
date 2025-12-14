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

void Oculun::writeText(const char* text, uint8_t size, uint8_t x, uint8_t y) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(size);
  display.setCursor(x, y);
  display.print(text);
  display.display();
}

void Oculun::writeText(const String& text, uint8_t size, uint8_t x, uint8_t y) {
  writeText(text.c_str(), size, x, y);
}

void Oculun::centerText(const char* text, uint8_t size) {
  uint16_t w = display.width();
  uint16_t h = display.height();

  uint8_t charW = 6 * size;
  uint8_t charH = 8 * size;

  uint8_t lines = 1;
  for (const char* p = text; *p; ++p) {
    if (*p == '\n') {
      lines++;
    }
  }

  uint16_t totalH = lines * charH;
  uint16_t y = (h - totalH) / 2;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(size);

  const char* lineStart = text;
  while (*lineStart) {
    const char* lineEnd = lineStart;
    while (*lineEnd && *lineEnd != '\n') {
      lineEnd++;
    }

    uint8_t len = lineEnd - lineStart;
    uint16_t textW = len * charW;
    uint16_t x = (w - textW) / 2;

    display.setCursor(x, y);
    display.write((const uint8_t*)lineStart, len);

    y += charH;
    lineStart = (*lineEnd == '\n') ? lineEnd + 1 : lineEnd;
  }

  display.display();
}

void Oculun::centerText(const String& text, uint8_t size) {
  centerText(text.c_str(), size);
}
