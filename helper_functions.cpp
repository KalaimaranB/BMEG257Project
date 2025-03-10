#include <stdio.h>
#include <stdbool.h>

// Code was created with the help of Gemini. Prompt: "write me functions in C to initialize and
// code a temperature sensor device that sends warnings when the temperature measured is out of
// range". Parts of the generated code was used as inspiration while others were copied and modified.

// Simulated temperature sensor hardware (replace with actual hardware interaction)
#define MIN_TEMP 15.0 // Minimum acceptable temperature in Celsius
#define MAX_TEMP 30.0 // Maximum acceptable temperature in Celsius

// Simulated sensor reading function (replace with actual hardware read)
float readTemperature() {
    // Simulate reading a temperature (replace with actual hardware read)
    // For testing, generate a random temperature within a range, then sometimes outside.
    static int count = 0;
    float temp;

    if (count % 5 == 0) { // simulate out of range every 5 reads
        temp = (float)(rand() % 50) - 10.0; // generate temp from -10 to 40
    } else {
        temp = (float)(rand() % 20) + 15.0; // generate temp from 15 to 35, usually in range.
    }
    count++;

    return temp;
}

// Simulated warning function (replace with actual warning mechanism)
void sendWarning(float temperature) {
    fprintf(stderr, "WARNING: Temperature %.2f°C is out of range!\n", temperature);
}

// Initialize the temperature sensor (replace with actual hardware initialization)
bool initTemperatureSensor() {
    // Simulate sensor initialization (replace with actual hardware initialization)
    printf("Initializing temperature sensor...\n");
    // In actual implementation, this would involve setting up GPIO pins,
    // configuring communication protocols (e.g., I2C, SPI), etc.
    // For now, just return true to indicate success.
    srand(time(NULL)); //seed rand for testing.
    return true;
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
