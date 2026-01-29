/*
    Library for easy interfacing with sensors in modules.
    Each Sensor driver source code contains the functions listed below.
    This means that the main function for each driver can be the same,
    so this library basically functions as an API for the different sensors
    To compile the different drivers read build_flags in "TranslationUnit --> platformio.ini"
*/

#include <pico/types.h> 
#include <pico/stdlib.h>
// #include "pico/binary_info.h"

#include <stdio.h>
// #include <math.h>
#include "hardware/gpio.h"
#include <hardware/i2c.h>
// #include "hardware/timer.h"
#include <string.h>
// #include <iostream>
// #include "protocol_translator.h"

#include <ArduinoJson-v6.19.4.h>
#include "constConfig.h"
#include "protocol_translator.h"

#pragma once


class CyrbSensor{
    private:
        bool sensorOn;
    public:
        CyrbSensor();
        /** 
         * @brief initializes the sensor, along with any systems needed for the sensor to work
        */
        void sensorInit();
        /**
         * @brief constructs a json with the data from the sensor
         * @return a struct containing the taken sensor measurement
        */
        WriteStruct sensorPrepData();
        /**
         * @brief returns the state of the sensor, 0 = off, 1 = on
         * @return state of the sensor, 0 = off, 1 = on
        */
        bool getSensorState();
        /**
         * @brief turn on the sensor using the mosfet, and any extra processes
        */
        void turnSensorOn();
        /**
         * @brief turn off the sensor using the mosfet
        */
        void turnSensorOff();
};