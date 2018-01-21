cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_executable(sysfs_led_flash src/led_flash.cpp)
add_dependencies(sysfs_led_flash sysfsled)

include_directories(${PROJECT_BINARY_DIR}/../lib/src/)


target_link_libraries(sysfs_led_flash sysfsled)
