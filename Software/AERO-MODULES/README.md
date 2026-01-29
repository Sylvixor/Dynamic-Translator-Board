# README #

This README would normally document whatever steps are necessary to get your application up and running.

### How to clone repo ###


once the repo has been cloned, run the command: "git submodule update --init --recursive"
to get all the submodules for this project.

### intro ###
* This project includes everything needed to build, compile, and flash sensor modules.
* This project was written to be used on a raspberry pi 3/4, possible 5(not tested), on ubuntu.




### How to add a new sensor ###

1. Add a new driver config in include/constConfig.h. Create a driver name for the new sensor called "DRIVER_SENSORNAME" with the information about the new sensorModule.
Make sure that the I2C_SLAVE_ADDRESS is unique.
2. create a copy of "sensorTemplate.cpp" in the src/sensors folder, and change the DRIVER_SENSORNAME to the new driver name.
3. Add the path of the new .cpp file to the CMakeLists.txt file in "add_executable".
4. Select the new driver in the CMakeLists.txt file at "add_definitions(-DDRIVER_SENSORNAME)", make sure that only 1 driver is enabled at the same time.
5. Follow the instructions about the functions in the template file, to implement the sensor. as a  general guide:
* fill in CyrbSensor::sensorInit() with the correnct functions to setup/config the sensor.
* add the functions to request / readout the sensor data to CyrbSensor::sensorPrepData().
* if more or larger functions are required in order for the sensor to work, add additional functions to the file declared as static, and call them from CyrbSensorPrepData.

### How to wire a sensor to the sensorModule ###

* Use prewired 7-wire jst connector, of which the pinout is as follows Alos see SensorModuleWire.jpg:
1. black-   MiSo / Txd
2. red-     Cs / Rxd
3. white-   sck / sda
3. yellow-  MoSi / scl
4. orange-  Ground
5. green-   +3.3V
6. blue-    +5V

* The empty pads on the lower side of the module can be used to add pull-up resistors to +3.3V or +5V, or a pull-down resistor, to each wire. Use 0805 sized resistors.

1. Connect the correct wires of the prewired connector to your sensor. Use the manufacturers datasheets/documenation of the sensor to determine the correct wiring. This can very per sensor, and per manufacturer of the same sensor.
2. add any pull-up/down resistors if necessary.

### How to compile this project ###

1. Read through Chapter 2.2 of the "getting-started-with-pico.pdf" document in this repo, and follow the instructions to install the correct tools.
1. Make sure the correct driver is selected in CMakeLists.txt
2. run the command: "sudo ./compileCmake.sh" to ready the build files.
* If this step fails, delete the contents of the ./build folder and try again.
* Only run this command if changes were made to the CMakeLists.txt file
3. run the command: "sudo ./qompile.sh" to only compile the project.
4. run the command: "sudo ./makeCompileBuild.sh" to compile and flash the project to the module in one go.


### How to flash a sensor ###

* This section quickly explains how to flash a sensor. The SWD protocol is used, so if a seperate SWD programmer is available, that can be used to flash the generated .elf output file onto the module. 
*In normal operation the raspberry pi pins are used to flash the output file to the module.

1. Read through Chapter 5. of the "getting-started-with-pico.pdf" document in this repo, and follow the instructions.
2. Connect your SWD debugger or raspberry pi to the module's +5V, Ground, SWDO, and SWCLK pins. Use chapter 5. from the .pdf file as a wiring guide. 
* If the programming doesn't work, switch the SWDO and SWCLK wires and try again.
4. Use the command: "sudo ./makeCompileFlash.sh" to compile the project, and flash it to the module


### How to change or add new pinout config / defines ###

* In the /include/boards folder are .h files which hold the pin config for the senosrmodule / rp2040. If the pinout changes, or a name needs to change, update it in the correct .h file.
* This also needs to be update in CMakeLists.txt.


* Currently used: "cyrb_sensor_module_v0_4.h"




