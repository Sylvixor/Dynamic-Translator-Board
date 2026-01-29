#include <i2c_fifo.h>
#include <i2c_slave.h>
#include <string.h>

#include "sensor.h"

#pragma once



// static const uint I2C_SLAVE_ADDRESS = 10;
// static const uint I2C_BAUDRATE = 100000; // 100 kHz
// /**
//  * the dev board currently in use is the QTPY RP2040, so we're
//  * using the I2C pinouts for that board.
//  * SDA = 24
//  * SCL = 25
// */
// static const uint I2C_SLAVE_SDA_PIN = 24;
// static const uint I2C_SLAVE_SCL_PIN = 25;

static bool i2cEvent = false;

/**
 * Struct from receiving and sending data over i2c
*/

struct i2cCommData{
    uint8_t mem[256];
    uint8_t mem_address;
};

extern DynamicJsonDocument infoJson;

void handler();
bool getI2cEvent();
void setup_slave(CyrbSensor *s);
void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event);
DynamicJsonDocument jsonReadOut(std::string jsonString);