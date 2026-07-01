<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0EA5E9,50:8B5CF6,100:EC4899&height=200&section=header&text=LankaMesh%20|%20Offline%20Disaster%20Communication&fontSize=32&fontColor=ffffff&animation=fadeIn&fontAlignY=38&desc=ESP32%20%2B%20LoRa%20%2B%20GPS%20%2B%20Flutter&descAlignY=58&descSize=16" width="100%"/>

<img src="https://readme-typing-svg.demolab.com/?font=Fira+Code&weight=600&size=22&duration=3000&pause=800&color=38BDF8&center=true&vCenter=true&width=700&lines=Resilient+Mesh+Networking;Offline+Emergency+Communication;Built+for+Disaster+Response" alt="Typing SVG" />

<br/>

[![Live Demo](https://img.shields.io/badge/🌐_Project-Overview-8B5CF6?style=for-the-badge&labelColor=111827)](https://github.com)
![ESP32](https://img.shields.io/badge/ESP32-S3-1E293B?style=for-the-badge&logo=espressif&logoColor=white)
![LoRa](https://img.shields.io/badge/LoRa-Wireless-0EA5E9?style=for-the-badge)
![Flutter](https://img.shields.io/badge/Flutter-Mobile-02569B?style=for-the-badge&logo=flutter&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

</div>

<img src="https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.gif" width="100%">

> A resilient, offline-capable disaster communication system built for emergency response, remote coordination, and community safety.

## ✨ What is LankaMesh?

LankaMesh is an intelligent mesh communication platform designed for disaster-prone environments where traditional networks may fail. It combines an ESP32-based hardware node, LoRa long-range radio communication, GPS positioning, environmental sensing, and a Flutter mobile companion app to provide:

- 🚨 Emergency SOS alerts
- 📍 Live location sharing
- 🌦️ Environmental sensor monitoring
- 📡 Offline peer-to-peer messaging
- 📱 A clean mobile dashboard for monitoring and response

This project is built to support early warning, coordination, and safe communication when connectivity is weak or unavailable.

---

## 🚀 Key Features

### Hardware Intelligence
- ESP32-based node with LoRa radio
- GPS module for positioning
- DHT22 sensor for temperature and humidity
- OLED display for local status feedback
- SOS button for fast emergency triggering

### Communication Layer
- Long-range LoRa packet exchange
- Mesh-style message relay logic
- Packet CRC validation and duplicate suppression
- Broadcast and targeted messaging support

### Mobile Experience
- Flutter app for monitoring node activity
- Simple and modern control interface
- Emergency status simulation and live status updates

---

## 🧠 Project Architecture

```text
[ ESP32 Node ] --LoRa--> [ Nearby Nodes ]
      |                     |
      |                     |
   GPS + Sensor         Mobile App
      |                     |
   OLED Display         Dashboard / Alerts
```

The system is organized into two main parts:

1. Firmware layer
   - Runs on the ESP32 board
   - Handles sensors, GPS, LoRa communication, and display output

2. Mobile app layer
   - Runs on Android/iOS through Flutter
   - Provides a user-friendly monitoring interface

---

## 📁 Project Structure

- [firmware](firmware) — ESP32 firmware using PlatformIO
  - [firmware/include](firmware/include) — configuration and handler headers
  - [firmware/src/main.cpp](firmware/src/main.cpp) — main firmware logic
- [mobile_app](mobile_app) — Flutter companion app
  - [mobile_app/lib/main.dart](mobile_app/lib/main.dart) — app UI and logic
  - [mobile_app/pubspec.yaml](mobile_app/pubspec.yaml) — app dependencies
- [README.md](README.md) — project documentation

---

## 🔧 Hardware Used

- ESP32 development board
- LoRa module (RA-02 / SX1276 compatible)
- GPS module
- DHT22 sensor
- SSD1306 OLED display
- Push button for SOS trigger

---

## 🛠️ Getting Started

### 1) Firmware setup

Open the [firmware](firmware) folder in VS Code with PlatformIO installed.

Build and upload the firmware to your ESP32 board.

### 2) Mobile app setup

```bash
cd mobile_app
flutter pub get
flutter run
```

### 3) Customize your node

Update settings such as:
- node ID
- LoRa frequency and power
- GPS pins
- sensor and display pins

in [firmware/include/config.h](firmware/include/config.h).

---

## 📦 What this project demonstrates

- Embedded systems design with Arduino/ESP32
- Low-power wireless communication using LoRa
- Real-time telemetry and event handling
- Mobile application development with Flutter
- Practical disaster-response technology concepts

---

## 🌟 Future Improvements

- Bluetooth or Wi-Fi bridge for mobile pairing
- Offline map visualization
- Message history and log storage
- Multi-node mesh routing optimization
- Battery monitoring and power-saving modes

---

## 🤝 Contributing

Contributions are welcome. If you want to improve the firmware, expand the mobile app, or add new communication features, feel free to open an issue or submit a pull request.

---

## 📌 Summary

LankaMesh is more than a prototype — it is a practical foundation for dependable communication during emergencies, especially in areas with limited or damaged infrastructure.

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:F472B6,50:9333EA,100:6D28D9&height=100&section=footer" width="100%"/>


