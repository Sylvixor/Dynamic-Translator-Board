#include <queue>
#include <vector>
#include "sensorModule.h"
#include "function_codes.h"

#pragma once

/*
* function code
* pointer to sensor module obkect
*/
typedef struct{
    int funcCode;
    SensorModule* sensorModule;
}FunctionStruct;




void pushToQueue(int funcCode, SensorModule* sensorModule);

int processFunction(FunctionStruct function);

int processQueue();


