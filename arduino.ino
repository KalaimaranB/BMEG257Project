/**
 * Arduino Temperature Monitoring System
 * 
 * This script reads temperature from an analog sensor connected to A0,
 * compares it against a safe range, and alerts the user if it goes out of range.
 * 
 * Features:
 * - Reads temperature from an analog input.
 * - Converts sensor voltage to temperature using a predefined formula.
 * - Uses the built-in LED (LED_BUILTIN) to indicate warnings when temperature is out of range.
 * - Continuously checks temperature every second.
 * - Sends temperature readings and warnings via Serial Monitor.
 * 
 * Hardware:
 * - Temperature sensor connected to A0 (analog input).
 * - Built-in LED blinks when temperature is out of range.
 * 
 * Dependencies:
 * - Uses "HelperFunctions.h" for sensor initialization and warning messages.
 * Sourced and edited with chatgpt from: https://chatgpt.com/share/67d2f3ba-71fc-8006-a85b-afa9db975de6
 */

#include <Arduino.h>
#include "HelperFunctions.h"  // Include helper functions for initialization and warnings

// Define the analog pin for temperature sensor input
#define TEMP_SENSOR_PIN A0
// Minimum & maximal acceptable temperature in Celsius
#define MIN_TEMP 15.0 
#define MAX_TEMP 30.0 
// Define tracker if sensor is working
int safeSensor = 0;

/**
 * @brief Sets up the Arduino and initializes components.
 * 
 * This function initializes serial communication, sets up the sensor input pin,
 * and configures the built-in LED as an output. It also calls the helper function
 * to initialize the temperature sensor.
 * 
 * @sideeffect Enables Serial communication.
 * @sideeffect Configures the built-in LED for output.
 * 
 * @note If sensor initialization fails, an error message is printed to the Serial Monitor.
 */
void setup() {
    Serial.begin(9600);  // Start serial communication at 9600 baud
    pinMode(TEMP_SENSOR_PIN, INPUT);  // Set temperature sensor pin as input
    pinMode(LED_BUILTIN, OUTPUT);  // Configure built-in LED as output

    if (initTemperatureSensor()) {
        Serial.println("Temperature sensor initialized successfully.");
	safeSensor=1; // Inform program sensor has been set properly. 
    } 
    else {
	Serial.println("Failed to initialize temperature sensor!");
	safeSensor = 0;
	sendFailedSetupWarning(LED_BUILTIN);
   }

}

/**
 * @brief Continuously reads temperature and checks for out-of-range conditions.
 * 
 * This function:
 * - Reads the raw temperature sensor value from the analog pin.
 * - Converts it to temperature in Celsius.
 * - Prints the temperature to the Serial Monitor.
 * - Checks if the temperature is outside the safe range.
 * - If out of range, it calls `sendWarning()` from HelperFunctions.h and blinks the LED.
 * 
 * @sideeffect Blinks the built-in LED when the temperature is out of range.
 * @sideeffect Prints temperature readings to Serial Monitor.
 * @sideeffect Calls `sendWarning()` when temperature exceeds safe limits.
 * 
 * @note The function loops indefinitely, reading temperature every second.
 */
void loop() {
    if (safeSensor == 1){
        int sensorValue = readVoltage(TEMP_SENSOR_PIN);  // Read sensor data from A0
        float temperature = voltageToTemperature(sensorValue);  // Convert raw value to temperature

        Serial.print("Current Temperature: ");
        Serial.print(temperature);
        Serial.println("°C");

        // Check if temperature is out of the predefined safe range
        if (inRange(temperature, MIN_TEMP, MAX_TEMP)) {
            sendWarning(temperature, LED_BUILTIN);  // Trigger warning via HelperFunctions.h
        }

        delay(1000);  // Wait 1 second before taking the next reading
    }
    else{
	sendFailedSetupWarning(LED_BUILTIN);
    }
}
