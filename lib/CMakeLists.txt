project(sysfsled)

include(ExternalProject)

cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")


ExternalProject_Add (
      libudevpp
      PREFIX external
      GIT_REPOSITORY "https://github.com/zeroping/libudevpp.git"
      GIT_TAG "master"
	  SOURCE_SUBDIR lib
	  INSTALL_COMMAND ""
	  CMAKE_ARGS
		"-DCMAKE_BUILD_TYPE=${configuration}"
		"-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
		"-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}"
		"-DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>"

)
message("install to " <INSTALL_DIR>)

include_directories(${PROJECT_BINARY_DIR}/include)

set(LIBUDEVPP_LIBRARIES "${PROJECT_BINARY_DIR}/external/src/libudevpp-build/lib/libudevpp.a")


set(SOURCES src/led.cpp src/sysfsled.h)

add_library(sysfsled ${SOURCES})

add_dependencies(sysfsled libudevpp)

include_directories(${PROJECT_BINARY_DIR}/external/src/libudevpp/lib/src)


install(FILES ${PROJECT_BINARY_DIR}/external/src/libudevpp/lib/src/udevpp.h DESTINATION include)
install(FILES ${PROJECT_BINARY_DIR}/external/src/libudevpp-build/libudevpp.a DESTINATION lib)


install(TARGETS sysfsled ARCHIVE DESTINATION lib)
install(FILES src/sysfsled.h DESTINATION include)

