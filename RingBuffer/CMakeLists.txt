
add_library(RingBuffer INTERFACE)

set_target_properties(RingBuffer PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_sources(RingBuffer INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes/RingBuffer.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes/StaticRingBuffer.hpp>
)

target_include_directories(RingBuffer INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
)

# Install
install(TARGETS RingBuffer
    EXPORT ShamsRingBufferTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(EXPORT ShamsRingBufferTargets
    FILE ShamsRingBufferTargets.cmake
    DESTINATION lib/cmake/ShamsRingBuffer
)

# Unit tests
add_subdirectory(test)
