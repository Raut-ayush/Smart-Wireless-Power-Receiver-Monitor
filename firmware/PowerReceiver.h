#ifndef POWER_RECEIVER_H
#define POWER_RECEIVER_H

#include <Arduino.h>

// Pin Definitions for ESP32
#define BATTERY_VOLTAGE_PIN 36  // GPIO36 (ADC1_CHANNEL_0)
#define THERMISTOR_PIN 39       // GPIO39 (ADC1_CHANNEL_3)
#define CHARGE_STATUS_PIN 33    // GPIO33 (Digital Input for CHG)
#define ALERT_LED_PIN 2         // GPIO2 (Digital Output for LED)

// Constants for ADC calibration
const float VOLTAGE_DIVIDER_RATIO = 2.0;  // Adjust based on your resistor values
const float ADC_REFERENCE_VOLTAGE = 3.3; // ESP32 ADC reference voltage
const int ADC_RESOLUTION = 4096;         // 12-bit ADC resolution

// Power range limits
const float MIN_POWER = 5.0;  // Minimum power in watts
const float MAX_POWER = 15.0; // Maximum power in watts

// Function Prototypes
void initializePins();
float readBatteryVoltage();
float readThermistorVoltage();
String getChargeStatus();
float calculatePower(float voltage);
void checkPowerRange(float power);

#endif
