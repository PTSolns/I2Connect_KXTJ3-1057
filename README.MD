# PTSolns *I2Connect: KXTJ3-1057* Library

![Arduino Library](https://img.shields.io/badge/Arduino-Library-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Sensor](https://img.shields.io/badge/Sensor-3--Axis_Accelerometer-orange)

Library for the PTSolns *I2Connect: KXTJ3-1057* module. Available through both the Arduino Library Manager and the PTSolns IDE Library Manager, this library provides a streamlined interface to read multi-axis acceleration, detect motion, and manage low-power states while automatically handling I2C communication.

---

## Overview

The *I2Connect: KXTJ3-1057* is a compact, ultra-low power 3-axis MEMS accelerometer module. Designed as part of the I2Connect Series, this module provides a simple and reliable way to add motion detection, tilt sensing, and orientation tracking to your embedded systems. 

The sensor communicates over the industry-standard I2C interface and features selectable measurement ranges (±2g, ±4g, ±8g, ±16g), scalable data rates, and built-in motion wake-up capabilities. The module features an onboard voltage regulator, making it fully compatible with both 3.3V and 5V systems out of the box. This allows it to be used with a wide range of popular microcontroller platforms without the need for external level shifters or power step-downs.

Like all I2Connect modules, it connects using dual Qwiic® compatible connectors to easily integrate into existing I2C systems without soldering. The preinstalled right-angle header provides direct access to the I2C bus and the hardware interrupt (`INT`) pin for breadboard-based prototyping.

---

## *I2Connect* Series

The PTSolns *I2Connect* Series is a family of plug and play expansion modules designed to simplify the integration of sensors, displays, user interfaces, and other peripherals into embedded systems. Built around the industry standard I2C communication protocol and featuring convenient Qwiic® compatible connectors (4 pin, 1 mm JST SH), *I2Connect* modules can be quickly connected without soldering or complex wiring.

Each module is fully assembled and includes a preinstalled male header that is compatible with standard solderless breadboards, enabling immediate use and rapid prototyping. Designed to work seamlessly with a wide range of microcontroller platforms, I2Connect modules combine compact hardware, comprehensive documentation, and easy to use software libraries. The _I2Connect_ Series enables makers, students, educators, and professionals to rapidly prototype, evaluate, and develop reliable electronic systems.

The following modules are part of the *I2Connect* Series:

* [**AHT20**](https://ptsolns.com/products/i2connect-aht20) — Temperature & Humidity
* [**VEML7700**](https://ptsolns.com/products/i2connect-veml7700) — Light & Lux
* [**EEPROM**](https://ptsolns.com/products/i2connect-eeprom) — 2 Mbit Memory
* **Buttons** — User Input via 4×4 Matrix of Buttons
* **Digit Display** — Dual 7 Segment Display
* **ICP-20100** — Pressure & Temperature
* **KXTJ3-1057** — 3 Axis Accelerometer
* **MUX** — 4 Channel I2C Multiplexer
* **OLED** — 0.96" 128×64 OLED Display
* **I2C Doctor** — I2C Bus Recovery and Diagnostics
* **...and more!**

---

## Key Features

* High-performance 3-axis digital accelerometer.
* Selectable dynamic ranges: ±2g, ±4g, ±8g, ±16g.
* Multiple resolutions: 8-bit (low power), 12-bit, and 14-bit (high resolution).
* Embedded wake-up and motion detection capabilities via the `INT` pin.
* Default I2C address of 0x0E (Alternative 0x0F via jumper pad).
* **Onboard voltage regulator** ensuring safe 3.3V and 5V logic and power compatibility.
* Dual Qwiic® compatible 4-pin JST SH connectors for daisy-chaining.
* Breadboard-friendly 5-pin 2.54mm angled male header (GND, 3V3, SDA, SCL, INT).
* Integrated power LED with a physical disconnect pad on the rear.

---

## I2Connect Ecosystem

The *I2Connect: KXTJ3-1057* is part of the PTSolns I2Connect ecosystem.

All *I2Connect* modules utilize a standardized 4 pin JST SH 1.0 mm connector carrying:

| Pin | Function |
| --- | -------- |
| 1   | GND      |
| 2   | VCC      |
| 3   | SDA      |
| 4   | SCL      |

This connector follows the widely adopted Qwiic® standard, allowing modules and compatible boards to be connected without soldering.

For maximum compatibility, the module also includes a preinstalled angled male header, allowing use with virtually any 3.3 V or 5 V microcontroller platform. The male header on this module also breaks out the hardware Interrupt (`INT`) pin.

---

## Sensor Specifications

| Parameter               | Value                                  |
| ----------------------- | -------------------------------------- |
| Sensor IC               | Kionix KXTJ3-1057                      |
| Measurement Range       | ±2g, ±4g, ±8g, ±16g                    |
| Interface               | I2C                                    |
| I2C Address             | 0x0E (Default) / 0x0F (Alt)            |
| Operating Voltage       | 3.3 V / 5 V Rated (Onboard Regulator)  |
| Communication Speed     | Standard, Fast, & High-Speed (Up to 3.4 MHz) |
| Resolutions             | 8-bit, 12-bit, 14-bit                  |
| Header Pinout           | INT, SCL, SDA, 3V3, GND                |
| Connectors              | 2x 4-pin 1mm JST SH                    |

---

## I2C Addressing & Multiplexing

The *I2Connect: KXTJ3-1057* module uses a default I2C address of:

```text
0x0E
```
This address can be modified to **0x0F** by adjusting the ADDR solder pad on the rear of the module PCB. If more than two accelerometer modules are required in the same system, an I2C multiplexer must be used.
The PTSolns I2Connect: MUX module provides four independent I2C channels, allowing multiple identically-addressed modules to be connected to a single microcontroller.

---


## *PTSolns IDE*

The [*PTSolns IDE*](https://ptsolns.com/ide) is a free desktop application for programming PTSolns microcontroller development boards and compatible Arduino platforms.

This library is available directly through both the PTSolns IDE Library Manager and the Arduino Library Manager.

To install:

1. Open the PTSolns IDE (or Arduino IDE).
2. Open the Library Manager.
3. Search for:

```text
I2Connect_KXTJ3
```

4. Click Install.

Features of the [*PTSolns IDE*](https://ptsolns.com/ide) include:

* Integrated board management
* Built in serial monitor
* Library management
* Example project browser
* Support for over 8,500 third party libraries
* Built in CH340 USB driver support
* Open source and community driven

The [*PTSolns IDE*](https://ptsolns.com/ide) can be used alongside the Arduino IDE and supports many PTSolns development boards out of the box.

---

## Quick Start
```cpp

#include <Wire.h>
#include "PTSolns_I2Connect_KXTJ3.h"

PTSolns_I2Connect_KXTJ3 accel;

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    // Initialize the sensor. The library automatically defaults to 0x0E.
    if (!accel.begin()) {
        Serial.println("Failed to find KXTJ3-1057 module.");
        while (true); // Halt if sensor is not found
    }

    // Set configuration: Output Data Rate (ODR) and Measurement Range
    accel.setRange(2); // Set to +/- 2g
    accel.setDataRate(50); // Set ODR to 50 Hz
}

void loop()
{
    float x, y, z;
    
    // Read the current acceleration data
    if (accel.readAcceleration(&x, &y, &z)) {
        Serial.print("X: "); Serial.print(x, 2);
        Serial.print(" g | Y: "); Serial.print(y, 2);
        Serial.print(" g | Z: "); Serial.print(z, 2);
        Serial.println(" g");
    }
    
    delay(100);
}
```

---

## Library Functions

| Function          | Description                                    |
| ----------------- | -----------------------------------------------|
| begin(address)          | Initialize the I2C hardware and sensor configuration  |
| readAcceleration()   | Poll the X, Y, and Z registers and return values in 'g'  |
| setRange(g)        | Sets the full-scale range (2, 4, 8, or 16) |
| setDataRate(hz)           | Sets the Output Data Rate (ODR)   |
| enableHighRes()   | Switches the sensor to 12-bit or 14-bit output mode         |
| standby(state)    | Enter/Exit the ultra-low-power standby mode                 |
| configInterrupt()     | Sets up the hardware INT pin for motion triggers        |


---

## Basic Functions

### Initialization
```cpp
// Initializes sensor at default address 0x0E
accel.begin();

// Initializes sensor at alternative address 0x0F
accel.begin(0x0F);

```

### Initialization

The KXTJ3-1057 requires you to place it into standby mode before changing core registers like the data rate or range.
```cpp
accel.standby(true);    // Put to sleep
accel.setRange(8);      // Adjust range to +/- 8g
accel.standby(false);   // Wake back up
```
---
## Typical Applications

* Embedded motion detection and wake-on-motion
* Device orientation and screen rotation triggers
* Robotics tilt and balance sensing
* Tap/Double-tap physical user interfaces
* Predictive maintenance via vibration sensing
---
## Included Examples

| Example                | Description                                          |
| ---------------------- | ---------------------------------------------------- |
| 01_BasicReadings          | Initialize the sensor and print X, Y, Z acceleration data over serial           |
| 02_HighResolution       | Demonstrates configuring the sensor for ±16g range and 12/14-bit data  |
| 03_TiltDetection     | Calculates roll and pitch angles based on the gravity vector         |
| 04_MotionInterrupt        | Configures the hardware INT pin to trigger a wake-up on motion       |
| 05_LowPowerSleep   | Shows how to manage standby states to conserve battery      |

---

## Documentation & Resources

Additional resources are available through the PTSolns Documentation Repository, including:

* Datasheets
* Schematics
* Pinout diagrams
* 3D models
* Fritzing files
* Tutorials
* Example projects

* [PTSolns Documentation Repository](https://docs.ptsolns.com)
* [PTSolns Website](https://ptsolns.com)
* [Contact Support](https://ptsolns.com/contact-us)
* [PTSolns IDE](https://ptsolns.com/ide)
