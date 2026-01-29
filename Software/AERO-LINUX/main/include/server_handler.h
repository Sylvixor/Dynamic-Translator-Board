#include "protocol_translator.h"
#include "ArduinoJson-v6.19.4.h"
#pragma once

void setTubeConf(DynamicJsonDocument *doc1, DynamicJsonDocument *doc2);
void sendData(DecodedData decodedData, int smId);