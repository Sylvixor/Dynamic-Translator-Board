#include <sensor.h>
#include <scd4x.h>

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


#include <ArduinoJson-v6.19.4.h>


// #include "constConfig.h"

#if defined DRIVER_SCD4X || defined (DRIVER_COMBINE)


/**************************** Init and reset ********************************/

Cyrb_SCD4X::Cyrb_SCD4X(uint8_t i2cAddr){
    printf("test\n");
	deviceAddr=SCD4X_I2C_ADDR;
}

//bool sensorSetup = false;

bool Cyrb_SCD4X::begin(void){

    enablePeriodMeasure(SCD4X_STOP_PERIODIC_MEASURE);

    return true;
}

void Cyrb_SCD4X::enablePeriodMeasure(uint16_t mode){
    writeData(mode);
    if(SCD4X_STOP_PERIODIC_MEASURE == mode){
        sleep_ms(500);
    }
}

/**************************** Read and Write ********************************/

void Cyrb_SCD4X::writeData(uint16_t cmd){

    uint8_t buf[2];
    buf[1] = cmd;
    buf[0] = cmd >> 8;
    i2c_write_timeout_us(i2c1, deviceAddr, buf, 2, false, 2*500);
    // i2c_write_blocking(i2c1, deviceAddr, buf, 2, false);
}

size_t Cyrb_SCD4X::readData(uint16_t cmd, uint8_t *buf, size_t size){
    size_t count = 0;

    // uint8_t * _pBuf = (uint8_t*)pBuf;

    uint8_t buffer[3];

    writeData(cmd);

    i2c_read_blocking(i2c1, deviceAddr, buf, size, 0);
    return count;
}

/********************************* Measurement Function *************************************/


void Cyrb_SCD4X::readMeasurement(sSensorMeasurement_t * data){
    uint8_t buf[9] = {0};
    readData(SCD4X_READ_MEASUREMENT, buf, sizeof(buf));

    data->CO2ppm = SCD4X_CONCAT_BYTES(buf[0], buf[1]);

    data->temp = -45 + 175 * (float)(SCD4X_CONCAT_BYTES(buf[3], buf[4])) / ((uint32_t)1 << 16);
    DBG(SCD4X_CONCAT_BYTES(buf[3], buf[4]));
    DBG((float)(SCD4X_CONCAT_BYTES(buf[3], buf[4])));
    DBG((float)(SCD4X_CONCAT_BYTES(buf[3], buf[4])) / ((uint32_t)1 << 16));
    DBG((uint32_t)1 << 16);
    DBG(175 * (float)(SCD4X_CONCAT_BYTES(buf[3], buf[4])) / ((uint32_t)1 << 16));
    DBG(data->temp);

    data->humidity = 100 * (float)(SCD4X_CONCAT_BYTES(buf[6], buf[7])) / ((uint32_t)1 << 16);


}

bool Cyrb_SCD4X::getDataReadyStatus(void){
    uint8_t buf[3] = {0};
    readData(SCD4X_GET_DATA_READY_STATUS, buf, sizeof(buf));
    if(0x000 == (SCD4X_CONCAT_BYTES(buf[0], buf[1]) & 0x7FF)){
        std::cout << "GetStatus: False" << std::endl;
        return false;
    }
    return true;
}

/*************************** compensation and calibration ********************************/

void Cyrb_SCD4X::setTempComp(float tempComp){
    /**
     * Temoperature offset can't be tested yet, not implemented.
     * temp has no effect on co2 measurements
    */
}

void Cyrb_SCD4X::setSensorAltitude(uint16_t altitude){
    /**
     * altitude varies, and has no effect on co2 measurements
    */

}

void Cyrb_SCD4X::setAmbientPressure(uint32_t ambientPressure){
    /**
     * ambient pressure has no effect on co2 measurements
    */
}

void Cyrb_SCD4X::setAutoCalibMode(bool mode){
    /**
     * is enabled by default, no need to change it yet.
    */
}



Cyrb_SCD4X SCD4X(SCD4X_I2C_ADDR);

// CyrbSensor::CyrbSensor(){
//     gpio_init(MOSFET_PIN);
//     gpio_set_dir(MOSFET_PIN, GPIO_OUT);
//     sensorOn = false;
//     if(SENSOR_START_ON_POWER){
//         gpio_put(MOSFET_PIN, 1);
//         sleep_ms(250);
//         sensorInit();
//     }
// }

// void CyrbSensor::turnSensorOn(){
//     gpio_put(MOSFET_PIN, 1);
//     sleep_ms(250);
//     sensorInit();
//     sensorOn = true;
// }
// void CyrbSensor::turnSensorOff(){
//     gpio_put(MOSFET_PIN, 0);
//     sensorOn = false;
// }

// WriteStruct CyrbSensor::sensorPrepData(){
    
//     WriteStruct ws;

//     printf("Prep Data\n");
//     DecodedData dataStruct;
//     dataStruct.dataPoints = 3;

//     DynamicJsonDocument doc(256);
//     if(!sensorSetup){
//         SCD4X.begin(); 
//         SCD4X.enablePeriodMeasure(SCD4X_START_PERIODIC_MEASURE);
//         sensorSetup = true;
//     }
// 	if(SCD4X.getDataReadyStatus()){
//         Cyrb_SCD4X::sSensorMeasurement_t data;
//         // SCD4X.readMeasurement(&senseData);
//         SCD4X.readMeasurement(&data);
//         //dataStruct.dataPoints = 3;


//         dataStruct.data[0] = data.CO2ppm;
//         dataStruct.data[1] = data.temp;
//         dataStruct.data[2] = data.humidity;



//         doc["d0"] = data.CO2ppm;
//         doc["d1"] = data.temp;
//         doc["d2"] = data.humidity;
//         std::cout << "CO2 Data: " << data.CO2ppm << std::endl;
//         std::cout << "temp Data: " << data.temp << std::endl;
//         std::cout << "humidity Data: " << data.humidity << std::endl;
//         printf("ppm: %i, temp: %i, humidity: %i\n", doc["d0"], doc["d1"], doc["d2"]);
//         ws = encodeData(dataStruct);
//         // return encodeData(2, data.CO2ppm, data.temp, data.humidity);
//     }else{
//         dataStruct.dataPoints = 1;
//         dataStruct.data[0] = -999;
//         // ws = encodeData(dataStruct);
//     }
//     ws = encodeData(dataStruct);

//     // return encodeData(dataStruct);
//     return ws;
// }

// bool CyrbSensor::getSensorState(){
//     return sensorOn;
// }

// void CyrbSensor::sensorInit(){
    

//     /* enable the i2c lines*/
//     gpio_init(I2C_MASTER_SDA_PIN);
//     gpio_set_function(I2C_MASTER_SDA_PIN, GPIO_FUNC_I2C);
    
//     gpio_init(I2C_MASTER_SCL_PIN);
//     gpio_set_function(I2C_MASTER_SCL_PIN, GPIO_FUNC_I2C);

//     gpio_pull_up(I2C_MASTER_SDA_PIN);
//     gpio_pull_up(I2C_MASTER_SCL_PIN);


//     i2c_init(i2c1, I2C_BAUDRATE);
//     sleep_ms(500);
//     SCD4X.begin(); 
//     SCD4X.enablePeriodMeasure(SCD4X_START_PERIODIC_MEASURE);
    // sleep_ms(5000);
    // SCD4X.begin(); 
    // SCD4X.enablePeriodMeasure(SCD4X_START_PERIODIC_MEASURE);


    // sleep_ms(500);

//     return;
// }
#endif