#include <Arduino.h>
#include <BluetoothSerial.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

BluetoothSerial SerialBT;  // Create Bluetooth Serial object
const char* filename = "/reminders.json";  // Path for JSON file in SPIFFS

// Timeout settings
const unsigned long SEARCH_TIME = 2 * 60 * 1000; // 2 minutes in milliseconds
unsigned long startTime;

// Function prototypes
bool writeFile(const char* path, String content);
String readFile(const char* path);
bool fileExists(const char* path);

void setup() {
    Serial.begin(115200); // Start serial monitor
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed!");
        return;
    }

    Serial.println("Starting Bluetooth...");
    SerialBT.begin("ESP32_Reminder_Device");  // Set Bluetooth device name

    startTime = millis(); // Record start time

    Serial.println("Waiting for Bluetooth connection...");
    while (millis() - startTime < SEARCH_TIME) {  
        if (SerialBT.available()) {  // Check if data is received
            Serial.println("Receiving data...");
            String jsonData;
            while (SerialBT.available()) {
                char c = SerialBT.read();
                jsonData += c;
            }
            Serial.println("Data received, saving to file...");
            
            if (writeFile(filename, jsonData)) {
                Serial.println("File saved successfully!");
            } else {
                Serial.println("Failed to save file!");
            }
            break;  // Exit loop once data is received
        }
    }

    // Handle timeout
    if (millis() - startTime >= SEARCH_TIME) {
        Serial.println("Timeout reached, checking if file exists...");
        if (!fileExists(filename)) {
            Serial.println("No reminders found. Powering off...");
            esp_deep_sleep_start();  // Put ESP32 into deep sleep mode
        } else {
            Serial.println("Reminders exist, continuing normal operation.");
        }
    }
}

void loop() {
    // Main loop will run indefinitely after Bluetooth check
    Serial.println("ESP32 is running. Press reset to restart Bluetooth search.");
    delay(5000);  // Delay to avoid spamming Serial Monitor
}

// Function to write data to SPIFFS
bool writeFile(const char* path, String content) {
    File file = SPIFFS.open(path, FILE_WRITE);
    if (!file) {
        Serial.println("Failed to open file for writing");
        return false;
    }
    file.print(content);
    file.close();
    return true;
}

// Function to read data from SPIFFS
String readFile(const char* path) {
    if (!SPIFFS.exists(path)) {
        Serial.println("File not found!");
        return "";
    }
    File file = SPIFFS.open(path, FILE_READ);
    String content;
    while (file.available()) {
        content += (char)file.read();
    }
    file.close();
    return content;
}

// Function to check if file exists
bool fileExists(const char* path) {
    return SPIFFS.exists(path);
}
