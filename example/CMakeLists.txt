cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")

include_directories(../lib/src)


include_directories(../deps/libudevpp/lib/src)

add_executable(led_flash src/led_flash.cpp)
target_link_libraries(led_flash udev sysfsled)
target_link_libraries(led_flash ${LIBUDEVPP_LIBRARIES} )
