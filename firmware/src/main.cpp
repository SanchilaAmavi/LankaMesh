#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "mesh_protocol.h"
#include "sensor_handler.h"
#include "display_handler.h"
#include "gps_handler.h"
#include "lora_handler.h"

SensorHandler sensorHandler;
DisplayHandler displayHandler;
GpsHandler gpsHandler;
LoRaHandler loraHandler;
SeenCache seenCache(SEEN_CACHE_SIZE);

uint32_t lastGpsBroadcast = 0;
uint32_t lastSensorRead = 0;
uint32_t lastDisplayRefresh = 0;
uint16_t seq = 1;
char lastMessage[64] = "Initializing";
bool sosTriggered = false;

void sendPacket(MsgType type, const char *payload, uint8_t dst = BROADCAST_ID) {
  MeshPacket pkt{};
  pkt.srcId = NODE_ID;
  pkt.dstId = dst;
  pkt.msgType = type;
  pkt.seq = seq++;
  pkt.lat = gpsHandler.latitude();
  pkt.lon = gpsHandler.longitude();
  pkt.category = CAT_OTHER;
  pkt.payloadLen = strlen(payload);
  strncpy(pkt.payload, payload, sizeof(pkt.payload) - 1);
  pkt.payload[sizeof(pkt.payload) - 1] = '\0';
  loraHandler.send(pkt);
}

void handleSos() {
  sosTriggered = true;
  displayHandler.showSosSent();
  snprintf(lastMessage, sizeof(lastMessage), "SOS sent");
  sendPacket(MSG_SOS, "SOS");
}

void setup() {
  pinMode(SOS_BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(APP_SERIAL_BAUD);
  delay(1000);

  bool displayOk = displayHandler.begin();
  if (!displayOk) {
    snprintf(lastMessage, sizeof(lastMessage), "OLED init failed");
  }

  sensorHandler.begin();
  gpsHandler.begin();

  if (!loraHandler.begin()) {
    snprintf(lastMessage, sizeof(lastMessage), "LoRa init failed");
  } else {
    snprintf(lastMessage, sizeof(lastMessage), "Ready");
  }

  sendPacket(MSG_NODE_HELLO, "HELLO");
}

void loop() {
  gpsHandler.update();

  if (digitalRead(SOS_BUTTON_PIN) == LOW) {
    static uint32_t lastSosPress = 0;
    if (millis() - lastSosPress > SOS_DEBOUNCE_MS) {
      handleSos();
      lastSosPress = millis();
    }
  }

  if (millis() - lastSensorRead >= SENSOR_READ_INTERVAL_MS) {
    sensorHandler.read();
    lastSensorRead = millis();
  }

  if (millis() - lastGpsBroadcast >= GPS_BROADCAST_INTERVAL_MS) {
    sendPacket(MSG_GPS_PING, "PING");
    lastGpsBroadcast = millis();
  }

  MeshPacket incoming{};
  if (loraHandler.receive(incoming)) {
    if (!seenCache.hasSeen(incoming.srcId, incoming.seq)) {
      seenCache.markSeen(incoming.srcId, incoming.seq);
      snprintf(lastMessage, sizeof(lastMessage), "Packet from %u", incoming.srcId);
      if (incoming.msgType == MSG_SOS) {
        displayHandler.showSosSent();
      }
    }
  }

  if (millis() - lastDisplayRefresh >= DISPLAY_REFRESH_INTERVAL_MS) {
    displayHandler.showStatus(
        gpsHandler.hasFix(),
        3,
        sensorHandler.temperature(),
        sensorHandler.humidity(),
        lastMessage);
    lastDisplayRefresh = millis();
  }

  delay(10);
}
