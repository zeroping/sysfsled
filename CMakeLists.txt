
####
# Set minimum version of CMake. Since command 'project' use
# VERSION sub-option we need 3.0.
cmake_minimum_required(VERSION 3.3)

####
# Set variables:
#   * PROJECT_NAME
#   * PROJECT_VERSION
project(sysfsled VERSION 0.1.1)

add_subdirectory(lib)

####
# Create targets
add_library(sysfsled src/led.cpp)
# used to make including easier, see https://github.com/boostcon/cppnow_presentations_2017/blob/master/05-19-2017_friday/effective_cmake__daniel_pfeifer__cppnow_05-19-2017.pdf
add_library(sysfsled::sysfsled ALIAS sysfsled)

# Generate:
#   * ${CMAKE_CURRENT_BINARY_DIR}/generated_headers/x/X_EXPORT.h with X_EXPORT
# Renaming because:
# * We need prefix to fit OSX/iOS frameworks layout
# * File name match name of the macro
set(generated_headers "${CMAKE_CURRENT_BINARY_DIR}/generated_headers")
set(sysfsled_export "${generated_headers}/sysfsled/SYSFSLED_EXPORT.hpp")
include(GenerateExportHeader)
generate_export_header(sysfsled EXPORT_FILE_NAME ${sysfsled_export})

# Global includes. Used by all targets
# Note:
#   * header location in project: include/x.hpp
#   * header can be included by C++ code `#include <x/x.hpp>`
#   * header location in project: ${CMAKE_CURRENT_BINARY_DIR}/generated_headers/x/X_EXPORT.h
#   * header can be included by: `#include <X_EXPORT.h>`
target_include_directories(
    sysfsled PUBLIC
    #"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
    "$<BUILD_INTERFACE:${generated_headers}>"
)

target_include_directories(
	sysfsled PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
)

# Link required library
target_link_libraries(sysfsled PUBLIC udevpp)

# Installation (https://github.com/forexample/package-example) {

# Layout. This works for all platforms:
#   * <prefix>/lib/cmake/<PROJECT-NAME>
#   * <prefix>/lib/
#   * <prefix>/include/
set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

#set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
# set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
# set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(version_config "${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Use:
#   * PROJECT_VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * TARGETS_EXPORT_NAME
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Targets:
#   * <prefix>/lib/libsysfsled.a 
#   * header location after install: <prefix>/include/sysfsled/sysfsled.hpp
#   * headers can be included by C++ code `#include <sysfsled/sysfsled.hpp>`
install(
    TARGETS sysfsled
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

# Install headers:
#   * include/X.hpp -> <prefix>/include/<project/X.hpp
install(
    DIRECTORY "src"
    DESTINATION "${include_install_dir}"
    FILES_MATCHING PATTERN "*.hpp"
)

# Install export headers:
#   * ${CMAKE_CURRENT_BINARY_DIR}/.../X_EXPORT.h -> <prefix>/include/<project>/X_EXPORT.h
install(
    FILES "${sysfsled_export}"
    DESTINATION "${include_install_dir}/sysfsled"
)

# Install package configuration file and version file for find_package
#   * <prefix>/lib/cmake/<project>/<project>Config.cmake
#   * <prefix>/lib/cmake/<project>/<project>ConfigVersion.cmake
install(
	FILES "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${project_config}>" "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/${version_config}>"
    DESTINATION "${config_install_dir}"
)

# Install the generated target import file
#   * <prefix>/lib/cmake/<project>/<project>Config.cmake
install(
    EXPORT "${TARGETS_EXPORT_NAME}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)

# Finally, add the example subdirectory:
add_subdirectory(example)
#add_subdirectory(test)

# }
