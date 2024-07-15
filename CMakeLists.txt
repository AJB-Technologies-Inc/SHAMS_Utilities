cmake_minimum_required(VERSION 3.16)
project(SHAMS_Utilities)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} INTERFACE)

# Only enable testing if this is the main project
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    enable_testing()
    add_subdirectory(test)
endif()

# Add the Types library
add_subdirectory(Types)

include(FetchContent)
FetchContent_Declare(
    cmake_modules
    GIT_REPOSITORY https://github.com/AJB-Technologies-Inc/CmakeModules.git
    GIT_TAG main # Optionally, specify a specific tag or commit
)
FetchContent_MakeAvailable(cmake_modules)

include(${cmake_modules_SOURCE_DIR}/InstallAndExportShamsLib.cmake)
install_and_export_shams_lib(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Types 1.0.0)