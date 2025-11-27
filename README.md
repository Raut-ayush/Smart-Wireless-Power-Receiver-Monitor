# 🔋 Smart Wireless Power Receiver Monitor (ESP32 + BQ51050B)

Firmware + hardware design for a **Qi-based wireless power receiver** using the **BQ51050B** IC and an **ESP32** microcontroller.

The system:

- Receives wireless power (5–15 W range)  
- Charges a single-cell Li-ion battery via BQ51050B  
- Monitors **battery voltage, temperature, and charge status**  
- Computes a simple **received power estimate**  
- Raises **alerts (LED + serial logs)** when power/temperature go out of range  

---

## 🧾 Overview

This project implements a **wireless power receiver monitoring system** built around:

- **Wireless power receiver IC**: TI **BQ51050B** (Qi-compatible, integrated Li-ion charger)  
- **MCU**: **ESP32-WROOM** module using the Arduino framework  
- **Power range**: 5 W – 15 W (configurable thresholds)  

The ESP32 continuously monitors:

- Battery voltage (via ADC + resistor divider)  
- Thermistor voltage (for temperature monitoring)  
- Charge status pin from BQ51050B (charging / complete / fault)  
- Estimated received power (simple voltage-based computation)

It then classifies system behaviour (normal, out-of-range, overheating) and raises alerts via:

- An **alert LED**  
- **Serial logs** for debugging and analysis  

---

## ✅ Features

- **Battery Voltage Monitoring**
  - Uses ESP32 ADC and a calibrated voltage divider.
  - Converts raw ADC counts to real battery voltage (in Volts).

- **Temperature Monitoring via Thermistor**
  - Reads thermistor voltage.
  - Compares against a threshold to detect **overtemperature** conditions.

- **Charge Status Monitoring**
  - Reads digital CHG/status pin of the receiver IC.
  - Distinguishes between:
    - Charging
    - Not charging / charge complete
    - Fault (depending on how BQ51050B status is wired)

- **Received Power Estimation**
  - Simple function `calculatePower()` that uses voltage as a proxy.
  - Can be extended later with current sensing.

- **Power Range Alerting**
  - Uses `MIN_POWER` and `MAX_POWER` to define acceptable range.
  - Raises alerts if out of range via:
    - LED
    - Serial print: `"Power Alert: Out of Range!"`

- **Modular Driver + Application Logic**
  - **`PowerReceiver.cpp/h`** implement a reusable driver layer.
  - **`ControlLogic.ino`** implements system-level logic and state handling.
  - **`TestCode.ino`** used for bring-up and basic validation.

---

## 🧱 System Architecture

At a high level:

1. Qi transmitter sends wireless power to the receiver coil.  
2. **BQ51050B** rectifies RF power into DC and manages Li-ion charging.  
3. Important analog/digital nodes are routed to the **ESP32**:
   - Battery voltage
   - Thermistor voltage
   - CHG / status pin
4. ESP32 firmware:
   - Samples ADC values
   - Computes useful quantities (voltage, power)
   - Checks thresholds (undervoltage, overtemperature, power range)
   - Logs everything over serial
   - Drives an alert LED on fault conditions


