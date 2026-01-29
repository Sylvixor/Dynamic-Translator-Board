#include <stdio.h>
#include <iostream>
#include <cstdint>

#pragma once


typedef struct{
    uint8_t buffer[64];
    int length;
}WriteStruct;

typedef struct{
    int dataPoints;
    bool error;
    double data0;
    double data1;
    double data2;
}DecodedData;

WriteStruct encodeFunction(int funcCode);


/**
 * 
 * @param dataPoints the number of data points in a msg, 0 if no data and only a single info valie aka veriosn, id.
*/
DecodedData decodeData(uint8_t *buffer, int dataPoints);
WriteStruct encodeData(DecodedData data);
/**
 * 
 * @param dataPoints the number of data points in a msg, 0 if no data and only a single info valie aka veriosn, id.
*/
DecodedData processModuleData(uint8_t *buffer, int dataPoints);



