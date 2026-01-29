// volledig nieuw
#include "sensorModule.h"
#include "i2cFunctions.h"
#include "function_handler.h"
#include "function_codes.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include <algorithm>

#include <unistd.h>
#include "server_handler.h"
#include <random>
// #include "dist/jsoncpp.cpp"
// #include "dist/json/json.h"
using namespace std;


static vector<shared_ptr<SensorModule>> activeModules;
vector<int> scanI2CDevices();

// std::vector<int> scanI2CDevices() {
//     return {0x40};  // dummy voor test
// }

// Helper to check if address already known
bool moduleExists(int addr) {
    for (auto &sm : activeModules)
        if (sm->getSettings().i2cAddress == addr)
            return true;
    return false;
}

// Called periodically to find and attach new sensors
void detectAndAddSensors(DynamicJsonDocument *configJson) {
    vector<int> detected = scanI2CDevices();

    for (int addr : detected) {
        if (!moduleExists(addr)) {
            cout << "New sensor detected at I2C address: " << addr << endl;

            auto sm = make_shared<SensorModule>();
            sm->basicSettings(activeModules.size(), addr, configJson);
            activeModules.push_back(sm);
        }
    }
}

// Optional: remove sensors that disappeared
void removeDisconnectedSensors() {
    activeModules.erase(
        remove_if(activeModules.begin(), activeModules.end(),
                  [](shared_ptr<SensorModule> &sm) {
                      return !sm->checkConnection();  // optional helper in SensorModule
                  }),
        activeModules.end());
}

// Main manager loop
void sensorManagerLoop(DynamicJsonDocument *configJson) {
    while (true) {
        detectAndAddSensors(configJson);
        removeDisconnectedSensors();
        this_thread::sleep_for(chrono::seconds(2));
    }
}