#include <stdio.h>
#include <iostream>
#include <stdint.h>


#pragma once

typedef struct{
    int dataPoints;
    double data[12];
}DecodedData;




typedef struct{
    uint8_t buffer[32];
    int length;
}WriteStruct;

uint8_t decodeFunction();

WriteStruct encodeData(DecodedData dataStruct);

WriteStruct encodeInt(int data);