#pragma once

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

class DisplayHandler {
 public:
  bool begin() {
    Wire.begin(OLED_SDA, OLED_SCL);
    if (!display_.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
      return false;
    }
    display_.clearDisplay();
    display_.setTextColor(SSD1306_WHITE);
    display_.display();
    return true;
  }

  void showStatus(bool gpsFix, int nodesInRange, float temp, float humidity,
                  const char *lastMsg) {
    display_.clearDisplay();
    display_.setTextSize(1);
    display_.setCursor(0, 0);
    display_.println(String("LankaMesh Node #") + String(NODE_ID));
    display_.drawLine(0, 10, OLED_WIDTH, 10, SSD1306_WHITE);

    display_.setCursor(0, 14);
    display_.print("GPS: ");
    display_.println(gpsFix ? "Active" : "Searching...");

    display_.setCursor(0, 24);
    display_.print("Nodes: ");
    display_.println(nodesInRange);

    display_.setCursor(0, 34);
    display_.print(temp, 1);
    display_.print((char)247);
    display_.print("C  ");
    display_.print(humidity, 0);
    display_.println("%");

    display_.setCursor(0, 46);
    display_.println("Last Message:");
    display_.setCursor(0, 56);
    display_.println(lastMsg);

    display_.display();
  }

  void showSosSent() {
    display_.clearDisplay();
    display_.setTextSize(2);
    display_.setCursor(10, 20);
    display_.println("SOS SENT");
    display_.display();
  }

 private:
  Adafruit_SSD1306 display_{OLED_WIDTH, OLED_HEIGHT, &Wire, -1};
};
