# LoRa Sensor Node – DHT22 + Soil Moisture

This project is an **Arduino-based LoRa transmitter node** that reads environmental data from a **DHT22 sensor** (temperature and humidity) and a **soil moisture sensor**, then sends the readings wirelessly via a **LoRa module (433 MHz)**.

---

## Overview

The sensor node performs the following:

1. Reads **temperature** and **humidity** using a DHT22 sensor.
2. Reads and averages **soil moisture** data from an analog sensor.
3. Formats the readings into a LoRa message string:

   ```
   S,<sensorNodeId>,<temperature>,<humidity>,<moisture>,E
   ```

4. Transmits the message every second over LoRa.

---

## Hardware Requirements

| Component              | Description                              |
| ---------------------- | ---------------------------------------- |
| Arduino (UNO/Nano/etc) | Main microcontroller board               |
| LoRa Module (433 MHz)  | SX1278 or RFM95 module for communication |
| DHT22 Sensor           | Measures temperature and humidity        |
| Soil Moisture Sensor   | Analog resistive or capacitive type      |
| Jumper Wires           | For connections                          |
| Breadboard (optional)  | For prototyping                          |

---

## Pin Connections

| Arduino Pin  | Sensor / Module    | Description              |
| ------------ | ------------------ | ------------------------ |
| D4           | DHT22              | Data pin                 |
| A0           | Soil Moisture      | Analog output            |
| 10           | LoRa NSS (CS)      | Chip select              |
| 11           | LoRa MOSI          | SPI MOSI                 |
| 12           | LoRa MISO          | SPI MISO                 |
| 13           | LoRa SCK           | SPI Clock                |
| 9            | LoRa RST           | LoRa module Reset Pin    |
| 2            | LoRa DI00          | LoRa module DI00 Pin     |
| GND, 3.3V/5V | Common Power Lines | Shared by all components |

> **Note:** Most LoRa modules are **3.3V** devices. Use a **logic level shifter** if using a 5V Arduino.

---

## Code Explanation

### Sensor Reading

* **DHT22:** Temperature and humidity are read via the DHT library.
* **Soil Moisture:** Analog readings are averaged over `moistureSampleCount` samples for stability.

```cpp
float moisturePercent = map(average, zeroMoisture, hundredMoisture, 0, 100);
```

You can adjust `zeroMoisture` and `hundredMoisture` to calibrate based on your soil sensor.

---

### LoRa Transmission

The message is sent in a CSV format for easy parsing on the receiver side:

```cpp
S,<node_id>,<temperature>,<humidity>,<moisture>,E
```

Example:

```
S,3,29.40,63.20,45.00,E
```

---

### Serial Monitor Output

```
Temperature: 29.40 °C | Humidity: 63.20 % | Soil Moisture: 45.00 % | LoRa Msg: S,3,29.40,63.20,45.00,E
```

---

## Library Dependencies

Install these libraries via **Arduino Library Manager**:

* **LoRa** by Sandeep Mistry
* **DHT sensor library** by Adafruit
* **Adafruit Unified Sensor** (dependency for DHT library)

---

## Transmission Interval

Currently set to transmit every **1 second**:

```cpp
delay(1000);
```

You can modify this to a longer interval to save power, e.g.:

```cpp
delay(60000); // Send every 60 seconds
```

---

## Calibration Notes

* `zeroMoisture` = sensor value in **dry air** (≈1023 for most analog sensors).
* `hundredMoisture` = sensor value in **water-saturated soil** (≈0).
* Reverse these if your sensor outputs inverted values.

---

## Example Use Case

This transmitter can be paired with a **LoRa receiver node** or a **base station** that:

* Receives and parses LoRa messages
* Displays data on an LCD, Serial Monitor, or sends it to a web dashboard

---

## License

MIT License © 2025 — You are free to use, modify, and distribute with attribution.

---

## Author

**Jay Four Javier**

Prototype Fabricator, Systems Developer
