find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(ringBufferTests tests/testRingBuffer.cpp)
target_link_libraries(ringBufferTests PUBLIC GTest::gtest_main RingBuffer)

gtest_discover_tests(ringBufferTests)