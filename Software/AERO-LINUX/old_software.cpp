#include <iostream>
#include <stdio.h>
#include <string.h>
#include <array>
//DO NOT USE
#include "ArduinoJson-v6.19.4.h"    //library for making / deconstructing json documents
//Correct one:
#include "dist/json/json.h"
#include "dist/jsoncpp.cpp"

#include "commandos.h"
#include "printmsg.h"

// #include "json.h"
#include <fstream>

#include "stopwatch_base.h"     
#include <pigpio.h>

#include <time.h>

#include <errno.h>
#include <cstring>

#include <chrono>   //lib fot timer

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curl/curl.h>

//I2C
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

char *i2cBus = (char*)"/dev/i2c-1";

#define BUFFERLEN 256    //the lenght of the buffers
#define COMMANDOLEN 1
#define DEVICELIM 127 //maximum number of device addresses available
unsigned char readBuffer[BUFFERLEN] = {0};
unsigned char processedBuffer[BUFFERLEN] = {0};
unsigned char writeBuffer[60] = {0};
int numberOfDevices = 0;

//end I2c

//initialize sw class
using StopWatch = sw::stopwatch_base<std::chrono::steady_clock>;

//namespaces
using namespace std;

//variables

int deviceAddresses[6];  //array with the adresses of the devices(sensor modules)

struct sensorModule{    //struct with infromation about the sensor module
    int deviceId;
    int *deviceAddress; //internal address of i2c device
    StopWatch stopWatch{};  //stopwatch for keeping track of the intervals
    int i2cAddress; //i2c address
    int sensorModuleId; //id of the sensor module
    int measureInterval;    //time between 2 measurements
    int senseInterval;  //time to wait after measurement requets for sm to make measurement
    int modulePriority;
    int sensorPrepareTime;  //time the sensor needs to startup
	int dataLength; //length of the transferred sensor data
    int dataAmount;
	bool sharedAddress;
};

sensorModule modules[] = {  //a array of structs with info about the sensor modules
    {0, &deviceAddresses[0]},
    {1, &deviceAddresses[1]},
    {2, &deviceAddresses[2]},
    {3, &deviceAddresses[3]},
    {4, &deviceAddresses[4]},
    {5, &deviceAddresses[5]},
};

uint8_t PREP_SM_ID[1] = {0x32};
uint8_t MAKE_MEASUREMENT[1] = {0x40};

//counts the amount of times readI2c has failed
int errCounter = 0;

void setup(){
    //setup
    printmsg(4);
    gpioInitialise();
    if(gpioInitialise() < 0){
        std::cout << "gpioInitialise failed" << endl;
    }else{
        std::cout << "gpioInitialise succeeded" << endl;
    }
    
}

/* json function */
/**
 * @brief takes the received json string from I2C, and formats it into a ArduinoJson Object. 
 * @param jsonString 
 * @return DynamicJsonDocument 
 */
DynamicJsonDocument jsonReadOut(string jsonString){ //deserializes the json document and returns it
    DynamicJsonDocument doc(1024);
    DeserializationError err = deserializeJson(doc, jsonString);
    if(err){
        std::cout << "Json Deserialization failed: " << err << endl;
        throw(-1);
    }
    return doc;
}

/* I2C functions */

int openI2CBus(int *deviceAddress){    //opens the i2c bus for a new device
    if((*deviceAddress = open(i2cBus, O_RDWR)) < 0){
        //error handling
        std::cout << "Failed to open the I2C bus" << endl;
        std::cout << "Error: openI2CBus - errno: " << std::strerror(errno) << endl;
        return -1;
    }   
    return 0;
}

int setI2CAdress(int *deviceAddress, int i2cAdress){

    if(ioctl(*deviceAddress, I2C_SLAVE, i2cAdress) < 0){
        //error handling
        std::cout << "failed to access the bus / talk to the device" << endl;
        std::cout << "Error: setI2CAdress - errno: " << std::strerror(errno) << endl;
        return -1;
    }
    return 0;
}

int readI2C(int *deviceAddress, bool scannerCheck, int length){
    //read bytes from device
    
    if(!scannerCheck){
        if(read(*deviceAddress, readBuffer, length) != length){
            //error handling
            std::cout << "Error: ReadI2C - errno: " << std::strerror(errno) << endl;
            return -1;
        }else{
            memset(processedBuffer, 0, sizeof(processedBuffer));
            for(int i = 0; i < length; i++){
                if(readBuffer[i] == '\r' || readBuffer[i] == '\n'){
                    break;
                }
                processedBuffer[i] = readBuffer[i];
            }
            if(!scannerCheck){
                std::cout << "processed after reading : " << processedBuffer << endl; 
                // DynamicJsonDocument doc = jsonReadOut(reinterpret_cast<char*>(processedBuffer));
                std::cout << "buffer: " << readBuffer << endl;
            }
            return 0;
        }
    }else{
        if(read(*deviceAddress, readBuffer, 1) != 1){
            //error handling
            if(!scannerCheck){
                std::cout << "Error: ReadI2C - errno: " << std::strerror(errno) << endl;
            }
            return -1;
        }
        return 0;
    }
}

// int writeI2C(int *deviceAddress, char writeBuffer[BUFFERLEN]){
/**
 * @brief writes a 1 byte commando to the sensormodule
 * @param deviceAddress pointer to the device adress of the sm
 * @param writebuffer 1 byte buffer for the commando to send
*/
int writeI2C(int *deviceAddress, uint8_t writeBuffer[COMMANDOLEN]){  
    if(write(*deviceAddress, writeBuffer, COMMANDOLEN) != COMMANDOLEN){
        //error handling
        std::cout << "Written bytes does not equal lenght" << endl;
        return -1;
    }
    return 0;
}

// int writeI2C(int *deviceAddress, )

void i2cScanner(){  //scans the i2c bus, and retrieves the data about the sensor modules, from the modules
    printmsg(2);
    int tempDevice;
    openI2CBus(&tempDevice);
    for(int i = 0; i < DEVICELIM; i++){ //scan i2c adresses
        setI2CAdress(&tempDevice, i);
        int err = readI2C(&tempDevice, true, 0);
        if(err == 0){
            // if(readBuffer[1] == 0x14){
                modules[numberOfDevices].i2cAddress = i;
                
                numberOfDevices++;
                std::cout << "+++Found one device at: " << i << "+++" << endl;
            // }
        }
    }
    std::cout << "+++Done scanning+++" << endl;
    usleep(500);    
    printmsg(3); 
}

void openSmDevices(){
    for(int i = 0; i < numberOfDevices; i++){
        openI2CBus(modules[i].deviceAddress);
        setI2CAdress(modules[i].deviceAddress, modules[i].i2cAddress);
    }
}

void getSmIds(){
    for(int i = 0; i < numberOfDevices; i++){
        int tries = 0;
        while(tries < 3){
            std::cout << "+++retrieving SM_ID+++" << endl;
            writeI2C(modules[i].deviceAddress, PREP_SM_ID);
            usleep(500); 
            readI2C(modules[i].deviceAddress, false, 2);

            modules[i].sensorModuleId = readBuffer[0];
            if(readBuffer[0] > 0){
                tries=4;
            }else{
                std::cout << "failed to fetch SMid, trying again" << endl;
            }
            tries++;
        }
    }
    Json::Value smConfigJson;
    std::ifstream config_doc("../files/sensorModules.json", std::ifstream::binary);
    config_doc >> smConfigJson;
    for(int i = 0; i < numberOfDevices; i++){
		int sm = modules[i].sensorModuleId;
		modules[i].measureInterval = smConfigJson[to_string(sm)]["MEASURE_INTERVAL"].asInt();
		modules[i].senseInterval = smConfigJson[to_string(sm)]["SENSE_INTERVAL"].asInt();
		modules[i].modulePriority = smConfigJson[to_string(sm)]["MODULE_PRIORITY"].asInt();
		modules[i].sensorPrepareTime = smConfigJson[to_string(sm)]["SENSOR_PREPARE_TIME"].asInt();
		modules[i].dataLength = smConfigJson[to_string(sm)]["DATA_LENGTH"].asInt();
		modules[i].dataAmount = smConfigJson[to_string(sm)]["DATA_AMOUNT"].asInt();
		modules[i].sharedAddress = smConfigJson[to_string(sm)]["SHARED_ADDRESS"].asBool();
    }

    std::cout << "+++Printing found device's information+++" << endl;
    for(int i = 0; i < numberOfDevices; i++){
        std::cout << "--------------------------------------" << endl;
        std::cout << "devId: " << modules[i].deviceId << endl;
        std::cout << "dev Adress: " << *modules[i].deviceAddress << endl;
        std::cout << "i2cAdress: " << modules[i].i2cAddress << endl;
        std::cout << "SensorModuleId: " << modules[i].sensorModuleId << endl;
        std::cout << "Measurement Interval: " << modules[i].measureInterval << endl;
        std::cout << "Sense Interval: " << modules[i].senseInterval << endl;
        std::cout << "Module Priority: " << modules[i].modulePriority << endl;
        std::cout << "Sensor Prepare Time in Secs: " << modules[i].sensorPrepareTime << endl;
        std::cout << "Data Length: " << modules[i].dataLength << endl;
        std::cout << "Shared Adress: " << modules[i].sharedAddress << endl;
    }
}

void retrieveData(sensorModule module, int extraDelay = 0){ //retrieves the sensor data from a sensor module
    // char statusJson[128];
    // DynamicJsonDocument doc(128);
    // doc["status"] = "2";
    // serializeJson(doc, statusJson);
    // // writeI2C(module.deviceAddress, statusJson);
    // doc["status"] = "3";
    // serializeJson(doc, statusJson);
    // writeI2C(module.deviceAddress, statusJson);

    writeI2C(module.deviceAddress, MAKE_MEASUREMENT);

    sleep(module.senseInterval);
    sleep(1+extraDelay);
    
    try{
        readI2C(module.deviceAddress, false, 0);
        // constructJson();
    }
    catch(int err){
        std::cout << "Caught it! ᕦ(ò_óˇ)ᕤ" << endl;
        std::cout << "caught: " << err << endl;
        errCounter++;
        if(errCounter < 4){
            std::cout << "retrying..." << endl;
            retrieveData(module, errCounter);//retries but inceases wait time.
        }else{
            std::cout << "failed 3 times, continuing" << endl;
        }
        errCounter = 0;
    }
    std::cout << "stopwatch time: " << module.stopWatch.elapsed() << endl;
    module.stopWatch.reset();
    std::cout << "stopwatch timeNew: " << module.stopWatch.elapsed() << endl;
    
}

int main(){
    printmsg(1);
    setup();
    i2cScanner();
    openSmDevices();
    getSmIds();


    // retrieveData(modules[0]);

    openI2CBus(&testDev);
    // setI2CAdress(&testDev, 99);

    uint8_t x = 0x32;

    // writeI2C(testDev, PREP_SM_ID); 

    // char statusJson[128];
    // DynamicJsonDocument doc(128);
    // doc["status"] = "2";
    // serializeJson(doc, statusJson);
    // writeI2C(&testDev, statusJson);



    // char writeBuffer[BUFFERLEN];
    

    // writeBuffer[0] = 1;

    uint8_t writeBuffer[1];

    writeBuffer[0] = 0x32;
    // writeBuffer[1] = 0x42;
    
    std::cout<< "size: "<< sizeof(PREP_SM_ID) << endl;
    // std::cout<< "size: "<< writeBuffer.length() << endl;

    int lengthc = sizeof(PREP_SM_ID);
    std::cout << PREP_SM_ID << endl;
 
    
    return 0;
}
