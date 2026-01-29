#include <iostream>
#include <stdio.h>
#include <cstdint>

#pragma once

#define AUDIO_DATA_FIELD 0x05

typedef struct{
    uint8_t modelVersion;
    uint16_t deviceId;
    uint64_t accessToken;
    uint8_t mqtt_qos;
    char* mqqt_broker_url;
    uint8_t schemaVersion;
}HeaderSettings_t;

typedef struct{
    uint16_t length;
    uint8_t buffer[1024];
}ByteArray_t;


typedef struct{
    uint8_t dBa;
    uint8_t dBz;
    uint8_t dBc;
    uint8_t confidence;
    uint16_t audioType;



}AudioData_t;

typedef struct{
    uint16_t sensorType;
    uint8_t *dataBuffer;
    uint16_t bufferLength;
}SensorData_t;



/**
 * @brief used to set a basic header template
 */
void eliApi_SetBasicConfig(HeaderSettings_t headerSettings);

ByteArray_t eliApi_CreateByteArray();


void eliApi_AppendSensorData(ByteArray_t *pByteArray, SensorData_t sensorData);

void eliApi_AppendAudioData(ByteArray_t *pByteArray, AudioData_t audioData);


void eliApi_TransmitData(ByteArray_t *pByteArray);
