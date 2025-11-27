#include "PowerReceiver.h"
#define THRESHOLD_VOLTAGE 5.5
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

  // IDLE STATE
  if (batteryVoltage == 0) {
    Serial.println("No battery detected.");
    digitalWrite(ALERT_LED_PIN, LOW);
    return;
  }

  // CHARGING STATE
  if (chargeStatus == "Charging") {
    Serial.println("Battery is charging...");
    checkPowerRange(receivedPower);

    // Overtemperature check
    if (thermistorVoltage > THRESHOLD_VOLTAGE) {
      Serial.println("Temperature Alert: Overheating!");
      digitalWrite(ALERT_LED_PIN, HIGH);
    } else {
      digitalWrite(ALERT_LED_PIN, LOW);
    }
  }

  // FULLY CHARGED STATE
  if (chargeStatus == "Not Charging / Charge Complete") {
    Serial.println("Battery is fully charged.");
    digitalWrite(ALERT_LED_PIN, LOW);
  }

  // SERIAL OUTPUT
  Serial.print("Battery Voltage: ");
  Serial.println(batteryVoltage);

  Serial.print("Thermistor Voltage: ");
  Serial.println(thermistorVoltage);

  Serial.print("Received Power: ");
  Serial.println(receivedPower);
  
  delay(1000);
}
