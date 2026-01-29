#include <iostream>
#include <array>
#include <cstdint>

#pragma once



#define DEVICELIM 127 //maximum number of device addresses available
// #define BUFFERLEN 32    //the lenght of the buffers
#define BUFFERLEN 256    //the lenght of the buffers


/**
 * @brief opens a new i2c 'bus' for a device
 * @param deviceBus pointer in which info the opened bus is stored
 * @return 0 - OK | -1 - fail
*/
int openI2CBus(int *deviceBus);

/**
 * @brief Sets the i2c address for a opened i2c bus
 * @param deviceBus pointer in which info the opened bus is stored
 * @param deviceAdress the i2c address of the device we want to access
 * @return 0 - OK | -1 - fail
*/
int setI2CAdress(int *deviceBus, int deviceAdress);

/**
 * @brief Reads a number of bytes from the i2c bus
 * @param deviceBus pointer in which info the opened bus is stored
 * @param length The number of bytes to read
 * @return 0 - OK | -1 - fail
*/
void readI2C(int *deviceBus, uint8_t *data, int length);

/**
 * @brief writes a 1 byte commando to the sensormodule
 * @param deviceBus pointer in which info the opened bus is stored
 * @param writebuffer 1 byte buffer for the commando to send
*/
int writeI2C(int *deviceBus, uint8_t writeBuffer[BUFFERLEN], int length);

bool i2c_detect_device(int busHandle, int address); // nieuwe toevoeging

/**
 * @brief Scnas the i2c bus for connected and active devices
 * @return int array {int nr of device, {id1, id2, etc}}
*/
std::array<std::array<int, 7>, 2> i2cScanner();