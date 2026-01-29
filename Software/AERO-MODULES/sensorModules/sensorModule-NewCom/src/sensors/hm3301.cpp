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



#if defined DRIVER_HM3301 

#define ADDRESS 0x40            // I2C Address of Sensor

//used to store the data from hm3301
static uint8_t buffer[30];
static uint16_t pm10 = 0, pm25 = 0, pm100 = 0;
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

    
    unsigned char reg = 0x81;
    if(!uart_disabled){
        unsigned char uart_disable_command = 0x88;
        if(i2c_write_blocking(i2c1, ADDRESS, &uart_disable_command, 1, 0) == -2){
            printf("Error writing to device\n");
        }
        uart_disabled = 1;
    }
    sleep_ms(1);
    i2c_write_blocking(i2c1, ADDRESS, &reg, 1, 1);

    if(i2c_read_blocking(i2c1, ADDRESS, buffer, 29, 0) == -2){
        printf("Error reading from device\n");
        dataStruct.dataPoints = 1;
        dataStruct.data[0] = -999;
    }else{
        pm10 =  buffer[4] << 8 | buffer[5];
        pm25 =  buffer[6] << 8 | buffer[7];
        pm100 = buffer[8] << 8 | buffer[9];
        
        dataStruct.data[0] = pm10;
        dataStruct.data[1] = pm25;
        dataStruct.data[2] = pm100;
        // printf("pm10: %d | pm25: %d | pm100: %d\n",dataStruct.data[0],dataStruct.data[1],dataStruct.data[2]);
    }

    
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