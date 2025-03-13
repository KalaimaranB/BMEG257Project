/**
 * @file HelperFunctions.cpp
 * @brief Contains utility functions for temperature monitoring, including reading sensor values,
 *        converting to temperature, and handling warnings.
 * 
 * This file provides helper functions to:
 * - Read voltage from a sensor pin.
 * - Convert sensor voltage to temperature.
 * - Check if a temperature value is within range.
 * - Send warning signals via Serial and LED.
 * - Handle sensor initialization failures.
 */


#include <Arduino.h>  // Required for analogRead, digitalWrite, and Serial

/**
 * @brief Reads voltage from an analog sensor pin.
 * 
 * This function reads an analog value (0-1023) from a specified pin and returns
 * the raw ADC value. The caller is responsible for converting it to voltage or temperature.
 * 
 * @param pinNumber The analog pin from which to read (e.g., A0).
 * @return float The raw ADC value (range: 0-1023).
 * 
 * @note This function simulates sensor reading. Replace with actual sensor logic if needed.
 */
float readVoltage(int pinNumber) {
    return (analogRead(pinNumber) / 1023.0) * 5.0;  // Convert ADC to voltage 
}

/**
 * @brief Sends a warning if the temperature is out of range.
 * 
 * This function prints a warning message and blinks the built-in LED to alert the user.
 * 
 * @param temperature The temperature value that triggered the warning.
 * @param LED_BUILTIN The built-in LED pin to use for blinking.
 * 
 * @sideeffect Prints a warning to Serial Monitor and blinks the LED.
 * 
 * @note The LED blinks twice for 500ms each to indicate an out-of-range temperature.
 */
void sendWarning(float temperature, int LED_BUILTIN) {
    Serial.print("WARNING: Temperature ");
    Serial.print(temperature, 2);
    Serial.println("°C is out of range!");

    // Blink built-in LED as a visual alert
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}

/**
 * @brief Calculates output voltage
 * 
 * This function calculates the output voltage given R1, R2, and the
 * input voltage.
 * 
 * @param v_in The input voltage in volts.
 * @param r2 The resistance of R2 in ohms.
 * @param r1 The resistance of R1 in ohms.
 * @return v_out The output voltage in volts.
 */
double calculate_v_out(double v_in, double r2, double r1) {

    // Declare v_out
    double v_out;
    
    // Calculate v_out using the formula from the circuits assignment
    v_out = -(v_in * (r1 - 2 * r2)) / (3 * (r1 + r2));

    // Output the result
    printf("The value of v_out is: %lf\n", v_out);

    return v_out;
}

/**
 * @brief Checks if a given temperature is within a safe range.
 * 
 * This function verifies whether a temperature value is within the specified
 * minimum and maximum threshold.
 * 
 * @param integ_temp The temperature value to check.
 * @param min The minimum acceptable temperature.
 * @param max The maximum acceptable temperature.
 * @return bool True if temperature is within range, otherwise false.
 */
bool inRange(float integ_temp, float min, float max) {
    return (integ_temp > min && integ_temp < max);
}

/**
 * @brief Converts a raw ADC sensor reading to temperature in Celsius.
 * 
 * The function first converts the ADC value (0-1023) into a voltage, assuming a 5V system.
 * Then, it applies a conversion formula to estimate the temperature in Celsius.
 * 
 * @param analogValue The raw ADC value from the temperature sensor (range: 0-1023).
 * @return float The calculated temperature in degrees Celsius.
 * 
 * @note The formula assumes:
 *       - Sensor outputs 0.5V at 0°C.
 *       - Sensor sensitivity is 10mV/°C.
 *       - Modify the equation if using a different sensor.
 */
float voltageToTemperature(int analogValue) {
    float voltage = (analogValue / 1023.0) * 5.0;  // Convert ADC value to voltage
    float r_2 = ((voltage/9 + (1/3)) * 300000) / (1 - (voltage/9 + (1/3)));
    float temperature = (voltage - 0.5) * 100.0;   // Convert voltage to temperature
    return temperature;
}
