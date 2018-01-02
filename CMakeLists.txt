cmake_minimum_required(VERSION 3.1)

include(ExternalProject)

project("sysfsled - C++ library for the linux kernel's LED device class")


ExternalProject_Add (
      libudevpp-external
      GIT_REPOSITORY "https://github.com/zeroping/libudevpp.git"
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}
      GIT_TAG "master"

)

include_directories(${PROJECT_BINARY_DIR}/include)
set(LIBUDEVPP_LIBRARIES "${PROJECT_BINARY_DIR}/lib/libudevpp.a")

add_subdirectory(lib)
add_subdirectory(example)

	
