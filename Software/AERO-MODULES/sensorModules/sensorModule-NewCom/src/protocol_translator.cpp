#include "protocol_translator.h"


//uint8_t decodeFunction();

/* encodes a data struct into a write struct, which can be written transmitted*/
WriteStruct encodeData(DecodedData dataStruct){
    WriteStruct writeStruct;
    writeStruct.length = 0;
    char buffer[64] = {0};

    std::string s;

    for(int i = 0; i < dataStruct.dataPoints; i++){
        std::string s = std::to_string(dataStruct.data[i]);
        s.erase(s.find_last_not_of('0')+1, std::string::npos);
        s.erase(s.find_last_not_of('.')+1, std::string::npos);

        if(i == 0){/* add data with the start of the msg */
            writeStruct.length += sprintf(buffer + writeStruct.length, "{%s",s.c_str());
        }else{ /* add data with the end of the msg*/
            writeStruct.length += sprintf(buffer + writeStruct.length, ":%s",s.c_str());
        }
        if(i ==  dataStruct.dataPoints-1){
            writeStruct.length += sprintf(buffer + writeStruct.length, "}",s.c_str());
        }
        s.clear();
    }   

    /* Move the concatenated buffer to the write struct */
    for(int i = 0; i < writeStruct.length; i++){
        writeStruct.buffer[i] = buffer[i];
    }

    printf("encodedDataLength: %i\n",writeStruct.length);

    printf("encodedDataFor: \n");
    for(int i = 0; i < writeStruct.length; i++){
        std::cout << writeStruct.buffer[i];
        // printf("%c",writeStruct.buffer[i]);
    }
    printf("\n");


    return writeStruct;
}

/* encodes a int into the a write struct*/
WriteStruct encodeInt(int data){
    WriteStruct writeStruct;
    char buffer[32] = {0};

    writeStruct.length = sprintf(buffer, "{%c}",data);

    for(int i = 0; i < 32; i++){
        writeStruct.buffer[i] = buffer[i];
    }

    return writeStruct;
}
