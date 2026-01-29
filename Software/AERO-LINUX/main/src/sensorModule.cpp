#include "sensorModule.h"
#include "i2cFunctions.h"
#include "function_handler.h"
#include "function_codes.h"
#include "sensorManager.h"

#include <stdio.h>
#include <iostream>
#include <string>

#include <unistd.h>
#include "server_handler.h"
#include <random>

// begin aanpassingen

// sensor module object creator
SensorModule::SensorModule(){

}

bool SensorModule::checkConnection() {
    return i2c_detect_device(moduleSettings.smBus, moduleSettings.i2cAddress);
}

int getSmIdFromI2C(DynamicJsonDocument &config, int i2cAddress) {
    for (JsonPair kv : config.as<JsonObject>()) {
        const char* id = kv.key().c_str();
        JsonVariant value = kv.value();

        if (value["I2C_ADDRESS"].as<int>() == i2cAddress) {
            return std::stoi(id);
        }
    }

    std::cerr << "Geen smId gevonden voor I2C-adres: " << i2cAddress << std::endl;
    return -1;
}

/* the init function for the sensor module, also load s the basic data, sets i2c addr, etc*/
// void SensorModule::basicSettings(int internalId, int i2cAddress, DynamicJsonDocument *smConfigJson){
//     printf("Creating sensor module with internalId: %i, and i2c address: %i\r\n",internalId, i2cAddress);
//     moduleSettings.internalId = internalId;
//     moduleSettings.i2cAddress = i2cAddress;
//     moduleSettings.errorCounter = 0;
//     moduleSettings.severityCounter = 0;
//     this->smConfigJson = smConfigJson;
//     openI2CBus(&moduleSettings.smBus);
//     setI2CAdress(&moduleSettings.smBus, moduleSettings.i2cAddress);
//     std::cout << "smBus0: " << moduleSettings.smBus << std::endl;
//     moduleSettings.measuring = false;
//     pushToQueue(SM_REQ_VERSION, this);
//     pushToQueue(SM_REQ_SMID, this);
//     pushToQueue(SM_PREP_DATA, this);
//     pushToQueue(SM_REQ_DATA, this);
// }

void SensorModule::basicSettings(int internalId, int i2cAddress, DynamicJsonDocument *smConfigJson) {
    printf("Creating sensor module with internalId: %i, and i2c address: %i\r\n",
           internalId, i2cAddress);

    moduleSettings.internalId = internalId;
    moduleSettings.i2cAddress = i2cAddress;
    moduleSettings.errorCounter = 0;
    moduleSettings.severityCounter = 0;
    this->smConfigJson = smConfigJson;

    openI2CBus(&moduleSettings.smBus);
    setI2CAdress(&moduleSettings.smBus, moduleSettings.i2cAddress);
    std::cout << "smBus0: " << moduleSettings.smBus << std::endl;
    moduleSettings.measuring = false;

    // search SmID based on i2cAddress automatically
    int detectedSmId = -1;

    for (JsonPair kv : (*smConfigJson).as<JsonObject>()) {
        int address = kv.value()["I2C_ADDRESS"];
        if (address == i2cAddress) {
            detectedSmId = std::stoi(kv.key().c_str());
            break;
        }
    }

    if (detectedSmId > 0) {
        setSmId(detectedSmId); // load settings based on detected SmID
    } else {
        std::cerr << "Geen sensorconfig gevonden voor adres " << i2cAddress << std::endl;
    }

    pushToQueue(SM_REQ_VERSION, this);
    pushToQueue(SM_REQ_SMID, this);
    pushToQueue(SM_PREP_DATA, this);
    pushToQueue(SM_REQ_DATA, this);
}

// eind aanpassingen

void SensorModule::setSmI2CAdress(int i2cAddress){
    moduleSettings.i2cAddress = i2cAddress;
}
void SensorModule::setState(int state){
    moduleSettings.state = state;
}
void SensorModule::setVersion(int version){
    moduleSettings.smVersion = version;
    printf("Version: %i\n",moduleSettings.smVersion);
}

/* set smId and load settings from json config*/
void SensorModule::setSmId(int smId){
    moduleSettings.smId = smId;
    DynamicJsonDocument doc(2048);
    doc = *smConfigJson;

    moduleSettings.measureInterval = doc[std::to_string(moduleSettings.smId)]["MEASURE_INTERVAL"];
    moduleSettings.senseInterval = doc[std::to_string(moduleSettings.smId)]["SENSE_INTERVAL"];
    moduleSettings.modulePriority = doc[std::to_string(moduleSettings.smId)]["MODULE_PRIORITY"];
    moduleSettings.dataPoints = doc[std::to_string(moduleSettings.smId)]["DATA_POINTS"];
    moduleSettings.sharedAddress = doc[std::to_string(moduleSettings.smId)]["SHARED_ADDRESS"];
    printf("Configured sm: %i, with MI: %i, DP: %i\n",moduleSettings.smId,moduleSettings.measureInterval,moduleSettings.dataPoints);
    printf("smId: %i\n",moduleSettings.smId);


}

void SensorModule::startSenseTimer(){
    //start timer for the time it takes for a measurement to be made
    
}
void SensorModule::startIntervalTimer(){
    //start timer for interval between measurements
}

bool SensorModule::checkSenseTimer(){
    bool finished = false;

    //check if the sense interval timer has finished
    if(swSInterval.elapsed() > moduleSettings.senseInterval){
        moduleSettings.measuring = false;
        swSInterval.reset();
        pushToQueue(SM_REQ_DATA, this);
        swMInterval.reset();
    }

    //return if timer has finished
    return finished;
}
bool SensorModule::checkIntervalTimer(){
    bool finished = false;

    //check if the sense interval timer has finished
    if(swMInterval.elapsed() > moduleSettings.measureInterval){
        moduleSettings.measuring = true;
        pushToQueue(SM_PREP_DATA, this);
        swMInterval.reset();
        swSInterval.reset();
    }

    return finished;
}

ModuleSettings SensorModule::getSettings(){
    return moduleSettings;
}

int SensorModule::getDataLength(){
    // return moduleSettings.dataLength;
    return 127; //<- i2c data ength max
}

int* SensorModule::getSmBus(){
   return &moduleSettings.smBus;
}

int SensorModule::getDataPoints(){
    return moduleSettings.dataPoints;
}

void SensorModule::setDataBuffer(unsigned char*){

}

void SensorModule::errorHandler(){
    /**
     * up the error counter
     *  if errC > 3, up severity
     * switch to correct severity option
    */
    moduleSettings.errorCounter++;
    if(moduleSettings.errorCounter > 3){
        moduleSettings.errorCounter = 0;
        moduleSettings.severityCounter++;
        if(moduleSettings.severityCounter > 3){

        }
    }
    switch (moduleSettings.severityCounter)
    {
    case 0: /* retry req data */
        /* for now do nothing */
        break;
    case 1: /* reset sensor */
        pushToQueue(SM_REBOOT_SENSOR, this);
        break;
    case 2: /* restart module */
        pushToQueue(SM_REBOOT_MODULE, this);
        break;
    case 3: /* reset sensor plate */
        /**
         * turn off sensor plate
         * sleep for 5 seconds
         * turn on sensor plate
         * flush the current function buffer
        */

       /* left out because other sensors are also effected*/
    default:
        break;
    }

}

int SensorModule::processData(DecodedData decodedData){
    /**
     * Check if error flag is set
     * if it's set, up error counter
     * 
    */

    if(decodedData.error){
        errorHandler();
        return -1;
    }
    printf("sm_sd0:%f\n",decodedData.data0);
    printf("sm_sd1:%f\n",decodedData.data1);
    printf("sm_sd2:%f\n",decodedData.data2);
    sendData(decodedData, moduleSettings.smId);    
    return 0;
}

void SensorModule::printSettings(){
    printf("V: %i\n",moduleSettings.smVersion);
    printf("id: %i\n",moduleSettings.smId);
    printf("MI: %i\n",moduleSettings.measureInterval);
}