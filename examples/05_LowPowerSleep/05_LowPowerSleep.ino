// Example: Low Power Sleep for I2Connect: KXTJ3-1057
// Last Update: August 6, 2026
// Support: http://ptsolns.com/contact-us[cite: 2]
//
// WHAT THIS EXAMPLE DOES
// Demonstrates how to put the sensor into an ultra-low power standby state 
// to save battery, waking it up only to take a reading.
//
// SKILLS LEARNED
// Managing the sensor's power states programmatically.
//
// DESCRIPTION
// The I2Connect: KXTJ3-1057 is a compact, ultra-low power 3-axis MEMS accelerometer module.
// It provides a simple and reliable way to add motion detection, tilt sensing, 
// and orientation tracking to your embedded systems.
// The module communicates over the standard I2C interface with a default address 
// of 0x0E. If multiple modules are required in the same system, the alternative 
// address 0x0F or an I2C multiplexer must be used.
// Like all I2Connect modules, it features dual Qwiic compatible connectors for 
// easy daisy-chaining and an angled male header for breadboard use.[cite: 2] It is 
// fully compatible with both 3.3V and 5V microcontroller systems.[cite: 2]

#include <Wire.h>
#include "PTSolns_I2Connect_KXTJ3_1057.h"

// User Settings
const uint32_t SERIAL_BAUD = 115200;

PTSolns_I2Connect_KXTJ3_1057 accel;

void setup() {
    Serial.begin(SERIAL_BAUD);
    while (!Serial);

    if (!accel.begin()) {
        Serial.println("Failed to find KXTJ3-1057 module!");
        while (true); 
    }
}

void loop() {
    float x, y, z;
    
    Serial.println("Waking up sensor...");
    accel.standby(false);
    delay(20); 
    
    if (accel.readAcceleration(&x, &y, &z)) {
        Serial.print("Reading -> X: "); Serial.print(x, 2);
        Serial.print("\tY: "); Serial.print(y, 2);
        Serial.print("\tZ: "); Serial.println(z, 2);
    }

    Serial.println("Putting sensor to sleep for 3 seconds...");
    accel.standby(true);
    
    delay(3000); 
}
