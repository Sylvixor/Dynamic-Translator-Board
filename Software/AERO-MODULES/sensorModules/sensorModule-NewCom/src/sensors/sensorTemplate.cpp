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
Use this code as a template for adding new sensors.
*/

#ifdef DRIVER_SENSORNAME

/*
init function of the driver, gets called during the init phase of the system.
Configures the MOSFET_PIN used to switch power to the sensor
And checks if the sensor should be started/configured when the system boots
*/
CyrbSensor::CyrbSensor(){
    gpio_init(MOSFET_PIN);
    gpio_set_dir(MOSFET_PIN, GPIO_OUT);
    sensorOn = false;
    if(SENSOR_START_ON_POWER){
        sensorInit();
    }
}

/*
Function to turn on the power to the sensor, and init the sensor
*/
void CyrbSensor::turnSensorOn(){
    gpio_put(MOSFET_PIN, 1);
    sleep_ms(250);
    sensorInit();
    sensorOn = true;
}

/*
Turns the sensor off
*/
void CyrbSensor::turnSensorOff(){
    gpio_put(MOSFET_PIN, 0);
    sensorOn = false;
}

/* 
This function gets called when a request for data is received.
Place all nesecarry code in here that asks and requests the data from a sensor,
and place it in a Decoded data struct. Also add to the struct the number of data points.
Finally the dataStruct is encoded into a write struct, which is returned.
*/
WriteStruct CyrbSensor::sensorPrepData(){
    
    WriteStruct ws;

    printf("Prep Data\n");
    DecodedData dataStruct;
     

    ws = encodeData(dataStruct);

    // return encodeData(dataStruct);
    return ws;
}

/*
    returns the state of the sensor
*/
bool CyrbSensor::getSensorState(){
    return sensorOn;
}

/* 
The init function of the sensor, this gets called when the sensor has to be turend on.
Add all init/boot code here for the sensor used.
*/
void CyrbSensor::sensorInit(){
    

   

    return;
}
#endif