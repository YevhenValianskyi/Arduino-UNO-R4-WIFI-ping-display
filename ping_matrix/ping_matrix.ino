#include <WiFiS3.h>
#include "Arduino_LED_Matrix.h"

// Wi-Fi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Target server for ping
const IPAddress serverAddr(216, 58, 206, 78); // clients3.google.com
const int serverPort = 80;

WiFiClient client;
ArduinoLEDMatrix matrix;

// Matrix size
const int width = 12;
const int height = 8;
uint8_t pixels[width * height];

void setup() {
  Serial.begin(115200);
  delay(1000);

  matrix.begin();
  clearMatrix();

  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Wi-Fi connected");
}

void clearMatrix() {
  memset(pixels, 0, sizeof(pixels));
  matrix.loadPixels(pixels, width * height);
}

void shiftRight() {
  for (int x = width - 1; x > 0; x--) {
    for (int y = 0; y < height; y++) {
      pixels[y * width + x] = pixels[y * width + (x - 1)];
    }
  }
}

void drawColumn(int heightValue) {
  for (int y = 0; y < height; y++) {
    pixels[y * width + 0] = (y >= (height - heightValue)) ? 1 : 0;
  }
}

int calculateBarHeight(unsigned long ping) {
  if (ping <= 40)       return 8;
  else if (ping <= 50)  return 7;
  else if (ping <= 60)  return 6;
  else if (ping <= 70)  return 5;
  else if (ping <= 80)  return 4;
  else if (ping <= 90)  return 3;
  else if (ping <= 250) return 2;
  else if (ping <= 800) return 1;
  else                  return 0;
}

void loop() {
  unsigned long start = millis();
  bool success = client.connect(serverAddr, serverPort);
  unsigned long pingTime = millis() - start;

  int barHeight = 0;

  if (success) {
    client.println("GET /generate_204 HTTP/1.1");
    client.println("Host: clients3.google.com");
    client.println("Connection: close");
    client.println();

    String response = "";
    unsigned long timeout = millis();

    while (client.available() == 0 && millis() - timeout < 3000) {
      delay(10);
    }

    while (client.available()) {
      char c = client.read();
      response += c;
    }

    if (response.indexOf("204 No Content") != -1) {
      barHeight = calculateBarHeight(pingTime);
    } else {
      Serial.println("⚠️ No 204 header – possible captive portal?");
      barHeight = 0;
    }

    client.stop();
  } else {
    Serial.println("❌ Connection failed");
    barHeight = 0;
  }

  Serial.print("Ping: ");
  Serial.print(pingTime);
  Serial.print(" ms | Bar height: ");
  Serial.println(barHeight);

  shiftRight();
  drawColumn(barHeight);
  matrix.loadPixels(pixels, width * height);

  delay(1000);
}
