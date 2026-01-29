cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(AERO)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
add_executable(${PROJECT_NAME} src/main.cpp)  


add_compile_options(-Os -Wall -Wextra -pthread -lrt)

include_directories(include)

# add_subdirectory(include/dist)



# target_link_libraries(${PROJECT_NAME} pigpio rt pthread curl)
target_link_libraries(${PROJECT_NAME} rt pthread)

