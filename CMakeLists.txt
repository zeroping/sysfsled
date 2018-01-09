cmake_minimum_required(VERSION 3.1)

include(ExternalProject)

project("sysfsled - C++ library for the linux kernel's LED device class")


ExternalProject_Add (
      libudevpp
      PREFIX external
      GIT_REPOSITORY "https://github.com/zeroping/libudevpp.git"
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}
      GIT_TAG "master"
      BUILD_COMMAND "${CMAKE_COMMAND}" --build . --target udevpp
      INSTALL_COMMAND "${CMAKE_COMMAND}" --target udevpp .

)
message("install to " ${PROJECT_BINARY_DIR})

include_directories(${PROJECT_BINARY_DIR}/include)
set(LIBUDEVPP_LIBRARIES "${PROJECT_BINARY_DIR}/external/src/libudevpp-build/lib/libudevpp.a")

add_subdirectory(lib)
add_subdirectory(example)

	
