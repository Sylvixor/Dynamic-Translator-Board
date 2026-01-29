#include <sensor.h>
#include <i2cHandlerCyrb.h>
#include "hardware/watchdog.h"

//i2c libraries
#include <i2c_fifo.h>
#include <i2c_slave.h>

#include <stdio.h>
#include "pico/stdlib.h"
    

  
int main() {

    /* init general systems */
    stdio_init_all();
    
    /* start the sensor driver / sensor */
    CyrbSensor sensor = CyrbSensor();
    
    /* setup the i2cSlave */
    setup_slave(&sensor);

    
    sleep_ms(500);
    // printf("Hello World!\n");
    // printf("from Cyrb Dev Board 1.0\n");

    /* enable watchdog at 6 seconds for crashes*/
    watchdog_enable(6000, 0);


    while(1){
        
        /* update watchdog*/
        watchdog_update();

        /*check for incomming i2c message, call hadler if ther is one*/
        if(getI2cEvent()){
           handler();
        }
    }  

}   