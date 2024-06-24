cmake_minimum_required(VERSION 3.25)
project(SHAMS_Utilities)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the RingBuffer library
add_subdirectory(RingBuffer)
