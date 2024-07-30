find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(ShamsUtilitiesTests)
target_link_libraries(ShamsUtilitiesTests PUBLIC GTest::gtest_main SHAMS_Utilities)

# Utility Type Tests
target_sources(ShamsUtilitiesTests PRIVATE
    tests/testRingBuffer.cpp
    tests/testDictionary.cpp
    tests/testBuffer.cpp
    tests/testString.cpp)

gtest_discover_tests(ShamsUtilitiesTests)