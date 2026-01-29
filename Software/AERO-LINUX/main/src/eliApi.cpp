#include "eliApi.h"

#include <iostream>
#include <stdio.h>
#include <cstdint>
#include <chrono>
#include <ctime>
#include <time.h>

static HeaderSettings_t headerTemplate;

// auto start = std::chrono::system_clock::now();

static uint16_t generate_crc(const uint8_t *data, size_t length) 
{
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= (uint16_t) data[i];
        for (int8_t j = 8; j != 0; j--) {
            if ((crc & 0x0001) != 0) {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else {
                crc >>= 1;
            }
        }
    }

    return (uint16_t) (crc << 8) | (uint16_t) (crc >> 8);
}


static void append_byte(ByteArray_t *pByteArray, uint8_t byte) 
{
    pByteArray->buffer[pByteArray->length++] = byte;
}

static void append_byte_buffer(ByteArray_t *pByteArray, uint8_t *buffer, uint16_t length) 
{
    for( uint16_t i = 0; i < length; i++)
    {
        pByteArray->buffer[pByteArray->length++] = buffer[i];
    }
}

static void append_bytes(ByteArray_t *pByteArray, uint64_t buffer, uint8_t length) 
{
    for (int16_t i = length * 8 - 8; i >= 0; i -= 8) {
        pByteArray->buffer[pByteArray->length++] = buffer >> i;
    }
}

void eliApi_SetBasicConfig(HeaderSettings_t headerSettings)
{
    headerTemplate = headerSettings;
}



static void appendHeader(ByteArray_t *pByteArray)
{
    append_byte(pByteArray, headerTemplate.schemaVersion);
    append_byte(pByteArray, headerTemplate.modelVersion);
    append_bytes(pByteArray, headerTemplate.deviceId, 2);
    append_bytes(pByteArray, headerTemplate.accessToken, 8);

    /* set data field number to 0*/
    append_byte(pByteArray, 0);

}

ByteArray_t eliApi_CreateByteArray()
{
    ByteArray_t byteArray;
    byteArray.length = 0;

    appendHeader(&byteArray);


    return byteArray;
}

static void appendTimestamp(ByteArray_t *pByteArray)
{

    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);

    /* convert to the correct format and place in following variable*/
    uint64_t nowTime;

    append_bytes(pByteArray, nowTime, 4);

}
void eliApi_AppendSensorData(ByteArray_t *pByteArray, SensorData_t sensorData)
{
    /* append data field start*/
    append_byte(pByteArray, sensorData.sensorType);

    /*append time stamp*/
    appendTimestamp(pByteArray);

    /*append sensor data buffer*/
    append_byte_buffer(pByteArray, sensorData.dataBuffer, sensorData.bufferLength);
}

void eliApi_AppendAudioData(ByteArray_t *pByteArray, AudioData_t audioData)
{

    /* append data field start*/
    append_byte(pByteArray, AUDIO_DATA_FIELD);

    /*append time stamp*/
    appendTimestamp(pByteArray);

    /*append decibels*/
    append_byte(pByteArray, audioData.dBa);
    append_byte(pByteArray, audioData.dBz);
    append_byte(pByteArray, audioData.dBc);

    /* append confidence*/
    append_byte(pByteArray, audioData.confidence);

    /*append sound type*/
    append_bytes(pByteArray, audioData.audioType, 2);
}



static void appendCRC(ByteArray_t *pByteArray)
{

    uint16_t crc = generate_crc(pByteArray->buffer, pByteArray->length);

    append_bytes(pByteArray, crc, 2);


}

void eliApi_TransmitData(ByteArray_t *pByteArray)
{
    /* append crc to array*/
    appendCRC(pByteArray);

    /* Call function to transmit the data */

}
















