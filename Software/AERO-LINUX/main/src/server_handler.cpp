#include "server_handler.h"
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Exception.hpp>
#include <curl/curl.h>
#include <iostream>
#include <string.h>
#include <stdio.h>


static DynamicJsonDocument *pTubeConf;
static DynamicJsonDocument *smConfigJson;

void setTubeConf(DynamicJsonDocument *doc1, DynamicJsonDocument *doc2){
    pTubeConf = doc1;
    smConfigJson = doc2;
}


void sendData(DecodedData decodedData, int smId){ //Sends the construced json to a webserver & databse

    DynamicJsonDocument tubeConf(2048);
    tubeConf = *pTubeConf;

    CURLcode res;
    char getHTTP[512];
    memset(getHTTP, 0, sizeof(getHTTP));
    
    char authHeader[512];
    memset(authHeader, 0, sizeof(authHeader));

    DynamicJsonDocument authJson(1028);
    char authChar[512];

    std::string authString = tubeConf["auth"]["token"];
    sprintf(authChar, "Bearer %s", authString.c_str());

    // std::cout << "authChar: "<<authChar<<std::endl;
    authJson["Authorization"] = authChar;
    // std::cout << "authJson: "<<authJson<<std::endl;

    authString.clear();

    DynamicJsonDocument jsonData(512);
    jsonData["sensorModuleID"] = smId;
    jsonData["d0"] = decodedData.data0;
    jsonData["d1"] = decodedData.data1;
    jsonData["d2"] = decodedData.data2;
    // DynamicJsonDocument jsonValue(512);
    // jsonValue["value"] = jsonData;
    std::string jsonStringData;
    serializeJson(jsonData, jsonStringData);
    // //// authString = confJson["auth"]["token"].asString();
    serializeJson(authJson, authString);
    
    sprintf(authHeader, "Authorization: %s", authChar);
    // std::cout << "authHeader: " << authHeader << std::endl;

    sprintf(getHTTP, "https://dashboard.cyrb.nl/api/data-aero%s%s", jsonStringData.data(), authString.data());
    std::cout << "GetHTTP: " << getHTTP << std::endl;
    DynamicJsonDocument doc(2048);
    doc = *smConfigJson;
    CURL *curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, "https://dashboard.cyrb.nl/api/data-aero");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

        struct curl_slist *headers = NULL;

        headers = curl_slist_append(headers, authHeader);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_mime *mime;
        curl_mimepart *part;
        mime = curl_mime_init(curl);
        part = curl_mime_addpart(mime);
        curl_mime_name(part, "data");
        curl_mime_data(part, jsonStringData.data(), CURL_ZERO_TERMINATED);

        part = curl_mime_addpart(mime);
        curl_mime_name(part, "format");
        curl_mime_data(part, doc[std::to_string(smId)]["TYPE"], CURL_ZERO_TERMINATED);
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
        // res = curl_easy_perform(curl);

        char errBuf[CURL_ERROR_SIZE];
        // curl_easy_setopt(curl, CURLOPT_URL, getHTTP);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errBuf);
        // std::cout << "CURL: " << curl << std::endl;
        res = curl_easy_perform(curl);  
        curl_mime_free(mime);
        curl_slist_free_all(headers);
        if(res != CURLE_OK){
            std::cout << "FL4 " << std::endl;
            std::cout << ":(" << std::endl;
            std::cout << "Curl Res Error: " << res << std::endl;
            std::cout << "Curl errBuf: " << errBuf << std::endl;
            curl_easy_reset(curl);
        }
    }
    curl_easy_cleanup(curl);
}