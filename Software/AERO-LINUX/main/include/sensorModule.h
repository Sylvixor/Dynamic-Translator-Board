// #include "dist/json/json.h"
// #include "dist/jsoncpp.cpp"
#include "protocol_translator.h"
#include "ArduinoJson-v6.19.4.h"
#include "stopwatch_base.h"
#include <time.h>
#include <chrono>

#pragma once

using StopWatch = sw::stopwatch_base<std::chrono::steady_clock>;

typedef struct{
            int i2cAddress;
            int smBus;
            int smId;
            int measureInterval;
            int senseInterval;
            int smVersion;
            int internalId;
            int state;
            int dataLength;
            int dataPoints;
            int modulePriority;
            bool sharedAddress;
            unsigned char *dataBuffer;
            bool measuring;
            int errorCounter;
            int severityCounter;
}ModuleSettings;


class SensorModule{
    private:
        // Json::Value *smConfigJson;
        DynamicJsonDocument *smConfigJson;
        ModuleSettings moduleSettings;
        StopWatch swMInterval{};
        StopWatch swSInterval{};
        void errorHandler();

    public:
        // SensorModule(int internalId, int i2cAddress, DynamicJsonDocument *smConfigJson);
        SensorModule();

        void basicSettings(int internalId, int i2cAddress, DynamicJsonDocument *smConfigJson);
        // void openI2CBus();
        void setSmI2CAdress(int i2cAddress);
        // void readi2c();
        // void writei2c();
        void setState(int state);
        void setVersion(int version);
        void setSmId(int smId);

        bool checkConnection(); // nieuwe toevoeging

        void startSenseTimer();
        void startIntervalTimer();
        bool checkSenseTimer();
        bool checkIntervalTimer();
        
        void printSettings();

        //void processData();
        int getDataLength();
        int getDataPoints();
        void setDataBuffer(unsigned char* data);

        int* getSmBus();

        /**
         * @brief processes the read data from a device, and pushes a request to the processedDataStack
         * @param a pointer to the data
         * @return ok if everything was good, error if fault -> retry a read request immediatly.
        */
        int processData(DecodedData decodedData);

        ModuleSettings getSettings();

    /**
     * @brief fills the relevant fields in the class from a json format
     * @param
     * @return a int for status, 0 = fail, 1 = success
    */
    // int fillFromJson(Json::Value);

};