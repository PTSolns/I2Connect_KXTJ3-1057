#include "PTSolns_I2Connect_KXTJ3_1057.h"

PTSolns_I2Connect_KXTJ3_1057::PTSolns_I2Connect_KXTJ3_1057() {
    _address = KXTJ3_ADDR_DEFAULT;
    _gMultiplier = 1.0f / 16384.0f; 
}

bool PTSolns_I2Connect_KXTJ3_1057::begin(uint8_t address) {
    _address = address;
    
    Wire.begin();
    
    if (readRegister(KXTJ3_WHO_AM_I) != KXTJ3_CHIP_ID) {
        return false;
    }
    
    standby(true);
    setRange(2);
    setDataRate(50);
    enableHighRes(true);
    standby(false);
    
    return true;
}

bool PTSolns_I2Connect_KXTJ3_1057::readAcceleration(float* x, float* y, float* z) {
    uint8_t buffer[6];
    readRegisters(KXTJ3_XOUT_L, buffer, 6);
    
    int16_t rawX = (int16_t)((buffer[1] << 8) | buffer[0]);
    int16_t rawY = (int16_t)((buffer[3] << 8) | buffer[2]);
    int16_t rawZ = (int16_t)((buffer[5] << 8) | buffer[4]);
    
    *x = (float)rawX * _gMultiplier;
    *y = (float)rawY * _gMultiplier;
    *z = (float)rawZ * _gMultiplier;
    
    return true;
}

void PTSolns_I2Connect_KXTJ3_1057::setRange(uint8_t gRange) {
    uint8_t ctrl = readRegister(KXTJ3_CTRL_REG1);
    ctrl &= 0xE3; 
    
    switch (gRange) {
        case 2:  
            ctrl |= (0x00 << 2); 
            _gMultiplier = 1.0f / 16384.0f; 
            break;
        case 4:  
            ctrl |= (0x02 << 2); 
            _gMultiplier = 1.0f / 8192.0f;  
            break;
        case 8:  
            ctrl |= (0x04 << 2); 
            _gMultiplier = 1.0f / 4096.0f;  
            break;
        case 16: 
            ctrl |= (0x01 << 2); 
            _gMultiplier = 1.0f / 2048.0f;  
            break;
        default: 
            return;
    }
    
    writeRegister(KXTJ3_CTRL_REG1, ctrl);
}

void PTSolns_I2Connect_KXTJ3_1057::setDataRate(uint16_t hz) {
    uint8_t dataCtrl = readRegister(KXTJ3_DATA_CTRL_REG);
    dataCtrl &= 0xF0; 
    
    if (hz < 2) dataCtrl |= 0x08;
    else if (hz < 4) dataCtrl |= 0x09;
    else if (hz < 10) dataCtrl |= 0x0A;
    else if (hz < 20) dataCtrl |= 0x00;
    else if (hz < 40) dataCtrl |= 0x01;
    else if (hz < 75) dataCtrl |= 0x02;
    else if (hz < 150) dataCtrl |= 0x03;
    else if (hz < 300) dataCtrl |= 0x04;
    else if (hz < 600) dataCtrl |= 0x05;
    else if (hz < 1200) dataCtrl |= 0x06;
    else dataCtrl |= 0x07; 
    
    writeRegister(KXTJ3_DATA_CTRL_REG, dataCtrl);
}

void PTSolns_I2Connect_KXTJ3_1057::enableHighRes(bool enable) {
    uint8_t ctrl = readRegister(KXTJ3_CTRL_REG1);
    if (enable) {
        ctrl |= (1 << 6); 
    } else {
        ctrl &= ~(1 << 6); 
    }
    writeRegister(KXTJ3_CTRL_REG1, ctrl);
}

void PTSolns_I2Connect_KXTJ3_1057::standby(bool sleep) {
    uint8_t ctrl = readRegister(KXTJ3_CTRL_REG1);
    if (sleep) {
        ctrl &= ~(1 << 7); 
    } else {
        ctrl |= (1 << 7);  
    }
    writeRegister(KXTJ3_CTRL_REG1, ctrl);
    delay(2); 
}

void PTSolns_I2Connect_KXTJ3_1057::configInterrupt(bool enable) {
    uint8_t intCtrl = readRegister(KXTJ3_INT_CTRL_REG1);
    if (enable) {
        intCtrl |= (1 << 5); 
    } else {
        intCtrl &= ~(1 << 5); 
    }
    writeRegister(KXTJ3_INT_CTRL_REG1, intCtrl);
}

void PTSolns_I2Connect_KXTJ3_1057::writeRegister(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

uint8_t PTSolns_I2Connect_KXTJ3_1057::readRegister(uint8_t reg) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission(false);
    
    Wire.requestFrom(_address, (uint8_t)1);
    if (Wire.available()) {
        return Wire.read();
    }
    return 0;
}

void PTSolns_I2Connect_KXTJ3_1057::readRegisters(uint8_t reg, uint8_t* buffer, uint8_t len) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission(false);
    
    Wire.requestFrom(_address, len);
    for (uint8_t i = 0; i < len; i++) {
        if (Wire.available()) {
            buffer[i] = Wire.read();
        }
    }
}
