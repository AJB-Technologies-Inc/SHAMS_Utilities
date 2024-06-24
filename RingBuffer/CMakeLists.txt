
add_library(ShamsRingBuffer STATIC)

set_target_properties(ShamsRingBuffer PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_sources(ShamsRingBuffer PRIVATE
    src/RingBuffer.cpp
)

target_include_directories(ShamsRingBuffer PUBLIC .)

# Install
install(TARGETS ShamsRingBuffer
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)