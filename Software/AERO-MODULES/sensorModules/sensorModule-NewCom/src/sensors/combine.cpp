// Volledig nieuw
#include <sensor.h>

#include <pico/types.h>
#include <pico/stdlib.h>
#include "pico/binary_info.h"

#include <stdio.h>
#include <math.h>
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include <hardware/i2c.h>
#include <string.h>
#include <iostream>

#include "constConfig.h"
#include "protocol_translator.h"
#include <scd4x.h>

// Sensor type enumeration
enum SensorType {
    SENSOR_NONE = 0,
    SENSOR_DHT22 = 1,
    SENSOR_BMP280 = 2,
    SENSOR_HM3301 = 3,
    SENSOR_SCD4X = 4
};

static uint8_t detectedSensorType = SENSOR_NONE;
static bool sensorOn = false;

static Cyrb_SCD4X SCD4X_sensor(SCD4X_MASTER_ADDR);
static bool SCD4X_initialized = false;

#ifdef DRIVER_COMBINE 

bool sensorSetup = false;

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
    sleep_ms(2000);
    sensorInit();
    sensorOn = true;
}

void CyrbSensor::turnSensorOff(){
    gpio_put(MOSFET_PIN, 0);
    sensorOn = false;
}

// Function to detect which sensor is connected
uint8_t detectSensor() {
    printf("\n=== Starting Sensor Detection ===\n");
    
    int ret;
    uint8_t test_byte = 0;
    
    // Try to detect DHT22
    printf("Trying DHT22 at 0x%02X... ", DHT22_MASTER_ADDR);
    ret = i2c_read_blocking(i2c1, DHT22_MASTER_ADDR, &test_byte, 1, false);
    printf("ret=%d\n", ret);
    if (ret > 0) {
        return SENSOR_DHT22;
    }
    
    // Try to detect BMP280
    printf("Trying BMP280 at 0x%02X... ", BMP280_MASTER_ADDR);
    ret = i2c_read_blocking(i2c1, BMP280_MASTER_ADDR, &test_byte, 1, false);
    printf("ret=%d\n", ret);
    if (ret > 0) {
        return SENSOR_BMP280;
    }
    
    // Try to detect HM3301
    printf("Trying HM3301 at 0x%02X... ", HM3301_MASTER_ADDR);
    ret = i2c_read_blocking(i2c1, HM3301_MASTER_ADDR, &test_byte, 1, false);
    printf("ret=%d\n", ret);
    if (ret > 0) {
        return SENSOR_HM3301;
    }
    
    // Try to detect SCD4X - AANGEPAST MET SPECIFIEK COMMANDO
    printf("Trying SCD4X at 0x%02X... ", SCD4X_MASTER_ADDR);
    
    // SCD4X vereist een specifiek commando om te reageren
    // Probeer "get serial number" commando (0x3682)
    uint8_t cmd[2] = {0x36, 0x82};
    uint8_t response[9];
    
    ret = i2c_write_blocking(i2c1, SCD4X_MASTER_ADDR, cmd, 2, false);
    printf("write ret=%d, ", ret);
    
    if(ret == 2) {
        sleep_ms(10);  // Wacht op respons
        ret = i2c_read_blocking(i2c1, SCD4X_MASTER_ADDR, response, 9, false);
        printf("read ret=%d\n", ret);
        
        if(ret == 9) {
            printf("SCD4X DETECTED!\n");
            return SENSOR_SCD4X;
        }
    } else {
        printf("no response\n");
    }
    
    printf("=== NO SENSOR DETECTED ===\n\n");
    return SENSOR_NONE;
}

static bool dataReady = false;
static DecodedData lastValidData;

WriteStruct CyrbSensor::sensorPrepData(){
    WriteStruct ws;
    DecodedData dataStruct;

    DynamicJsonDocument doc(256);
    
    printf("Prep Data\n");

    // if(!dataReady) {
    //     printf("Data not ready yet, returning cached data\n");
    //     ws = encodeData(lastValidData);
    //     return ws;
    // }

    switch(detectedSensorType) {
        case SENSOR_DHT22:
            {
                // DHT22 code - placeholder
                printf("Reading DHT22 at 0x%02X\n", DHT22_MASTER_ADDR);
                dataStruct.dataPoints = 2;
                // TODO: Implement DHT22 reading logic
                dataStruct.data[0] = -999; // placeholder
                dataStruct.data[1] = -999; // placeholder
            }
            break;
            
        case SENSOR_BMP280:
            {
                // BMP280 code - placeholder
                printf("Reading BMP280 at 0x%02X\n", BMP280_MASTER_ADDR);
                dataStruct.dataPoints = 3;
                // TODO: Implement BMP280 reading logic
                dataStruct.data[0] = -999; // placeholder
                dataStruct.data[1] = -999; // placeholder
                dataStruct.data[2] = -999; // placeholder
            }
            break;
            
        case SENSOR_HM3301:
            {
                dataStruct.dataPoints = 3;
                unsigned char reg = 0x81;
                unsigned char buffer[30];
                
                printf("Reading HM3301 at 0x%02X\n", HM3301_MASTER_ADDR);
                
                if(i2c_write_blocking(i2c1, HM3301_MASTER_ADDR, &reg, 1, true) > 0){
                    int ret = i2c_read_blocking(i2c1, HM3301_MASTER_ADDR, buffer, 29, false);
                        uint16_t pm10 = buffer[4] << 8 | buffer[5];
                        uint16_t pm25 = buffer[6] << 8 | buffer[7];
                        uint16_t pm100 = buffer[8] << 8 | buffer[9];
                        
                        dataStruct.data[0] = pm10;
                        dataStruct.data[1] = pm25;
                        dataStruct.data[2] = pm100;
                        
                        lastValidData = dataStruct;
                }
                else{
                    printf("Failed to write register to HM3301\n");
                    dataStruct = lastValidData;  // Gebruik cached data
                }
            }
            break;
            
        case SENSOR_SCD4X:
            {
                //static Cyrb_SCD4X SCD4X_sensor(SCD4X_MASTER_ADDR);
                
                printf("Reading SCD4X at 0x%02X\n", SCD4X_MASTER_ADDR);
                dataStruct.dataPoints = 3;
                
                if(!SCD4X_initialized) {
                        printf("ERROR: SCD4X not initialized!\n");
                        dataStruct.data[0] = -999;
                        dataStruct.data[1] = -999;
                        dataStruct.data[2] = -999;
                        break;
                    }

                if(SCD4X_sensor.getDataReadyStatus()) {
                    Cyrb_SCD4X::sSensorMeasurement_t data;
                    SCD4X_sensor.readMeasurement(&data);
                    dataStruct.data[0] = data.CO2ppm;
                    dataStruct.data[1] = data.temp;
                    dataStruct.data[2] = data.humidity;
                    
                    lastValidData = dataStruct;

                    // doc["d0"] = data.CO2ppm;
                    // doc["d1"] = data.temp;
                    // doc["d2"] = data.humidity;
                    // std::cout << "CO2 Data: " << data.CO2ppm << std::endl;
                    // std::cout << "temp Data: " << data.temp << std::endl;
                    // std::cout << "humidity Data: " << data.humidity << std::endl;
                    // printf("ppm: %i, temp: %i, humidity: %i\n", doc["d0"], doc["d1"], doc["d2"]);
                }
                else {
                    printf("SCD4X data not ready yet, using cached data\n");
                    dataStruct = lastValidData;
                }
            }
            break;
            
        case SENSOR_NONE:
        default:
            {
                printf("No sensor detected or initialized\n");
                dataStruct.dataPoints = 1;
                dataStruct.data[0] = -999;
            }
            break;
    }
    
    ws = encodeData(dataStruct);
    return ws;
}

bool CyrbSensor::getSensorState(){
    return sensorOn;
}

void CyrbSensor::sensorInit(){
    // Initialize I2C pins 
    gpio_init(I2C_MASTER_SDA_PIN);
    gpio_set_function(I2C_MASTER_SDA_PIN, GPIO_FUNC_I2C);
    gpio_init(I2C_MASTER_SCL_PIN);
    gpio_set_function(I2C_MASTER_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_MASTER_SDA_PIN);
    gpio_pull_up(I2C_MASTER_SCL_PIN);
    
    i2c_init(i2c1, 100000);
    sleep_ms(2000);
    
    // Detect sensor
    for(int attempt = 0; attempt < 3; attempt++) {
        detectedSensorType = detectSensor();
        if(detectedSensorType != SENSOR_NONE) {
            break;
        }
        printf("Detection attempt %d failed, retrying...\n", attempt + 1);
        sleep_ms(500);
    }
    
    printf("Detected sensor type: %d\n", detectedSensorType);

    // Reset initialization flags if sensor type changed
    static uint8_t lastDetectedType = SENSOR_NONE;
    if(lastDetectedType != detectedSensorType) {
        printf("Sensor type changed, resetting initialization flags\n");
        // Hier kun je later static flags resetten als je die per sensor hebt
        lastDetectedType = detectedSensorType;
    }
    
    // Initialize detected sensor specific setup if needed
    switch(detectedSensorType) {
        case SENSOR_DHT22:
            printf("DHT22 initialization\n");
            // TODO: Add DHT22 specific initialization
            break;
        case SENSOR_BMP280:
            printf("BMP280 initialization\n");
            // TODO: Add BMP280 specific initialization
            break;
        case SENSOR_HM3301:
            printf("HM3301 initialization\n");
            // HM3301 doesn't need special initialization
            break;
        case SENSOR_SCD4X:
            {
                printf("SCD4X initialization\n");
                SCD4X_sensor.begin();
                SCD4X_sensor.enablePeriodMeasure(SCD4X_START_PERIODIC_MEASURE);
                SCD4X_initialized = true;
                printf("SCD4X periodic measurement started\n");
                sleep_ms(1000);
            }
            // {
            //     if(!sensorSetup){
            //         printf("SCD4X initialization\n");
            //         static Cyrb_SCD4X SCD4X_sensor(SCD4X_MASTER_ADDR);
            //         SCD4X_sensor.begin();
            //         SCD4X_sensor.enablePeriodMeasure(SCD4X_START_PERIODIC_MEASURE);
            //         sensorSetup = true;
            //     }
            //     printf("SCD4X periodic measurement started\n");
            // }
            break;
        default:
            printf("No recognized sensor detected\n");
            break;
    }

    lastValidData.dataPoints = 3;
    lastValidData.data[0] = -999;
    lastValidData.data[1] = -999;
    lastValidData.data[2] = -999;
    
    return;
}
#endif