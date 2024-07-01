
add_library(Buffer INTERFACE)

set_target_properties(Buffer PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_sources(Buffer INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes/Buffer.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes/StaticBuffer.hpp>
)

target_include_directories(Buffer INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
)

# Install
install(TARGETS Buffer
    EXPORT ShamsBufferTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(EXPORT ShamsBufferTargets
    FILE ShamsBufferTargets.cmake
    DESTINATION lib/cmake/ShamsRingBuffer
)

# Unit tests
add_subdirectory(test)
