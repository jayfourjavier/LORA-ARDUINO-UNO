# LoRa Sensor Node – DHT22 + Soil Moisture

This project is an **Arduino-based LoRa transmitter node** that reads environmental data from a **DHT22 sensor** (temperature and humidity) and a **soil moisture sensor**, then sends the readings wirelessly via a **LoRa module (433 MHz)**.

**Receiver Node:** [LORA-ESP32-CONTROLLER-NODE](https://github.com/jayfourjavier/LORA-ESP32-CONTROLLER-NODE)

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
| GND, 3.3V/5V | Common Power Lines | Shared by all components |

---

## Code Explanation

### Sensor Reading

* **DHT22:** Reads temperature and humidity via the Adafruit DHT library.
* **Soil Moisture:** Analog readings are averaged across several samples for stability.

```cpp
float moisturePercent = map(average, zeroMoisture, hundredMoisture, 0, 100);
```

You can adjust `zeroMoisture` and `hundredMoisture` for sensor calibration.

---

### LoRa Transmission

The data is sent as a comma-separated string for easy parsing:

```cpp
S,<node_id>,<temperature>,<humidity>,<moisture>,E
```

**Example:**

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

Install the following via the **Arduino Library Manager**:

* **LoRa** by Sandeep Mistry
* **DHT sensor library** by Adafruit
* **Adafruit Unified Sensor** (required by the DHT library)

---

## Transmission Interval

Default: **1 second**

```cpp
delay(1000);
```

To reduce power usage, increase the interval:

```cpp
delay(60000); // Send every 60 seconds
```

---

## Calibration Notes

| Variable          | Description                                         | Typical Value |
| ----------------- | --------------------------------------------------- | ------------- |
| `zeroMoisture`    | Analog value when sensor is in dry soil             | 1023          |
| `hundredMoisture` | Analog value when sensor is in wet soil (saturated) | 0             |

If your sensor outputs inverted values, swap the two.

---

## Example Use Case

This transmitter can be paired with a **LoRa receiver node** or **base station** that:

* Receives and parses LoRa messages
* Displays data on an LCD, serial monitor, or sends to a web dashboard

See companion project:
[LORA-ESP32-CONTROLLER-NODE](https://github.com/jayfourjavier/LORA-ESP32-CONTROLLER-NODE)

---

## License

**MIT License © 2025**
You are free to use, modify, and distribute with attribution.

---

## Author

**Jay Four Javier**
Prototype Fabricator · Systems Developer
