#include <Wire.h>
#include "Adafruit_VL6180X.h"
#include "FS.h"
#include "SPIFFS.h"
#include "time.h"

#define MOTION_THRESHOLD 100 // Example threshold for motion detection
#define DETECTION_TIME 2000  // 2 seconds of consistent motion
#define RESET_INTERVAL (30 * 24 * 60 * 60) // 30 days in seconds

Adafruit_VL6180X sensor = Adafruit_VL6180X();

const char* filename = "/motion_log.bin";
const char* remindersFile = "/reminders.json";

void setup() {
    Serial.begin(115200);
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    
    if (!sensor.begin()) {
        Serial.println("Failed to initialize VL6180X");
        while (1);
    }

    // Initialize RTC time
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
    }

    checkResetCondition();
}

void loop() {
    static unsigned long motionStart = 0;
    int range = sensor.readRange();
    
    if (range < MOTION_THRESHOLD) { // Motion detected
        if (motionStart == 0) motionStart = millis();
        
        if (millis() - motionStart >= DETECTION_TIME) {
            storeTimestamp();
            motionStart = 0;
        }
    } else {
        motionStart = 0;
    }
    
    delay(100);
}

void storeTimestamp() {
    time_t now = time(NULL);
    File file = SPIFFS.open(filename, FILE_APPEND);
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }
    file.write((uint8_t*)&now, sizeof(time_t));
    file.close();
    Serial.printf("Logged motion event at %ld\n", now);
}

void checkResetCondition() {
    File file = SPIFFS.open(filename, FILE_READ);
    if (!file) return;
    
    time_t firstTimestamp;
    if (file.read((uint8_t*)&firstTimestamp, sizeof(time_t)) > 0) {
        time_t now = time(NULL);
        if (now - firstTimestamp >= RESET_INTERVAL) {
            file.close();
            Serial.println("Resetting motion log due to 30-day limit.");
            SPIFFS.remove(filename);
        }
    }
    file.close();
}
