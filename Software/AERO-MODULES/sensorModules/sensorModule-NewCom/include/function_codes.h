#pragma once



#define SM_PREP_DATA            0x40
#define SM_REQ_DATA             0x41

#define SM_REQ_SMID             0x50
#define SM_REQ_VERSION          0x51
#define SM_REQ_STATE            0x52
#define SM_REQ_SENSOR_STATE     0x53 //smversuib >=3

#define SM_START_SLEEP          0x60
#define SM_REBOOT_SENSOR        0x61 //smversuib >=3
#define SM_REBOOT_MODULE        0x62 
#define SM_SENSOR_ON            0x63 //smversuib >=3
#define SM_SENSOR_OFF           0x64 //smversuib >=3