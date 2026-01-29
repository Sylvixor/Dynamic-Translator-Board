/* volledige file aangepast aan de hand van nieuwe functionaliteit
    oude functionaliteit zit er tussen geweven, gezien het hier op is voortgebouwd */
#include <iostream>
#include <stdio.h>
#include <vector>
#include <memory>
#include <algorithm>

//hardware access
#include <pigpio.h>

#include "sensorModule.h"
#include "i2cFunctions.h"
#include "function_handler.h"

#include "protocol_translator.h"
#include "ArduinoJson-v6.19.4.h"

#include "server_handler.h"
// #include "dist/json/json.h"
// #include "dist/jsoncpp.cpp"

#include <fstream>
#include <chrono>
#include <thread>

#include "eliApi.h"

#define SENSORMODULENR 6

void mainSetup() {
    gpioInitialise();
    if (gpioInitialise() < 0) {
        printf("gpioInitialise failed\n");
    } else {
        printf("gpioInitialise succeeded\n");
    }

    /* configs the mosfet pin for the sensor plate*/
    gpioSetMode(25, PI_OUTPUT);
    gpioWrite(25, 1);

    printf("Waiting for devices to boot");
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

void DEMOsetup_EliApi() {
    HeaderSettings_t headerSettings;
    headerSettings.modelVersion = 40;
    headerSettings.deviceId = 10;
    eliApi_SetBasicConfig(headerSettings);
}

void DEMOByteArray() {
    ByteArray_t byteArray = eliApi_CreateByteArray();

    SensorData_t sensorData;
    sensorData.sensorType = 2;
    uint8_t sensorDataBuffer[32] = {0, 3, 2, 5, 3, 1, 8, 7, 4};
    sensorData.dataBuffer = sensorDataBuffer;
    sensorData.bufferLength = 9;
    eliApi_AppendSensorData(&byteArray, sensorData);

    AudioData_t audioData;
    audioData.dBa = 65;
    audioData.dBz = 42;
    audioData.dBc = 19;
    audioData.confidence = 89;
    audioData.audioType = 23;
    eliApi_AppendAudioData(&byteArray, audioData);

    eliApi_TransmitData(&byteArray);
}

//dynamic sensor detection

bool sensorExists(std::vector<std::shared_ptr<SensorModule>> &list, int address) {
    for (auto &sm : list)
        if (sm->getSettings().i2cAddress == address)
            return true;
    return false;
}

void detectAndAttachSensors(std::vector<std::shared_ptr<SensorModule>> &list,
                            DynamicJsonDocument *smConfigJson, int &nextInternalId) {
    std::array<std::array<int, 7>, 2> foundDevices = i2cScanner();

    for (int i = 0; i < foundDevices[0][0]; i++) {
        int address = foundDevices[1][i];
        if (!sensorExists(list, address)) {
            printf("New sensor detected at address: %i\n", address);
            auto sm = std::make_shared<SensorModule>();
            sm->basicSettings(nextInternalId++, address, smConfigJson);
            list.push_back(sm);
        }
    }
}


int main() {
    /* init systems */
    mainSetup();
    DEMOsetup_EliApi();

    /* Read general Pi config */
    DynamicJsonDocument tubeConfJson(2048);
    std::ifstream tubeConfig_doc("../files/conf.json", std::ifstream::binary);
    deserializeJson(tubeConfJson, tubeConfig_doc);

    /* Read sensormodule config */
    DynamicJsonDocument smConfigJson(2048);
    std::ifstream smConfig_doc("../files/sensorModules_demo.json", std::ifstream::binary);
    deserializeJson(smConfigJson, smConfig_doc);
    setTubeConf(&tubeConfJson, &smConfigJson);

    /* Dynamic sensor list */
    std::vector<std::shared_ptr<SensorModule>> smList;
    int nextInternalId = 0;

    DEMOByteArray();

    /* main infinite loop */
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        /* Periodically scan for new sensors (every 2 seconds) */
        static auto lastScan = std::chrono::steady_clock::now();
        if (std::chrono::steady_clock::now() - lastScan > std::chrono::seconds(2)) {
            detectAndAttachSensors(smList, &smConfigJson, nextInternalId);
            lastScan = std::chrono::steady_clock::now();
        }

        /* Process the event queue */
        processQueue();

        /* Check all active sensor modules */
        for (auto &sm : smList) {
            sm->checkIntervalTimer();
            if (sm->getSettings().measuring)
                sm->checkSenseTimer();
        }

        /* Optional: remove disconnected sensors */
        smList.erase(
            std::remove_if(smList.begin(), smList.end(),
                           [](std::shared_ptr<SensorModule> &sm) {
                               if (!sm->checkConnection()) {
                                   std::cout << "Sensor at " << sm->getSettings().i2cAddress
                                             << " disconnected.\n";
                                   return true;
                               }
                               return false;
                           }),
            smList.end());
    }
}
