#include "i2cFunctions.h"
//I2C
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <cstring>
#include <array>
#include <vector>
#include <string>


char *i2cBus = (char*)"/dev/i2c-1";


/* I2C functions */

std::vector<int> scanI2CDevices() { // nieuwe toevoeging
    std::vector<int> found;
    int file = open("/dev/i2c-1", O_RDWR);
    if (file < 0) {
        perror("Failed to open I2C bus");
        return found;
    }

    for (int addr = 0x03; addr <= 0x77; addr++) {
        if (ioctl(file, I2C_SLAVE, addr) < 0)
            continue;

        char buf = 0;
        if (write(file, &buf, 0) >= 0)
            found.push_back(addr);
    }

    close(file);
    return found;
}

int openI2CBus(int *deviceBus){

    if((*deviceBus = open(i2cBus, O_RDWR)) < 0){
        //error handling
        std::cout << "Failed to open the I2C bus" << std::endl;
        std::cout << "Error: openI2CBus - errno: " << std::strerror(errno) << std::endl;
        return -1;
    }   
    return 0;
}


/**
 * @brief set the i2c address for a device on the i2c bus
 * @param deviceBus pointer is to object from the i2c lib
 * @param deviceAddress the i2c address to set
 */
int setI2CAdress(int *deviceBus, int deviceAdress){
    if(ioctl(*deviceBus, I2C_SLAVE, deviceAdress) < 0){
        //error handling
        std::cout << "failed to access the bus / talk to the device" << std::endl;
        std::cout << "Error: setI2CAdress - errno: " << std::strerror(errno) << std::endl;
        return -1;
    }
    return 0;
}

/* read data from a i2c device*/
void readI2C(int *deviceBus, uint8_t *data, int length){
    unsigned char readBuffer[BUFFERLEN] = {0};
    unsigned char processedBuffer[BUFFERLEN] = {0};
    uint8_t readBuffer1[BUFFERLEN] = {0};
    //read bytes from device
    if(read(*deviceBus, readBuffer1, length) != length){
        //error handling
        std::cout << "Error: ReadI2C - errno: " << std::strerror(errno) << std::endl;
    }else{
        memset(processedBuffer, 0, sizeof(processedBuffer));
        printf("ReadBuffer: ");
        for(int i = 0; i < length; i++){
            if(readBuffer1[i] == '\r' || readBuffer1[i] == '\n'){
                break;
            }

            data[i] = readBuffer1[i];
            printf("%c",data[i]);
            
        }
        printf("\n");
    }
}


/* write data to a i2c device */
int writeI2C(int *deviceBus, uint8_t writeBuffer[BUFFERLEN], int length){  
    if(write(*deviceBus, writeBuffer, length) != length){
        //error handling
        std::cout << "Written bytes does not equal lenght" << std::endl;
        return -1;
    }
    return 0;
}

/**
 * @brief i2c read functions specificaly for the i2c scanner
 * @param deviceBus pointer in which info the opened bus is stored
 * @return  0 - Found device at address | -1 - no device found
*/
int readI2CScanner(int *deviceBus){
    unsigned char readBuffer[BUFFERLEN] = {0};
    if(read(*deviceBus, readBuffer, 3) != 3){
        //error handling
        return -1;
    }
    return 0;
}

bool i2c_detect_device(int busHandle, int address) { // nieuwe toevoeging
    // Try selecting the device
    if (ioctl(busHandle, I2C_SLAVE, address) < 0) {
        return false;
    }

    // Try a simple zero-length write to probe
    char buf = 0;
    if (write(busHandle, &buf, 0) >= 0) {
        return true;  // got ACK
    }

    // If write() failed with remote I/O error, no device responded
    return false;
}

/**
 * @brief preforms a i2c scan on the bus
 * @return a list of found addresses
 */
std::array<std::array<int, 7>, 2> i2cScanner(){  //scans the i2c bus, and retrieves the data about the sensor modules, from the modules
    std::array<std::array<int, 7>, 2> foundDevices = {{0}};
    int tempDevice;
    openI2CBus(&tempDevice);
    for(int i = 0; i < DEVICELIM; i++){ //scan i2c adresses
        if(i != 66){
            setI2CAdress(&tempDevice, i);
            int err = readI2CScanner(&tempDevice);
            if(err == 0){
                    std::cout << "+++Found one device at: " << i << "+++" << std::endl;
                    foundDevices[1][foundDevices[0][0]] = i;
                    foundDevices[0][0]++;
            }
        }
    }
    std::cout << "+++Done scanning+++" << std::endl;
    usleep(500);
    return foundDevices;
}