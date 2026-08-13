# SCADA Multi-Protocol Firmware: Dual-MCU Bench Prototype

Firmware written during an embedded systems internship at Tata Elxsi for a Phase 1 bench prototype of a SCADA (Supervisory Control and Data Acquisition) system, targeting an oil & gas industrial monitoring use case.

## What this is

A dual-MCU architecture pairing an **Adafruit Grand Central M4 Express** (ATSAMD51, 120MHz ARM Cortex-M4) with an **ESP32**, communicating over serial handshake. The Metro M4 side handles direct sensor/GPIO signals; the ESP32 side handles wireless connectivity (Wi-Fi, BLE, MQTT) and bridges sensor state to a broker for remote monitoring.

Across the two boards, this repo implements and bench-validates five protocols hands-on: **I2C, UART, Wi-Fi, BLE, and MQTT**.

**Status: Phase 1 bench-validated prototype.** This was built and tested on a lab bench during the internship, and it was never deployed to a live facility or run in a production environment. Latency was informally observed to be roughly sub-second during bench testing; this was not precisely benchmarked and shouldn't be read as a measured figure.

## File map

| File | Protocol / Role | Description |
|---|---|---|
| `metro_scada_final.ino` | UART, Digital I/O | Metro M4 side: reads a pressure sensor pin, listens for serial commands (e.g. from a connected computer or test harness), and pulses a data pin to signal the ESP32 |
| `esp32_scada_final.ino` | Digital I/O, UART | ESP32 side: reads Metro M4's data pin, drives a status LED, logs over serial |
| `code_for_adafruitm4.ino` | UART | Metro M4 side of a serial handshake, sending sensor data and waiting for ESP32 acknowledgment |
| `code_for_esp32_paired_w_adafruit_m4.ino` | UART | ESP32 side of the handshake, receiving a signal code from the Metro M4 and blinking a status LED per signal type |
| `adafruit_p_high.ino` | I2C | Metro M4 as I2C master, flagging a "pressure high" condition to the ESP32 over I2C and polling for a response |
| `blempu9250.ino` | BLE, I2C | Reads temperature from an MPU9250 IMU (via I2C) and broadcasts it over a BLE characteristic |
| `connect_to_a_wifi.ino` | Wi-Fi | Basic station-mode Wi-Fi connection, followed by a network scan |
| `connect_to_a_wifi_with_rssi.ino` | Wi-Fi | Station-mode connection with static IP configuration, signal strength (RSSI) reporting, and network scan |
| `esp32sta.ino` | Wi-Fi | Minimal station-mode connection test, connects and prints the assigned IP |
| `scan_wifi.ino` | Wi-Fi | Standalone network scanner utility |
| `esp32ws.ino` | Wi-Fi, Web Server | Local browser-based GPIO control panel (two-output toggle UI), dark theme iteration |
| `web_server_esp32.ino` | Wi-Fi, Web Server | Same browser-based GPIO control panel, green/light theme iteration |
| `ledwesp32mqtt.ino` | MQTT | Subscribes to an MQTT topic and toggles an LED based on ON/OFF payloads |
| `mqtt_broker_temp.ino` | MQTT, I2C (DHT) | Reads temperature/humidity from a DHT sensor and publishes it to an MQTT broker as JSON |

## Dependencies

- `WiFi.h`, `PubSubClient`: Wi-Fi and MQTT connectivity (ESP32 core + [PubSubClient](https://github.com/knolleary/pubsubclient))
- `BLEDevice`, `BLEUtils`, `BLEServer`: ESP32 BLE stack (bundled with the ESP32 Arduino core)
- `Wire.h`: I2C (Arduino core)
- `Adafruit_Sensor`, `Adafruit_MPU9250`: sensor abstraction. Note that `Adafruit_MPU9250` here is a **third-party library** (not an official Adafruit product) built to plug into Adafruit's Unified Sensor framework
- `DHT`: DHT11/22 temperature/humidity sensor library (Adafruit)

## Setup

All Wi-Fi and MQTT credentials in this repo are placeholders (`YOUR_SSID`, `YOUR_PASSWORD`, `your_MQTT_USERNAME`, etc.). The original hardware credentials used during bench testing have been scrubbed. Replace these with your own before flashing.

## Known limitations

This is bench-prototype code, not production firmware. A few things worth knowing if you're reading through it:
- Some serial handshakes between the two boards use blocking waits with no timeout or retry logic. Fine for a controlled bench setup, not hardened for field use.
- No persistent error handling or reconnection backoff beyond what's shown above.
- `esp32ws.ino` and `web_server_esp32.ino` are two UI iterations of the same local GPIO control panel, kept both to show the design iteration.

## Background

Built as part of an internship at Tata Elxsi (Industrial Design and Visualization group), under the supervision of Prabu Appunu. All 14 modules were written solo as the sole firmware author on this project.
