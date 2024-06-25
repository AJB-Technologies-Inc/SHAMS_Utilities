cmake_minimum_required(VERSION 3.25)
project(SHAMS_Utilities)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(cmake/install_libs.cmake)

enable_testing()

# Add the RingBuffer library
add_subdirectory(RingBuffer)

# Add the Buffer library
add_subdirectory(Buffer)

# Add the Dictionary library
add_subdirectory(Dictionary)
