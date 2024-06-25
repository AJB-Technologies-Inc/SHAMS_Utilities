
add_library(Dictionary INTERFACE)

set_target_properties(Dictionary PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_sources(Dictionary INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes/Dictionary.hpp>
)

target_include_directories(Dictionary INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
)

# Install
install(TARGETS Dictionary
    EXPORT ShamsDictionaryTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(EXPORT ShamsDictionaryTargets
    FILE ShamsDictionaryTargets.cmake
    DESTINATION lib/cmake/ShamsDictionary
)

# Unit tests
add_subdirectory(test)
