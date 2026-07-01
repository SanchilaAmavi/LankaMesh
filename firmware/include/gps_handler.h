#pragma once

#include <TinyGPSPlus.h>
#include <HardwareSerial.h>
#include "config.h"

class GpsHandler {
 public:
  void begin() {
    gpsSerial_.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  }

  void update() {
    while (gpsSerial_.available() > 0) {
      gps_.encode(gpsSerial_.read());
    }
  }

  bool hasFix() const { return gps_.location.isValid(); }

  double latitude() const { return hasFix() ? gps_.location.lat() : 0.0; }
  double longitude() const { return hasFix() ? gps_.location.lng() : 0.0; }
  double accuracyMeters() const {
    return gps_.hdop.isValid() ? gps_.hdop.hdop() * 5.0 : 15.0;
  }
  int satellites() const { return gps_.satellites.isValid() ? gps_.satellites.value() : 0; }

 private:
  HardwareSerial gpsSerial_{1};
  TinyGPSPlus gps_;
};
