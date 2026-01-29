cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(AERO)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
add_executable(${PROJECT_NAME} src/main.cpp src/printmsg.cpp src/sensorModule.cpp src/i2cFunctions.cpp src/function_handler.cpp src/protocol_translator.cpp src/server_handler.cpp src/eliApi.cpp src/sensorManager.cpp)   


add_compile_options(-Os -Wall -Wextra -pthread -lcurl -lpigpio -lrt)

include_directories(include)

add_subdirectory(include/dist)



target_link_libraries(${PROJECT_NAME} jsoncpp pigpio rt pthread curl)

