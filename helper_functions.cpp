#include <stdio.h>
#include <stdbool.h>

// Code was created with the help of Gemini. Prompt: "write me functions in C to initialize and
// code a temperature sensor device that sends warnings when the temperature measured is out of
// range". Parts of the generated code was used as inspiration while others were copied and modified.

// Simulated temperature sensor hardware (replace with actual hardware interaction)
#define MIN_TEMP 15.0 // Minimum acceptable temperature in Celsius
#define MAX_TEMP 30.0 // Maximum acceptable temperature in Celsius

// Simulated sensor reading function (replace with actual hardware read)
float readTemperature(int Pin) {
    return analogRead(Pin);
}

// Simulated warning function (replace with actual warning mechanism)
void sendWarning(float temperature) {
    fprintf(stderr, "WARNING: Temperature %.2f°C is out of range!\n", temperature);
}

// Threshold function that checks if integrated temperature is above threshold
bool inThreshold( float integ_temp, float min, float max ) {
  return ( integ_temp > min && integ_temp < max);
}

// Check temperature and send warning if out of range
void checkTemperature() {
    float temperature = readTemperature();
    printf("Current temperature: %.2f°C\n", temperature);

    if (temperature < MIN_TEMP || temperature > MAX_TEMP) {
        sendWarning(temperature);
    }
}

int main() {
    if (initTemperatureSensor()) {
        printf("Temperature sensor initialized successfully.\n");

        // Simulate continuous temperature monitoring
        for (int i = 0; i < 20; ++i) { //check 20 times for testing.
            checkTemperature();
            // Add a delay here if needed (e.g., using sleep() or a timer)
            // sleep(1); // sleep for 1 second.
        }

    } else {
        fprintf(stderr, "Error: Failed to initialize temperature sensor.\n");
        return 1;
    }

    return 0;
}
