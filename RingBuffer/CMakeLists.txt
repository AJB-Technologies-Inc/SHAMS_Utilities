
add_library(RingBuffer STATIC)

set_target_properties(RingBuffer PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_sources(RingBuffer PRIVATE
    src/RingBuffer.cpp
)

target_include_directories(RingBuffer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
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
    NAMESPACE SHAMS::
    DESTINATION lib/cmake/ShamsRingBuffer
)