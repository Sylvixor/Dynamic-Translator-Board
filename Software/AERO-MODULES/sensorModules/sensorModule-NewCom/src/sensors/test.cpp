#include <sensor.h>


#include <pico/types.h> //fixes 'not included' error on uint, true, etc
#include <pico/stdlib.h>
#include "pico/binary_info.h"

#include <stdio.h>
#include <math.h>
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include <hardware/i2c.h>
#include <string.h>
#include <iostream>


/*
* this driver is used as a test driver, to test new features, verify workings, etc.
*/

#ifdef DRIVER_TEST

#define ADDRESS 0x40            // I2C Address of Sensor

//used to store the data from hm3301
static uint8_t buffer[30];
static uint16_t TEST_DATA = 42;
static uint16_t TEST_DATA1 = 101;
static unsigned char uart_disabled = 0;

CyrbSensor::CyrbSensor(){
    gpio_init(MOSFET_PIN);
    gpio_set_dir(MOSFET_PIN, GPIO_OUT);
    sensorOn = false;
    if(SENSOR_START_ON_POWER){
        gpio_put(MOSFET_PIN, 1); 
        sleep_ms(250);
        sensorInit();
    }
}

void CyrbSensor::turnSensorOn(){
    gpio_put(MOSFET_PIN, 1);
    sleep_ms(250);
    sensorInit();
    sensorOn = true;
}
void CyrbSensor::turnSensorOff(){
    gpio_put(MOSFET_PIN, 0);
    sensorOn = false;
    uart_disabled = 0;
}

WriteStruct CyrbSensor::sensorPrepData(){
    
    WriteStruct ws;

    printf("Prep Data\n");
    DecodedData dataStruct;
   
    dataStruct.dataPoints = 3;



    dataStruct.data[0] = TEST_DATA;
    dataStruct.data[1] = TEST_DATA1;


    ws = encodeData(dataStruct);

    return ws;
}

bool CyrbSensor::getSensorState(){
    return sensorOn;
}

void CyrbSensor::sensorInit(){
    
    static const uint I2C_BAUDRATE = 100000; // 100 kHz


    gpio_init(I2C_MASTER_SDA_PIN);
    gpio_set_function(I2C_MASTER_SDA_PIN, GPIO_FUNC_I2C);
    gpio_init(I2C_MASTER_SCL_PIN);
    gpio_set_function(I2C_MASTER_SCL_PIN, GPIO_FUNC_I2C);

    gpio_pull_up(I2C_MASTER_SDA_PIN);
    gpio_pull_up(I2C_MASTER_SCL_PIN);
    i2c_init(i2c1, I2C_BAUDRATE);

   
    sleep_ms(500);
    return;
}
#endif