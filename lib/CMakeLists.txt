project(sysfsled)

cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")

set(SOURCES src/led.cpp src/sysfsled.h)

add_library(sysfsled ${SOURCES})
add_dependencies(sysfsled libudevpp)

install(TARGETS sysfsled ARCHIVE DESTINATION lib)

install(FILES src/sysfsled.h DESTINATION include)
