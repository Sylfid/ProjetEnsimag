cmake_minimum_required(VERSION 2.8.11)

project(Demo)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(exe src/Test.cpp src/Dvector.cpp src/Height.cpp src/WaveModel.cpp)

