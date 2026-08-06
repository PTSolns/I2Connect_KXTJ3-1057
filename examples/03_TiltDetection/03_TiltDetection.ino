// Example: Tilt Detection for I2Connect: KXTJ3-1057
// Last Update: August 6, 2026
// Support: http://ptsolns.com/contact-us[cite: 2]
//
// WHAT THIS EXAMPLE DOES
// Reads acceleration data and calculates the roll and pitch angles using 
// basic trigonometry based on the gravity vector.
//
// SKILLS LEARNED
// Converting raw gravity vectors into usable angles (roll and pitch) for 
// orientation tracking.
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
#include <math.h>
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
    
    if (accel.readAcceleration(&x, &y, &z)) {
        float roll = atan2(y, z) * 180.0 / PI;
        float pitch = atan2(-x, sqrt(y * y + z * z)) * 180.0 / PI;

        Serial.print("Roll: "); Serial.print(roll, 1); Serial.print(" deg\t");
        Serial.print("Pitch: "); Serial.print(pitch, 1); Serial.println(" deg");
    }
    
    delay(100);
}
