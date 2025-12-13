# Oculun

Oculun is a lightweight PlatformIO library that provides higher-level text utilities for SSD1306 OLED displays based on the Adafruit GFX ecosystem.

The project name is derived from oculus (Latin for eye), reflecting its purpose as a visual output helper.
Oculun aims to simplify common text-rendering tasks while remaining minimal, predictable, and extensible.

## Overview

Oculun acts as a thin abstraction layer on top of Adafruit_SSD1306, focusing on ergonomic text control rather than replacing the underlying display driver.

The library is designed with the following principles:
- Minimal overhead
- Clear and deterministic behavior
- Compatibility with existing Adafruit APIs
- Easy integration into PlatformIO projects
- Extensibility for future visual utilities

## Features

- SSD1306 OLED initialization via I²C
- Text rendering with configurable size and position
- Automatic horizontal and vertical text centering
- Multiline text support
- Simple display flash / invert effect
- Designed for ESP32 and Arduino-based platforms

## Dependencies

Oculun relies on the following libraries:
- Adafruit SSD1306
- Adafruit GFX Library
- Wire (Arduino core)

These dependencies are standard within the Arduino / PlatformIO ecosystem and are automatically resolved when using PlatformIO.

## Installation

### PlatformIO (GitHub source)

Add the following to your platformio.ini:
```ini
lib_deps =
  https://github.com/kuu-shi/oculun.git
```

### Local Library

Alternatively, place the library in your project’s lib directory:
```
lib/
└── oculun/
    ├── include/
    │   └── Oculun.h
    ├── src/
    │   └── Oculun.cpp
```

## Basic Usage

```cpp
#include <Oculun.h>

Oculun display(21, 22); // SDA, SCL

void setup() {
  display.begin();
}
```

The constructor accepts the I²C SDA and SCL pin numbers, allowing flexible pin assignment (e.g. ESP32).

## API Reference

### writeText

Writes text at a specified position.

```cpp
oled.writeText("Hello World", 2, 0, 0);
```

**Parameters**

| Name | Type | Description |
| --- | --- | --- |
| `text` | `String` | Text to display |
| `size` | `uint8_t` | Text scale factor (default: `2`) |
| `x` | `uint8_t` | Horizontal cursor position (default: `0`) |
| `y` | `uint8_t` | Vertical cursor position (default: `0`) |

### centerText

Centers text both horizontally and vertically on the display.
Multiline text is supported using newline characters (`\n`).

```cpp
oled.centerText("Hello\nWorld", 2);
```

**Parameters**

| Name | Type | Description |
| --- | --- | --- |
| `text` | `String` | Text to display |
| `size` | `uint8_t` | Text scale factor (default: `2`) |

**Notes**
- Uses the default Adafruit GFX font (6×8 pixels per character at size 1)
- Calculates alignment dynamically per line
- Clears the display before rendering

### flash

Inverts the display colors for visual feedback.

**Parameters**

```cpp
oled.flash(3, 200);
```

| Name | Type | Description |
| --- | --- | --- |
| `times` | `uint8_t` | Number of flash cycles (default: `2`) |
| `duration` | `uint16_t` | Duration per state in milliseconds (default: `150`) |

## Design Considerations

- The library intentionally avoids hiding Adafruit APIs
(advanced users may still access `Adafruit_SSD1306` features directly).
- Effects are implemented using blocking delays for simplicity.
- Text metrics assume the default GFX font; custom fonts may require adjustments.
- The library prioritizes clarity over aggressive optimization.


## Project Status

Oculun is currently under active early development. The API is stable for basic usage, but additional features and refinements are planned.

## Roadmap

Planned enhancements include:
- Additional text alignment modes
- Basic animation helpers
- Bitmap rendering utilities
- Optional non-blocking effects
- Extended font handling

## License

This project is licensed under the MIT License.

## Author

### Tabah Mulya
GitHub: https://github.com/tabah-mly