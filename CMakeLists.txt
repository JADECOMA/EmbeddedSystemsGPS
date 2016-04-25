cmake_minimum_required(VERSION 3.5)
project(EmbeddedSystemsGPS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Satellite/Satellite.cpp Satellite/Satellite.h SumSignal/SumSignal.cpp SumSignal/SumSignal.h Decoder/Decoder.cpp Decoder/Decoder.h)
add_executable(EmbeddedSystemsGPS ${SOURCE_FILES})
