// #include <sensor.h>

#pragma once


/* 

This file contains the static configs which are compiled with the program.c
Only 1 set of configs is selected, based on the driver selected in CMakeList.txt
*/


static const uint I2C_BAUDRATE = 100000; // 100 kHz
// Nieuw
// Sensor I2C addresses (master mode - reading external sensors)
#define DHT22_MASTER_ADDR 0x44
#define BMP280_MASTER_ADDR 0x77
#define HM3301_MASTER_ADDR 0x40
#define SCD4X_MASTER_ADDR 0x62


static const uint SM_VERSION = 3;

#ifdef DRIVER_TEST
static const uint I2C_SLAVE_ADDRESS = 99;
static const uint SENSOR_MODULE_ID = 99;
static const uint MEASURE_INTERVAL = 5;
static const uint SENSE_INTERVAL = 3;
static const uint MODULE_PRIORITY = 1;
static const uint SENSOR_PREPARE_TIME = 0;
static const uint SENSOR_START_ON_POWER = 0;
#endif

#ifdef DRIVER_DHT22
static const uint I2C_SLAVE_ADDRESS = 8;
static const uint SENSOR_MODULE_ID = 1;
static const uint MEASURE_INTERVAL = 5;
static const uint SENSE_INTERVAL = 3;
static const uint MODULE_PRIORITY = 1;
static const uint SENSOR_PREPARE_TIME = 0;
static const uint SENSOR_START_ON_POWER = 1;
#endif

#ifdef DRIVER_BMP280
static const uint I2C_SLAVE_ADDRESS = 9;
static const uint SENSOR_MODULE_ID = 2;
static const uint MEASURE_INTERVAL = 5;
static const uint SENSE_INTERVAL = 3;
static const uint MODULE_PRIORITY = 1;
static const uint SENSOR_PREPARE_TIME = 0;
static const uint SENSOR_START_ON_POWER = 1;
#endif

#ifdef DRIVER_HM3301
static const uint I2C_SLAVE_ADDRESS = 10;
static const uint SENSOR_MODULE_ID = 3;
static const uint MEASURE_INTERVAL = 5;
static const uint SENSE_INTERVAL = 3;
static const uint MODULE_PRIORITY = 1;
static const uint SENSOR_PREPARE_TIME = 0;
static const uint SENSOR_START_ON_POWER = 1;
#endif

#ifdef DRIVER_SCD4X
static const uint I2C_SLAVE_ADDRESS = 11;
static const uint SENSOR_MODULE_ID = 4;
static const uint MEASURE_INTERVAL = 5;
static const uint SENSE_INTERVAL = 6;
static const uint MODULE_PRIORITY = 1;
static const uint SENSOR_PREPARE_TIME = 0;
static const uint SENSOR_START_ON_POWER = 1;
#endif

// Nieuw
#ifdef DRIVER_COMBINE
static const uint I2C_SLAVE_ADDRESS = 12;
static const uint SENSOR_MODULE_ID = 5;
static const uint MEASURE_INTERVAL = 5;
static const uint SENSE_INTERVAL = 3;
static const uint MODULE_PRIORITY = 1;
static const uint SENSOR_PREPARE_TIME = 0;
static const uint SENSOR_START_ON_POWER = 1;
#endif