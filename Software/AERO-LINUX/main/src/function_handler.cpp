#include "function_handler.h"
#include "protocol_translator.h"
#include "i2cFunctions.h"
#include "function_codes.h"
#include <unistd.h>

std::queue<FunctionStruct> functionQueue;

#define SMID_LENGTH 3

/* push new event / function code to queue */
void pushToQueue(int funcCode, SensorModule* sensorModule){    
    functionQueue.push(FunctionStruct{funcCode, sensorModule});
}

/* process a function code struct*/
int processFunction(FunctionStruct function){



    switch (function.funcCode){ 
        case SM_PREP_DATA: 
        {
            WriteStruct writeStruct = encodeFunction(SM_PREP_DATA);
            writeI2C(function.sensorModule->getSmBus(), writeStruct.buffer, writeStruct.length);
        }
            break;
        case SM_REQ_DATA:
        {
            uint8_t data[256] = {0};
            readI2C(function.sensorModule->getSmBus(), data, function.sensorModule->getDataLength());
            DecodedData DecodedData = processModuleData(data, function.sensorModule->getDataPoints());
            function.sensorModule->processData(DecodedData);  
        }
            break;
        case SM_REQ_SMID:  
        {
            uint8_t data[32] = {0};
            WriteStruct writeStruct = encodeFunction(SM_REQ_SMID);
            writeI2C(function.sensorModule->getSmBus(), writeStruct.buffer, writeStruct.length);  
            usleep(5000); 
            readI2C(function.sensorModule->getSmBus(), data, SMID_LENGTH);
            DecodedData decodedData = processModuleData(data, 0);
            function.sensorModule->setSmId(decodedData.data1);
        }
            break;
        case SM_REQ_VERSION:   
        {
            uint8_t data[32] = {0};
            WriteStruct writeStruct = encodeFunction(SM_REQ_VERSION);
            writeI2C(function.sensorModule->getSmBus(), writeStruct.buffer, writeStruct.length);  
            usleep(5000); 
            readI2C(function.sensorModule->getSmBus(), data, SMID_LENGTH);
            DecodedData decodedData = processModuleData(data, 0);
            function.sensorModule->setVersion(decodedData.data1);
        }
            break;
        case SM_REQ_STATE:  
        {

        }
            break;
        case SM_START_SLEEP: 
        {

        }
            break;
        case SM_REBOOT_SENSOR:
        {
            WriteStruct writeStruct = encodeFunction(SM_REBOOT_SENSOR);
            writeI2C(function.sensorModule->getSmBus(), writeStruct.buffer, writeStruct.length);
        }
            break;
        case SM_REBOOT_MODULE: 
        {
            WriteStruct writeStruct = encodeFunction(SM_REBOOT_MODULE);
            writeI2C(function.sensorModule->getSmBus(), writeStruct.buffer, writeStruct.length);
        }
            break;
        case SM_TRANSMIT_DATA:
        {

        }
            break;
        default:
        {}
            break;
    }
    return 0;
}

/* process events in the queue until it is empty */
int processQueue(){
    int success;

    while(!functionQueue.empty()){
        usleep(5000);
        processFunction(functionQueue.front()); // <---- implement check to see if it succeeded, retry if failed, move to next if fail x3
        functionQueue.pop();
        usleep(5000);
    }

    return success;
}
