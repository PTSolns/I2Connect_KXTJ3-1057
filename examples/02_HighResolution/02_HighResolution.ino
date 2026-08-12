// Example: High Resolution for I2Connect: KXTJ3-1057
// Last Update: August 6, 2026
// Support: http://ptsolns.com/contact-us 
//
// WHAT THIS EXAMPLE DOES
// Configures the sensor to use the +/- 16g measurement range, high data rate, 
// and high-resolution mode, then prints the data.
//
// SKILLS LEARNED
// Using standby mode to safely change settings, configuring G-range, data rate, 
// and 12/14-bit resolution modes.
//
// NOTE ON POWER CONSUMPTION:
// According to the datasheet, the bare sensor current consumption is:
// - 0.9 uA in Standby
// - 10 uA in Low Power Mode
// - 155 uA in High Resolution Mode
//
// Calling accel.begin() automatically initializes this library in High 
// Resolution Mode (RES=1) to provide the most precise 12-bit/14-bit data. 
// If you are deploying this code in a battery-operated environment, you must 
// explicitly turn off high resolution by calling accel.enableHighRes(false); 
// inside your setup() block immediately after initialization. Note that Low 
// Power Mode is only available at output data rates of 200 Hz or lower.
//
// HARDWARE MODIFICATION FOR LOW POWER:
// To achieve these microamp power states on the I2Connect module, you 
// MUST cut the trace on the back of the board for the PWR LED. The power 
// drawn by the LED is vastly greater than the IC's current draw (milliamps 
// vs microamps) and will drain your battery if not disabled.
//
// DESCRIPTION
// The I2Connect: KXTJ3-1057 is a compact, ultra-low power 3-axis MEMS accelerometer module.
// It provides a simple and reliable way to add motion detection, tilt sensing, 
// and orientation tracking to your embedded systems.
// The module communicates over the standard I2C interface with a default address 
// of 0x0E. If multiple modules are required in the same system, the alternative 
// address 0x0F or an I2C multiplexer must be used.
// Like all I2Connect modules, it features dual Qwiic compatible connectors for 
// easy daisy-chaining and an angled male header for breadboard use.  It is 
// fully compatible with both 3.3V and 5V microcontroller systems. 

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

    accel.standby(true);
    accel.setRange(16); 
    accel.setDataRate(400); 
    accel.enableHighRes(true);
    accel.standby(false);

    Serial.println("High Resolution Mode Configured (+/- 16g)");
}

void loop() {
    float x, y, z;
    
    if (accel.readAcceleration(&x, &y, &z)) {
        Serial.print("X: "); Serial.print(x, 4); Serial.print(" g\t");
        Serial.print("Y: "); Serial.print(y, 4); Serial.print(" g\t");
        Serial.print("Z: "); Serial.print(z, 4); Serial.println(" g");
    }
    
    delay(50);
}
