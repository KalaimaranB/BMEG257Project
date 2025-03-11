#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <nlohmann/json.hpp>  // JSON Library: https://github.com/nlohmann/json

using json = nlohmann::json;
using namespace std;

// Mock function to display text (replace with OLED display function)
void displayMessage(const string &message) {
    cout << "Displaying on OLED: " << message << endl;
}

// Mock function to set a pixel color on the OLED
void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    cout << "Setting pixel (" << x << "," << y << ") to RGB("
         << (int)r << "," << (int)g << "," << (int)b << ")" << endl;
}

// Function to read reminders from JSON file
vector<string> readReminders(const string &filename) {
    vector<string> reminders;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Unable to open " << filename << endl;
        return reminders;
    }

    json data;
    file >> data;
    file.close();

    if (data.contains("reminders")) {
        for (const auto &timeStr : data["reminders"]) {
            reminders.push_back(timeStr);
        }
    }

    return reminders;
}

// Function to check if the current time matches any reminder
bool isReminderTime(const vector<string> &reminders) {
    time_t now = time(nullptr);
    struct tm *currentTime = localtime(&now);
    
    char currentTimeStr[20];
    strftime(currentTimeStr, sizeof(currentTimeStr), "%Y-%m-%dT%H:%M:%S", currentTime);

    for (const string &reminder : reminders) {
        if (reminder == currentTimeStr) {
            return true;
        }
    }

    return false;
}

int main() {
    string filename = "remind.json";
    vector<string> reminders = readReminders(filename);

    if (reminders.empty()) {
        cerr << "No reminders found in " << filename << endl;
        return 1;
    }

    while (true) {
        if (isReminderTime(reminders)) {
            displayMessage("Medication Time!");
            
            // Example: Highlight specific pixels in RED
            for (int x = 10; x < 30; x++) {
                for (int y = 10; y < 30; y++) {
                    setPixel(x, y, 255, 0, 0);  // Red color
                }
            }
        }

        // Sleep for 1 minute before checking again
        this_thread::sleep_for(chrono::minutes(1));
    }

    return 0;
}
