#pragma once

#include <Arduino.h>

#define BROADCAST_ID 0xFF

enum MsgType : uint8_t {
  MSG_TEXT        = 0x01,
  MSG_SOS         = 0x02,
  MSG_GPS_PING    = 0x03,
  MSG_SENSOR_DATA = 0x04,
  MSG_ACK         = 0x05,
  MSG_NODE_HELLO  = 0x06
};

enum Category : uint8_t {
  CAT_MEDICAL     = 0x01,
  CAT_FLOOD       = 0x02,
  CAT_FIRE        = 0x03,
  CAT_LANDSLIDE   = 0x04,
  CAT_EVACUATION  = 0x05,
  CAT_SUPPLY      = 0x06,
  CAT_OTHER       = 0x07,
  CAT_NONE        = 0x00
};

#pragma pack(push, 1)
struct MeshPacket {
  uint8_t  srcId;
  uint8_t  dstId;
  uint8_t  msgType;
  uint16_t seq;
  float    lat;
  float    lon;
  uint8_t  category;
  uint8_t  payloadLen;
  char     payload[64];
  uint16_t crc;
};
#pragma pack(pop)

inline uint16_t crc16(const uint8_t *data, size_t len) {
  uint16_t crc = 0xFFFF;
  for (size_t i = 0; i < len; i++) {
    crc ^= static_cast<uint16_t>(data[i]) << 8;
    for (uint8_t b = 0; b < 8; b++) {
      crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : (crc << 1);
    }
  }
  return crc;
}

inline uint16_t computePacketCrc(const MeshPacket &pkt) {
  size_t crcOffset = offsetof(MeshPacket, crc);
  return crc16(reinterpret_cast<const uint8_t *>(&pkt), crcOffset);
}

class SeenCache {
 public:
  explicit SeenCache(size_t capacity) : cap_(capacity) {
    keys_ = new uint32_t[capacity];
    for (size_t i = 0; i < capacity; i++) keys_[i] = 0;
  }

  bool hasSeen(uint8_t srcId, uint16_t seq) {
    uint32_t key = (static_cast<uint32_t>(srcId) << 16) | seq;
    for (size_t i = 0; i < cap_; i++) {
      if (keys_[i] == key) return true;
    }
    return false;
  }

  void markSeen(uint8_t srcId, uint16_t seq) {
    uint32_t key = (static_cast<uint32_t>(srcId) << 16) | seq;
    keys_[idx_] = key;
    idx_ = (idx_ + 1) % cap_;
  }

 private:
  uint32_t *keys_;
  size_t cap_;
  size_t idx_ = 0;
};
