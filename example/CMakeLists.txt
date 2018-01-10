cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_executable(led_flash src/led_flash.cpp)
add_dependencies(led_flash sysfsled libudevpp)

include_directories(${PROJECT_BINARY_DIR}/../lib/src/)
include_directories(${PROJECT_BINARY_DIR}/lib/external/src/libudevpp/lib/src)


target_link_libraries(led_flash sysfsled udev)
target_link_libraries(led_flash ${PROJECT_BINARY_DIR}/lib/external/src/libudevpp-build/libudevpp.a)
