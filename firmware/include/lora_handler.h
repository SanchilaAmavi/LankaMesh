#pragma once

#include <LoRa.h>
#include "config.h"
#include "mesh_protocol.h"

class LoRaHandler {
 public:
  bool begin() {
    LoRa.setPins(LORA_CS, LORA_RST, LORA_DIO0);
    if (!LoRa.begin(LORA_FREQUENCY)) {
      return false;
    }
    LoRa.setSpreadingFactor(LORA_SPREADING);
    LoRa.setSignalBandwidth(LORA_BANDWIDTH);
    LoRa.setCodingRate4(LORA_CODING_RATE);
    LoRa.setTxPower(LORA_TX_POWER);
    LoRa.enableCrc();
    return true;
  }

  void send(MeshPacket &pkt) {
    pkt.crc = computePacketCrc(pkt);
    LoRa.beginPacket();
    LoRa.write(reinterpret_cast<uint8_t *>(&pkt), sizeof(MeshPacket));
    LoRa.endPacket();
  }

  bool receive(MeshPacket &out) {
    int packetSize = LoRa.parsePacket();
    if (packetSize == 0) return false;
    if (packetSize != sizeof(MeshPacket)) {
      while (LoRa.available()) LoRa.read();
      return false;
    }

    uint8_t buf[sizeof(MeshPacket)];
    for (size_t i = 0; i < sizeof(MeshPacket) && LoRa.available(); i++) {
      buf[i] = LoRa.read();
    }
    memcpy(&out, buf, sizeof(MeshPacket));

    uint16_t expected = computePacketCrc(out);
    if (expected != out.crc) return false;

    lastRssi_ = LoRa.packetRssi();
    lastSnr_  = LoRa.packetSnr();
    return true;
  }

  int lastRssi() const { return lastRssi_; }
  float lastSnr() const { return lastSnr_; }

  void relayWithBackoff(MeshPacket &pkt) {
    uint32_t delayMs = random(RELAY_BACKOFF_MIN_MS, RELAY_BACKOFF_MAX_MS);
    delay(delayMs);
    send(pkt);
  }

 private:
  int lastRssi_ = 0;
  float lastSnr_ = 0;
};
