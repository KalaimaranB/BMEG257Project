/*
* HelperFunctions.h
*
* This file contains useful function structure functions for the arduino
*/

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

void Audible( bool thresh_pass, int pin_number );

// Light function that will turn on the LED light if threshold is achieved.
void LightIndic( bool thresh_pass, int pin_number );

// Function to read the temperature from the sensor
float readTemperature();

// Function to send warning signal to user that temperature is outside range
void sendWarning(float temperature);

// Function to check if temperature is within range and send warning otherwise
void checkTemperature();

// Function to initialize the temperature sensor with proper values
bool initTemepratureSensor();

#endif // HELPERFUNCTIONS_H
