/*
  This is a library written for the SCD4x family of CO2 sensors
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/18365

  Written by Paul Clark @ SparkFun Electronics, June 2nd, 2021

  The SCD41 measures CO2 from 400ppm to 5000ppm with an accuracy of +/- 40ppm + 5% of reading

  This library handles the initialization of the SCD4x and outputs
  CO2 levels, relative humidty, and temperature.

  https://github.com/sparkfun/SparkFun_SCD4x_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.13

  SparkFun code, firmware, and software is released under the MIT License.
  Please see LICENSE.md for more details.
*/

#ifndef __Cyrb_SCD4X_H__
#define __Cyrb_SCD4X_H__


//Enable/disable including debug log (to allow saving some space)
// #define ENABLE_DBG   //!< Open this macro and you can see the details of the program
#ifdef ENABLE_DBG
  #define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
  #define DBG(...)
#endif


#define SCD4X_I2C_ADDR   uint8_t(0x62)   ///< SCD4X I2C address

//Available commands

/* SCD4X Basic Commands */
#define SCD4X_START_PERIODIC_MEASURE    uint16_t(0x21b1)   ///< start periodic measurement, signal update interval is 5 seconds.
#define SCD4X_READ_MEASUREMENT          uint16_t(0xec05)   ///< read measurement
#define SCD4X_STOP_PERIODIC_MEASURE     uint16_t(0x3f86)   ///< stop periodic measurement command	execution time: 500ms

/* SCD4X On-chip output signal compensation */
#define SCD4X_SET_TEMPERATURE_OFFSET    uint16_t(0x241d)   ///< set temperature offset  execution time: 1ms
#define SCD4X_GET_TEMPERATURE_OFFSET    uint16_t(0x2318)   ///< get temperature offset  execution time: 1ms
#define SCD4X_SET_SENSOR_ALTITUDE       uint16_t(0x2427)   ///< set sensor altitude     execution time: 1ms
#define SCD4X_GET_SENSOR_ALTITUDE       uint16_t(0x2322)   ///< get sensor altitude     execution time: 1ms
#define SCD4X_SET_AMBIENT_PRESSURE      uint16_t(0xe000)   ///< set ambient pressure    execution time: 1ms

/* SCD4X Field calibration */
#define SCD4X_PERFORM_FORCED_RECALIB    uint16_t(0x362f)   ///< perform forced recalibration              execution time: 400ms
#define SCD4X_SET_AUTOMATIC_CALIB       uint16_t(0x2416)   ///< set automatic self calibration enabled    execution time: 1ms
#define SCD4X_GET_AUTOMATIC_CALIB       uint16_t(0x2313)   ///< get automatic self calibration enabled    execution time: 1ms

/* SCD4X Low power */
#define SCD4X_START_LOW_POWER_MEASURE   uint16_t(0x21ac)   ///< start low power periodic measurement, signal update interval is approximately 30 seconds.
#define SCD4X_GET_DATA_READY_STATUS     uint16_t(0xe4b8)   ///< get data ready status       execution time: 1ms

/* SCD4X Advanced features */
#define SCD4X_PERSIST_SETTINGS          uint16_t(0x3615)   ///< persist settings      execution time: 800ms
#define SCD4X_GET_SERIAL_NUMBER         uint16_t(0x3682)   ///< get serial number     execution time: 1ms
#define SCD4X_PERFORM_SELF_TEST         uint16_t(0x3639)   ///< perform self test     execution time: 10000ms
#define SCD4X_PERFORM_FACTORY_RESET     uint16_t(0x3632)   ///< perform factory reset execution time: 1200ms
#define SCD4X_REINIT                    uint16_t(0x3646)   ///< reinit                execution time: 20ms

/* SCD4X Low power single shot */
#define SCD4X_MEASURE_SINGLE_SHOT            uint16_t(0x219d)   ///< measure single shot              execution time: 5000ms
#define SCD4X_MEASURE_SINGLE_SHOT_RHT_ONLY   uint16_t(0x2196)   ///< measure single shot rht only     execution time: 50ms
#define SCD4X_POWER_DOWN                     uint16_t(0x36e0)   ///< Put the sensor from idle to sleep to reduce current consumption.
#define SCD4X_WAKE_UP                        uint16_t(0x36f6)   ///< Wake up the sensor from sleep mode into idle mode.

/* Convenience Macro */
#define SCD4X_CONCAT_BYTES(msb, lsb)   (((uint16_t)msb << 8) | (uint16_t)lsb)   ///< Macro combines two 8-bit data into one 16-bit data

class Cyrb_SCD4X
{
public:
	/**
	* @struct sSensorMeasurement_t
	* @brief Sensor readings, including CO2 concentration, temperature and humidity
	*/
	typedef struct{
		uint16_t   CO2ppm;
	    float   temp;
	    float   humidity;
	} sSensorMeasurement_t;

public:

	sSensorMeasurement_t senseData;

	/**
	* @fn DFRobot_SCD4X
	* @brief Constructor
	* @param pWire - Wire object is defined in Wire.h, so just use &Wire and the methods in Wire can be pointed to and used
	* @param i2cAddr - SCD4X I2C address.
	* @return None
	*/

	/**************************** Init and reset ********************************/
	Cyrb_SCD4X(uint8_t i2cAddr);

	bool begin(void);

	/**
	 * @brief writes uint16_t of data to the sensor
	 * @param cmd command to be send to scd4x sensor
	*/

	/**************************** Read and Write ********************************/
	void writeData(uint16_t cmd);

	size_t readData(uint16_t cmd, uint8_t *buf, size_t size);

	/**
	 * @brief enables or disables the periodic measurement
	 * @param mode command for changing the sensor settings
	*/
	void enablePeriodMeasure(uint16_t mode);

	/********************************* Measurement Function *************************************/
	/**
	 * @brief requests & gets a measurement from the sensor in CO2ppm, temp & humidity
	 * @param data a pointer to a struct for storing the sensor data
	*/
	void readMeasurement(sSensorMeasurement_t * data);
	/**
	 * @brief returns a true back if the sensor is ready to make a measurement
	 * @return true or false
	*/
	bool getDataReadyStatus(void);


	/*************************** compensation and calibration ********************************/

	void setTempComp(float tempComp);

	void setSensorAltitude(uint16_t altitude);

	void setAmbientPressure(uint32_t ambientPressure);

	void setAutoCalibMode(bool mode);

	/*************************** sending data packs ********************************/
	/**
   * @fn pack
   * @brief Pack the data to be sent
   * @param data - The data to be sent
   * @return The packed data to be sent
   */
  	uint8_t * pack(uint16_t data);


private:
  	uint8_t deviceAddr;
};
#endif