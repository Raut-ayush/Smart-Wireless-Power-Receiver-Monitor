#include "PowerReceiver.h"

// Initialize all pins
void initializePins() {
    pinMode(BATTERY_VOLTAGE_PIN, INPUT);   // Battery voltage ADC pin
    pinMode(THERMISTOR_PIN, INPUT);        // Thermistor ADC pin
    pinMode(CHARGE_STATUS_PIN, INPUT);     // Charge status digital pin
    pinMode(ALERT_LED_PIN, OUTPUT);        // Alert LED pin
    digitalWrite(ALERT_LED_PIN, LOW);      // Ensure LED is off initially
}

// Read the battery voltage through the ADC
float readBatteryVoltage() {
    int batteryADC = analogRead(BATTERY_VOLTAGE_PIN);
    return (batteryADC * ADC_REFERENCE_VOLTAGE / ADC_RESOLUTION) * VOLTAGE_DIVIDER_RATIO;
}

// Read the thermistor voltage through the ADC
float readThermistorVoltage() {
    int thermistorADC = analogRead(THERMISTOR_PIN);
    return thermistorADC * ADC_REFERENCE_VOLTAGE / ADC_RESOLUTION;
}

// Get the charge status from the CHG pin
String getChargeStatus() {
    int chargeStatus = digitalRead(CHARGE_STATUS_PIN);
    if (chargeStatus == LOW) {
        return "Charging";
    } else {
        return "Not Charging / Charge Complete";
    }
}

// Calculate the power based on voltage (placeholder for full calculation)
float calculatePower(float voltage) {
    // Placeholder logic; replace with full voltage-current power calculation if current data is available
    return voltage;
}

// Check if the power is within the specified range and handle alerts
void checkPowerRange(float power) {
    if (power < MIN_POWER || power > MAX_POWER) {
        digitalWrite(ALERT_LED_PIN, HIGH); // Trigger alert
        Serial.println("Power Alert: Out of Range!");
    } else {
        digitalWrite(ALERT_LED_PIN, LOW); // Clear alert
    }
}
