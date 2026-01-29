#include <iostream>
#include "../include/dist/json/json.h"
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;

int main(){
    
    std::cout << "Starting" << endl;
    std::cout << "leleel" << endl;


    Json::Value root;

    std::ifstream config_doc("../files/sensorModules.json", std::ifstream::binary);

    if(config_doc.fail()){
        std::cout << "failed" <<endl;
    }

    config_doc >> root;

    std::cout << root << endl;

    int sm = 1;

    std::cout << "interval: " << root[to_string(sm)]["MEASURE_INTERVAL"] << endl;






    return 0;
}