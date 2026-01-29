/**
 * This file handles the i2c communication.
*/

#include "hardware/gpio.h"
#include "hardware/watchdog.h"
#include <hardware/i2c.h>
#include <string.h>
#include <iostream>


#include "i2cHandlerCyrb.h"
#include "function_codes.h"
#include "protocol_translator.h"
#include "boards/cyrb_sensor_module_v0_4.h"
#include "constConfig.h"


using namespace std;

uint8_t functionCode = 0;
std::string requestedData;
std::string str;

bool sensorMeasurementComplete;

CyrbSensor *pSensor;

static struct i2cCommData context;
static struct i2cCommData dataSend;

DynamicJsonDocument readOutDoc(256);
DynamicJsonDocument infoJson(256);

uint8_t x;

DynamicJsonDocument jsonReadOut(std::string jsonString){ //deserializes the json document and returns it
    DynamicJsonDocument doc(256);
    DeserializationError err = deserializeJson(doc, jsonString);
    if(err){
        std::cout << "Json Deserialization failed: " << err << endl;
    }
    return doc;
}

DynamicJsonDocument senseCompleteJson(){
    DynamicJsonDocument doc(256);
    doc["senseComplete"] = sensorMeasurementComplete;
    return doc;
}

    
void functionCodeHandler(int functionCode){
    // std::cout << "Function code Handler, Func.Code: "  << functionCode << endl;

    /*on_req = on i2c request from the master device.*/
    switch (functionCode)
    {
    /*make a measurement and ready it for transmitting*/
    case SM_PREP_DATA: 
        {
            /* returns an array with data points.*/
            WriteStruct ws = pSensor->sensorPrepData(); 

            for(int i = 0; i < ws.length; i++){
                dataSend.mem[i] = ws.buffer[i];
            }  
        }
        break;
        /*place SMID in output buffer*/
    case SM_REQ_SMID:   
        {
            std::cout << "prepping smId" << endl;
            WriteStruct ws = encodeInt(SENSOR_MODULE_ID);
            //for(int i = 0; i < ws.length; i++){
            for(int i = 0; i < 12; i++){
                dataSend.mem[i] = ws.buffer[i];
            }

        }
        break;
        /*place version in output buffer*/
    case SM_REQ_VERSION:    
        {
            std::cout << "prepping smVersion" << endl;
            WriteStruct ws = encodeInt(SM_VERSION);

            for(int i = 0; i < 12; i++){
                dataSend.mem[i] = ws.buffer[i];
            }    
        }
        break;
        /*place the current state of the SM in output buffer*/
    case SM_REQ_STATE: 
        break;
    case SM_REQ_SENSOR_STATE:
        {
            WriteStruct ws = encodeInt(pSensor->getSensorState());
            for(int i = 0; i < 12; i++){
                dataSend.mem[i] = ws.buffer[i];
            } 
        }
        break;
    case SM_START_SLEEP: 
        break;
    case SM_REBOOT_SENSOR:
        pSensor->turnSensorOff();
        sleep_ms(750);
        pSensor->turnSensorOn();
        break;
    case SM_SENSOR_ON:
        pSensor->turnSensorOn();
        break;
    case SM_SENSOR_OFF:
        pSensor->turnSensorOff();
        break;
    case SM_REBOOT_MODULE:
        watchdog_enable(10, 0);
        while(1);
        break;
    default:
        break;
    }
}

/* handler to process the i2c message*/
void handler(){
    //reads i2c msg from buffer
    //checks CRC - optioinal

    //calls functionHandler with functionCode

    /* check if received data is not empty */
    if(functionCode != 0){

        /* call handler for the funciton code*/        
        functionCodeHandler(functionCode);

        functionCode = 0;
        // std::cout << "dataSEnd: " << dataSend.mem[0] << endl;
        // std::cout << "dataSEnd1: " << dataSend.mem[1] << endl;
        // std::cout << "dataSEnd1: " << dataSend.mem[2] << endl;
        // std::cout << "dataSEnd1: " << dataSend.mem[3] << endl;
        
        // std::cout << "dataSend.mem_address: " << dataSend.mem_address << endl;
        dataSend.mem_address = 0;
        // printf("memAddr: %i\n", dataSend.mem_address);
    }else{
        std::cout << "IfReceived-Failed" << endl;
    }
    i2cEvent = false;
}

/* return state of i2c event*/
bool getI2cEvent(){
    return i2cEvent;
}

/* handler for the i2c events, receive and requests*/
void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event){   
    switch (event){     
    case I2C_SLAVE_RECEIVE: //read incomming data into context.mem
        context.mem[context.mem_address] = i2c_read_byte(i2c);
        context.mem_address++;
        break;   
    case I2C_SLAVE_REQUEST: //write data to master on request
        i2c_write_byte(i2c, dataSend.mem[dataSend.mem_address]);
        dataSend.mem_address++;
        break;
    case I2C_SLAVE_FINISH: //stop/reset bit was send by master 
        i2cEvent = true;
        functionCode = context.mem[1];
        
        for(int i = 0; i < 4; i++){
            printf("%c",context.mem[i]);
        }
        printf("\n");

        std::cout << "--------------" << endl;
        memset(context.mem, 0, 256);       
        context.mem_address = 0;
        dataSend.mem_address = 0;
        break;
    default:
        break;
    }
}

/* setup the i2c slave*/
void setup_slave(CyrbSensor *s){

    pSensor = s;

    pSensor->turnSensorOn();

    gpio_init(I2C_SLAVE_SDA_PIN);
    gpio_set_function(I2C_SLAVE_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SLAVE_SDA_PIN);

    gpio_init(I2C_SLAVE_SCL_PIN);
    gpio_set_function(I2C_SLAVE_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SLAVE_SCL_PIN);

    i2c_init(i2c0, I2C_BAUDRATE);
    
    i2c_slave_init(i2c0, I2C_SLAVE_ADDRESS, &i2c_slave_handler);

    context.mem_address = 0;
    dataSend.mem_address = 0;
}



