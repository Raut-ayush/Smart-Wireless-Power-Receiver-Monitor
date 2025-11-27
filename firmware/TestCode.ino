#include "PowerReceiver.h"

// Constants for ESP32 (same as header file)
const float VOLTAGE_DIVIDER_RATIO = 2.0;

void setup() {
    initializePins();                  // Initialize all pins
    Serial.begin(115200);              // Use higher baud rate for ESP32
    Serial.println("ESP32 Power Receiver Test Initialized");
}

void loop() {
    float batteryVoltage = readBatteryVoltage();
    float thermistorVoltage = readThermistorVoltage();
    String chargeStatus = getChargeStatus();
    float receivedPower = calculatePower(batteryVoltage);

    checkPowerRange(receivedPower);    // Check if power is in range

    Serial.println("============================");
    Serial.print("Battery Voltage: ");
    Serial.print(batteryVoltage);
    Serial.println(" V");

    Serial.print("Thermistor Voltage: ");
    Serial.print(thermistorVoltage);
    Serial.println(" V");

    Serial.print("Charge Status: ");
    Serial.println(chargeStatus);

    Serial.print("Received Power: ");
    Serial.print(receivedPower);
    Serial.println(" W");
    Serial.println("============================");

    delay(1000); // Wait for 1 second
}
