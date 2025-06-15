# ESP32 Ping Display with LED Matrix

This project visualizes the current ping time on an LED matrix. The lower the ping, the higher the bar display.

## 🔧 Hardware

- ESP32 (tested with Arduino Nano ESP32)
- Arduino LED matrix (12x8)
- Wi-Fi connection (SSID + password)

## 💡 Features

- Connects to `clients3.google.com`
- Measures ping time using `WiFiClient.connect()`
- Displays the ping time as bars on the LED matrix
- Bars scroll to the right to show historical data

## 📚 Used Libraries

- `WiFiS3.h`
- `Arduino_LED_Matrix.h`

## ⚙️ Setup

1. Enter your Wi-Fi credentials in the code (`ssid`, `password`)
2. Connect the LED matrix via I2C
3. Upload the sketch to your ESP32 board

## 📊 Bar Height (Ping in ms)

| Ping Time | Bar Height |
|-----------|------------|
| ≤ 40 ms   | 8          |
| ≤ 50 ms   | 7          |
| ≤ 60 ms   | 6          |
| ≤ 70 ms   | 5          |
| ≤ 80 ms   | 4          |
| ≤ 90 ms   | 3          |
| ≤ 250 ms  | 2          |
| ≤ 800 ms  | 1          |
| > 800 ms  | 0 (no internet) |

---

## ⚠️ Note

Be sure to set your own Wi-Fi credentials:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
