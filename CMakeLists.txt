cmake_minimum_required(VERSION 3.16)
project(SHAMS_Utilities)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(cmake/install_libs.cmake)

# Only enable testing if this is the main project
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    enable_testing()

    # Define a variable to indicate testing is enabled
    set(SHAMS_UTIL_TESTING_ENABLED ON CACHE INTERNAL "Enable SHAMS Utilities tests")
endif()

# Add the RingBuffer library
add_subdirectory(RingBuffer)

# Add the Buffer library
add_subdirectory(Buffer)

# Add the Dictionary library
add_subdirectory(Dictionary)
