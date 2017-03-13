cmake_minimum_required(VERSION 3.5)
project(TimeLogger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ITimeLogger.h FileTimeLogger.cpp FileTimeLogger.h)
add_executable(TimeLogger ${SOURCE_FILES})