find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(bufferTests tests/testBuffer.cpp)
target_link_libraries(bufferTests PUBLIC GTest::gtest_main Buffer)

gtest_discover_tests(bufferTests)