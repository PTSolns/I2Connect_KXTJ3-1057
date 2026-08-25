// Example: Low Power Sleep for I2Connect: KXTJ3-1057
// Last Update: August 6, 2026
// Support: http://ptsolns.com/contact-us 
//
// WHAT THIS EXAMPLE DOES
// Demonstrates how to put the sensor into an ultra-low power standby state 
// to save battery, waking it up only to take a reading.
//
// SKILLS LEARNED
// Managing the sensor's power states programmatically.
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
#include <PTSolns_I2Connect_KXTJ3_1057.h>

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

    // Explicitly force Low Power Mode (RES = 0) to reduce active current to 10uA
    accel.standby(true);
    accel.enableHighRes(false);
    // We leave it in standby here because the loop() logic will wake it up
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
