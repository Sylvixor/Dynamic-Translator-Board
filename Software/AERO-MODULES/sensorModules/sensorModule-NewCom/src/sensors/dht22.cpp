//the following code is based on the adafruit arduino DHT Library 
//and the Raspberry pi Pico dht example code
#include <sensor.h>

#ifdef DRIVER_DHT22

#define MIN_INTERVAL 2000 //min interval between sensor readings

const uint DHT_PIN = 5;
uint8_t data[5];
#define TIMEOUT UINT32_MAX
typedef struct {
    float humidity;
    float temp_celsius;
} dht_reading;

void read_from_dht(dht_reading *result);
uint32_t expectedPulse(bool level);
uint64_t lastReadTime;

void sensorInit(){
    gpio_init(DHT_PIN);
    gpio_pull_up(DHT_PIN);
    lastReadTime = to_ms_since_boot(get_absolute_time());
}

dht_reading reading;

void sensorGetData(){
    //check to make sure > 2seconds have passed since last sensor reading
    uint16_t timeDiff = to_ms_since_boot(get_absolute_time()) - lastReadTime;
    if(timeDiff > MIN_INTERVAL){
        // dht_reading reading;
        read_from_dht(&reading);
        float fahrenheit = (reading.temp_celsius * 9 / 5) + 32;
        printf("Humidity = %.1f%%, Temperature = %.1fC (%.1fF)\n",
               reading.humidity, reading.temp_celsius, fahrenheit);
    }else{
        //return last correct data
    }
    lastReadTime = to_ms_since_boot(get_absolute_time());
}

DynamicJsonDocument sensorConstructJson(){
    DynamicJsonDocument doc(256);
    doc["sM"] = SENSOR_MODULE_ID;
    doc["d0"] = reading.temp_celsius;
    doc["d1"] = reading.humidity;
    return doc;
}

void read_from_dht(dht_reading *result){
    // reset 40 bits of data to 0
    data[0] = data[1] = data[2] = data[3] = data[4] = 0;
    uint last = 0;
    // uint j = 0;
    //start reading process
    gpio_set_dir(DHT_PIN, GPIO_OUT);
    gpio_put(DHT_PIN, 1);
    busy_wait_us(1000);
    // gpio_pull_down(DHT_PIN);
    gpio_put(DHT_PIN, 0);
    busy_wait_us(2500);

    //set data line low for 
    gpio_put(DHT_PIN, 1);
    sleep_us(20);

    gpio_set_dir(DHT_PIN, GPIO_IN);

    if(expectedPulse(0) == TIMEOUT){
        printf("DHT timeout waiting for start signal low pulse.\n");
        last = 0;
        // return last;    //breaks out of çycles[80]
    }
    if (expectedPulse(1) == TIMEOUT){
		printf("DHT timeout waiting for start signal high pulse.\n");
		last = 0;
		// return last;     //breaks out of çycles[80]
	}

    uint32_t cycles[80];{
        for (int i = 0; i < 80; i += 2)
		{
			cycles[i] = expectedPulse(0);
			cycles[i + 1] = expectedPulse(1);
		}
    }

    for(int i = 0; i < 40; ++i){
        uint32_t lowCycles = cycles[2*i];
        uint32_t highCycles = cycles[2*i+1];
        if((lowCycles == TIMEOUT) || (highCycles == TIMEOUT)){
            printf("DHT TIMEOUT WAITING FOR PULSE");
            last = false;
            break;
        }
        data[i/8] <<=1;

        if(highCycles > lowCycles){
            data[i/8] |=1;
        }   
    }

    if(data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)){
        result->humidity = (float) ((data[0] << 8) + data[1]) / 10;
        if (result->humidity > 100) {
            result->humidity = data[0];
        }
        result->temp_celsius = (float) (((data[2] & 0x7F) << 8) + data[3]) / 10;
        if (result->temp_celsius > 125) {
            result->temp_celsius = data[2];
        }
        if (data[2] & 0x80) {
            result->temp_celsius = -result->temp_celsius;
        }
    }else{
        printf("checkSum failed!\n");
    }
    
}

//returns a 'count' that contains the time between a high and low signal
//'count' can be used for comparison to another 'count', to figure out if a pulse is high or low
//TIMEOUT will be returned if there is no change in pulse on the GPIO after ~100us
uint32_t expectedPulse(bool level){
    uint32_t count = 0;
    while(gpio_get(DHT_PIN) == level){
        if(count++ >= 2048){
            return TIMEOUT;
        }   
    }
    return count;
}
#endif