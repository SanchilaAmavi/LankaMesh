#pragma once

#include <DHT.h>
#include "config.h"

class SensorHandler {
 public:
  void begin() { dht_.begin(); }

  void read() {
    float t = dht_.readTemperature();
    float h = dht_.readHumidity();
    if (!isnan(t)) temperature_ = t;
    if (!isnan(h)) humidity_ = h;
  }

  float temperature() const { return temperature_; }
  float humidity() const { return humidity_; }

  static int batteryPercent(int milliVolts) {
    int pct = map(milliVolts, BATTERY_EMPTY_MV, BATTERY_FULL_MV, 0, 100);
    return constrain(pct, 0, 100);
  }

 private:
  DHT dht_{DHT_PIN, DHT_TYPE};
  float temperature_ = 0.0f;
  float humidity_ = 0.0f;
};
