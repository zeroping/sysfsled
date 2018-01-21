cmake_minimum_required(VERSION 3.2)

set(needed_libs "googletest udevpp")

# This file is here to download libraries and projects that we depend on. It uses DownloadProject from https://github.com/Crascit/DownloadProject
if( ${CMAKE_SOURCE_DIR}/lib STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  # stand-alone build
  message(STATUS "Configuring ${PROJECT_NAME} for stand-alone build, downloading libs into ${CMAKE_CURRENT_BINARY_DIR}")
#   foreach(needed_lib ${needed_libs})
#     set(libdir "${libs_dir}/${needed_lib}")
#     if(NOT EXISTS "${libdir}/CMakeLists.txt")
#       message(FATAL_ERROR "Failed to find library ${needed_lib} in ${libdir}")
# 	endif()
# 	add_subdirectory(${libdir})
#   endforeach()
  
else()
  message(STATUS "Configuring ${PROJECT_NAME} for integrated build, expecting to find lib targets defined: ${needed_libs}")
  return()

#   foreach(needed_lib ${needed_libs})
#     set(libdir ${libs_dir}/${needed_lib})
#     if(NOT TARGET "${needed_lib}")
#       message(STATUS "trying FIND_PACKAGE for library ${needed_lib}")
#       #should we try #find_package(${needed_lib} 0.0.1 REQUIRED) ?
#       find_package(${needed_lib} 0.0.1 REQUIRED)
#       if(NOT ${needed_lib}_FOUND)
#         message(FATAL_ERROR "Needed target ${needed_lib} for ${PROJECT_NAME}. Be sure to add_subdirectory() it somewhere.")
#       endif()
# 	endif()
#   endforeach()
endif()


include(CTest)

#Fetch google test
include(DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             release-1.8.0
                 PREFIX ${CMAKE_CURRENT_BINARY_DIR}
                 UPDATE_DISCONNECTED 1
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

#fetch udevpp
download_project(PROJ                udevpp
                 GIT_REPOSITORY      https://github.com/zeroping/libudevpp.git
                 GIT_TAG             cmakesubmod
                 PREFIX ${CMAKE_CURRENT_BINARY_DIR}
                 UPDATE_DISCONNECTED 1
)
add_subdirectory(${udevpp_SOURCE_DIR} ${udevpp_BINARY_DIR} EXCLUDE_FROM_ALL)
