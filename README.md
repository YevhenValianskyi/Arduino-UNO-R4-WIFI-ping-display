# Arduino Uno R4 WIFI (Type-C USB) Ping Display with LED Matrix

![Arduino Uno R4 WIFI Ping Display](images/logo.jpg)

This project visualizes the current ping time on a 12x8 LED matrix. The lower the ping, the higher the bar displayed.

## 🔧 Hardware

- Arduino Uno R4 WIFI (Type-C USB) — only supported board  
- Wi-Fi connection (SSID + password)  

## 💡 Features

- Connects to `clients3.google.com`  
- Measures ping time using WiFi methods supported on the Uno R4 WIFI  
- Displays the ping time as bars on the LED matrix  
- Bars scroll to the right to show historical data  

## 📚 Used Libraries

- `WiFiS3.h`  
- `Arduino_LED_Matrix.h`  

## ⚙️ Setup

1. Enter your Wi-Fi credentials in the code (`ssid`, `password`)  
2. Upload the sketch to your Arduino Uno R4 WIFI board  

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

This project works **only** on the Arduino Uno R4 WIFI (Type-C USB) board with a 12x8 LED matrix.

Make sure to set your own Wi-Fi credentials:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
