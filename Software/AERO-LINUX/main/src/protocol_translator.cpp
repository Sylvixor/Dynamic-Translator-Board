#include "protocol_translator.h"
#include <stdio.h>
#include "ArduinoJson-v6.19.4.h"

/**
 * from linux data structure: : {DATA:DATA,DATA:DATA:CRC}
 * from module data structure: : {STATUS:DATA,DATA:DATA:CRC}
*/

/* this file is for encoding and decoding the data send on the i2c bus */

/* encode a functioncode for i2c transmit*/
WriteStruct encodeFunction(int funcCode){
    WriteStruct writeStruct;
    
    char buffer[32] = {0};

    writeStruct.length = sprintf(buffer, "{%c}",funcCode);

    for(int i = 0; i < 32; i++){
        writeStruct.buffer[i] = buffer[i];
    }

    return writeStruct;
}

/* decode incomming data */
DecodedData decodeData(uint8_t *buf, int dataPoints){
    /**
     * take the incomming buffer and go through it until the '}' is reached
     *  check also if it starts with '{'
     * seperate the data by ':'
     * store the data in a char
     * then cover to string
     * then to double
     * then store in json?
     * check if the json gets rid of trailing 0's
    */

    /**
     * Check that data is not empty
     * Check data data is not -999
    */
    DecodedData decodedData;
    decodedData.error = false;

    // if(buf[1] == '}'){
    // if(buf[2] == '}'){
    if(buf[0] == 0 || buf[2] == '}'){
        decodedData.error = true;
        printf("Error\n");
        return decodedData;
    }

    std::string s;


    int dataPoint = 0;

    if(buf[0] == '{'){

        for(int i = 1; i < 32; i++){

            if(buf[i] == ':' || buf[i] == '}'){

                switch (dataPoint)
                {
                case 0:
                    decodedData.data0 = std::stod(s);
                    if(decodedData.data0 == -999){
                        decodedData.error = true;
                        return decodedData;
                        // printf("DATA ERROR -999 \n");
                    }
                    break;
                case 1:
                    decodedData.data1 = std::stod(s);
                    break;
                case 2:
                    decodedData.data2 = std::stod(s);
                    break;
                default:
                    break;
                }
                s.clear();
                dataPoint++;
                if(buf[i] == '}'){
                    break;
                }
            }else{
                s.push_back(buf[i]);
            }
        }
    }

    return decodedData;
}

DecodedData processModuleData(uint8_t *buffer, int dataPoints){
    DecodedData decodedData;
    
    /**
     * IMPORTANT: IN VERSION 2 OF THE SENOR MODULES THE SENSOPR DATA IS SEND USING ARDUINO JSON
     * 
    */
    if(dataPoints != 0){
        decodedData = decodeData(buffer, dataPoints);
    }else{
        decodedData.data1 = buffer[1];
    }


    return decodedData;
}

WriteStruct encodeData(DecodedData data){
    /**
     * receive data points in decoded data
     * convert data to string
     * remove trailing '0''s and '.'
     *  concatenate the data
     *  move the data into the correct bugffer 
    */
    

    WriteStruct writeStruct;
    char buffer[128] = {0};

    std::string s0 = std::to_string(data.data0);
    std::string s1 = std::to_string(data.data1);
    std::string s2 = std::to_string(data.data2);

    /* remove trailing 0's and '.' */
    s0.erase(s0.find_last_not_of('0')+1, std::string::npos);
    s0.erase(s0.find_last_not_of('.')+1, std::string::npos);

    s1.erase(s1.find_last_not_of('0')+1, std::string::npos);
    s1.erase(s1.find_last_not_of('.')+1, std::string::npos);

    s2.erase(s2.find_last_not_of('0')+1, std::string::npos);
    s2.erase(s2.find_last_not_of('.')+1, std::string::npos);


    writeStruct.length = sprintf(buffer, "{%s:%s:%s}",s0.c_str(), s1.c_str(), s2.c_str());

    /* Move the concatenated buffer to the write struct */
    for(int i = 0; i < writeStruct.length; i++){
        writeStruct.buffer[i] = buffer[i];
    }
    // printf("encodedDataLength: %i\n",writeStruct.length);

    // printf("encodedDataFor: \n");
    // for(int i = 0; i < writeStruct.length; i++){
    //     std::cout << writeStruct.buffer[i];
    //     // printf("%c",writeStruct.buffer[i]);
    // }
    // printf("\n");

    return writeStruct;
}