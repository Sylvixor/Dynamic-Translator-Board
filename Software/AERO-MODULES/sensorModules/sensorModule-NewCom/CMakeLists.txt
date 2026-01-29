cmake_minimum_required(VERSION 3.13)

# You need to include a .cmake file which has configurations for the Pico SDK
# It is located here: path-to-pico-sdk/pico_sdk_init.cmake
#include(external/pico-sdk/pico_sdk_import.cmake)
include(../pico-sdk/pico_sdk_init.cmake)
set(PICO_BOARD_HEADER_DIRS ${CMAKE_SOURCE_DIR})


project(sensorModule-NewCom C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)



set(PICO_BOARD "include/boards/cyrb_sensor_module_v0_4") # Changing the board configuration so that the default pin defines are correct for this board



# Initialises the sdk environment
pico_sdk_init()

#Add all .c files here
add_executable(sensorModule-TEST_ENV src/main.cpp src/i2cHandlerCyrb.cpp src/protocol_translator.cpp src/sensors/dht22.cpp src/sensors/hm3301.cpp src/sensors/bmp280.cpp src/sensors/scd4x.cpp src/sensors/test.cpp src/sensors/combine.cpp)


#includes the "libs" folder, containing libraries
include_directories(include)
add_subdirectory(include/i2c_slave)

# The compile option below optimizes for size, so code size is kept at a minimum
add_compile_options(-Os -Wall -Wextra)

# Below definition can be used to change for which sensor the project is built.
# Change the X in -DDRIVER_X to one of the sensor options (see below).
# There are three options:
# - DHT22(temp & RH)
# - HM3301 (ppm1,2.5,10)
# - BMP280 (temp & air pressure)
# - SCD4X (co2)
# Only one sensor can be defined at a time! Otherwise build errors
# add_definitions(-DDRIVER_HM3301)
add_definitions(-DDRIVER_COMBINE)
# add_definitions(-DDRIVER_SCD4X)

pico_enable_stdio_usb(sensorModule-TEST_ENV 1)
pico_enable_stdio_uart(sensorModule-TEST_ENV 0)

# pico_enable_stdio_usb(sensorModule-TEST_ENV 0)
# pico_enable_stdio_uart(sensorModule-TEST_ENV 1)

#target_compile_options(sensorModule-TEST_ENV PRIVATE -Wall)

target_link_libraries(sensorModule-TEST_ENV i2c_slave pico_stdlib hardware_i2c hardware_spi hardware_irq hardware_pio) # Include the pico libs


pico_add_extra_outputs(sensorModule-TEST_ENV) # Makes a UF2 file which is needed to upload to the QT Py


