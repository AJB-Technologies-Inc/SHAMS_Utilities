find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(testDictionary tests/testDictionary.cpp)
target_link_libraries(testDictionary PUBLIC GTest::gtest_main Dictionary)

gtest_discover_tests(testDictionary)