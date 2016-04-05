cmake_minimum_required(VERSION 3.3)
project(Year1Project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp encode.cpp decode.cpp encode.h decode.h md5.h md5.cpp)
add_executable(Year1Project ${SOURCE_FILES})