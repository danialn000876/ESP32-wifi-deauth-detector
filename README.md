# ESP32 Wi-Fi Deauth Detector & IDS (Project #3)

A lightweight, passive intrusion detection system (IDS) built on an ESP32 development board. This project monitors local wireless traffic in real-time to detect potential Wi-Fi deauthentication attacks and management frame anomalies.

## Features
- **Passive Monitoring:** Utilizes ESP32 promiscuous mode to sniff 802.11 management frames without connecting to access points.
- **Real-Time Analysis:** Tracks management packets per second via Serial Monitor (`115200 baud`).
- **Hardware Agnostic / Minimal Setup:** Requires only an ESP32 board connected via USB—no external peripherals or buzzers needed.

## Usage
1. Open the sketch in Arduino IDE.
2. Select your ESP32 board and COM port.
3. Upload the code and open the Serial Monitor at `115200 baud`.
