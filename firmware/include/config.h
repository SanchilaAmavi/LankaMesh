#pragma once

#include <Arduino.h>
#include <DHT.h>

// LoRa RA-02 (SX1276)
#define LORA_SCK      12
#define LORA_MISO     13
#define LORA_MOSI     11
#define LORA_CS       10
#define LORA_RST      9
#define LORA_DIO0     8

#define LORA_FREQUENCY   433E6
#define LORA_BANDWIDTH   125E3
#define LORA_SPREADING   10
#define LORA_CODING_RATE 5
#define LORA_TX_POWER    20

// GPS UART
#define GPS_RX_PIN    17
#define GPS_TX_PIN    18
#define GPS_BAUD      9600

// OLED (I2C)
#define OLED_SDA      21
#define OLED_SCL      22
#define OLED_ADDR     0x3C
#define OLED_WIDTH    128
#define OLED_HEIGHT   64

// DHT22 sensor
#define DHT_PIN       4
#define DHT_TYPE      DHT22

// SOS button
#define SOS_BUTTON_PIN 0
#define SOS_DEBOUNCE_MS 300

// Battery
#define BATTERY_ADC_PIN 1
#define BATTERY_FULL_MV 4200
#define BATTERY_EMPTY_MV 3300

// Timing
#define GPS_BROADCAST_INTERVAL_MS   15000UL
#define SENSOR_READ_INTERVAL_MS     10000UL
#define DISPLAY_REFRESH_INTERVAL_MS 1000UL
#define RELAY_BACKOFF_MIN_MS        100
#define RELAY_BACKOFF_MAX_MS        400
#define SEEN_CACHE_SIZE             64

// Node identity
#define NODE_ID  1

// Serial to mobile app
#define APP_SERIAL_BAUD 115200
