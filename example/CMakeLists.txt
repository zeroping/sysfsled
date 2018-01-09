cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

include_directories(../lib/src)



add_executable(led_flash src/led_flash.cpp)
add_dependencies(led_flash sysfsled libudevpp)
include_directories(${PROJECT_BINARY_DIR}/external/src/libudevpp/lib/src)

target_link_libraries(led_flash sysfsled udev)
target_link_libraries(led_flash ${LIBUDEVPP_LIBRARIES} )
