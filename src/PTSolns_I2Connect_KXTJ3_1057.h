#ifndef PTSOLNS_I2CONNECT_KXTJ3_1057_H
#define PTSOLNS_I2CONNECT_KXTJ3_1057_H

#include <Arduino.h>
#include <Wire.h>

#define KXTJ3_ADDR_DEFAULT 0x0E
#define KXTJ3_ADDR_ALT     0x0F

#define KXTJ3_XOUT_L       0x06
#define KXTJ3_WHO_AM_I     0x0F
#define KXTJ3_CTRL_REG1    0x1B
#define KXTJ3_CTRL_REG2    0x1D
#define KXTJ3_INT_CTRL_REG1 0x1E
#define KXTJ3_INT_CTRL_REG2 0x1F
#define KXTJ3_DATA_CTRL_REG 0x21
#define KXTJ3_INT_REL      0x1A

#define KXTJ3_CHIP_ID      0x35

class PTSolns_I2Connect_KXTJ3_1057 {
public:
    PTSolns_I2Connect_KXTJ3_1057();

    bool begin(uint8_t address = KXTJ3_ADDR_DEFAULT);
    
    bool readAcceleration(float* x, float* y, float* z);
    
    void setRange(uint8_t gRange);
    void setDataRate(uint16_t hz);
    void enableHighRes(bool enable = true);
    
    void standby(bool sleep = true);
    void configInterrupt(bool enable);

private:
    uint8_t _address;
    float _gMultiplier;
    
    void writeRegister(uint8_t reg, uint8_t data);
    uint8_t readRegister(uint8_t reg);
    void readRegisters(uint8_t reg, uint8_t* buffer, uint8_t len);
};

#endif
