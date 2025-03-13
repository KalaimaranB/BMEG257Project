/**
 * @file HelperFunctions.h
 * @brief Contains utility function declarations for temperature monitoring.
 */

#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <Arduino.h>  // Required for analogRead, digitalWrite, and Serial

// Reads voltage from an analog sensor pin.
float readVoltage(int pinNumber);

// Sends a warning if the temperature is out of range.
void sendWarning(float temperature, int LED_BUILTIN);

// Sends a long blink warning for sensor initialization failure.
void sendFailedSetupWarning(int LED_BUILTIN);

// Checks if a given temperature is within a safe range.
bool inRange(float integ_temp, float min, float max);

// Converts a raw ADC sensor reading to temperature in Celsius.
float voltageToTemperature(int analogValue);

// Initializes the temperature sensor (returns true if successful).
bool initTemperatureSensor();

#endif // HELPER_FUNCTIONS_H
