cmake_minimum_required(VERSION 3.16)
project(SHAMS_Utilities)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(ShamsUtilities INTERFACE)

# Only enable testing if this is the main project
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    enable_testing()
    add_subdirectory(test)
endif()

# Add the Types library
add_subdirectory(Types)