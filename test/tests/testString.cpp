#include <gtest/gtest.h>

#include "ShamsStaticString.hpp"
using namespace SHAMS;

TEST(String, create_from_c_string)
{
    constexpr StaticString str("Hello");
    ASSERT_EQ(str.length(), 5);
    ASSERT_STREQ(str.c_str(), "Hello");
}

TEST(String, create_from_empty_c_string)
{
    constexpr StaticString str("");
    ASSERT_EQ(str.length(), 0);
    ASSERT_STREQ(str.c_str(), "");
}

TEST(String, create_without_default_constructor)
{
    constexpr StaticString str;
    ASSERT_EQ(str.length(), 0);
    ASSERT_STREQ(str.c_str(), "");
    ASSERT_EQ(str.maxLength(), 16);
}

TEST(String, create_default_with_max_length)
{
    constexpr StaticString<10> str;
    ASSERT_EQ(str.length(), 0);
    ASSERT_STREQ(str.c_str(), "");
    ASSERT_EQ(str.maxLength(), 10);
}


TEST(String, access_elements)
{
    constexpr StaticString str("Hello");
    ASSERT_EQ(str[0], 'H');
    ASSERT_EQ(str[1], 'e');
    ASSERT_EQ(str[2], 'l');
    ASSERT_EQ(str[3], 'l');
    ASSERT_EQ(str[4], 'o');
}

TEST(String, access_elements_out_of_range)
{
    constexpr StaticString str("Hello");
    ASSERT_THROW(str[5], std::out_of_range);
}

TEST(String, modify_string_elements)
{
    StaticString str("world");
    str[0] = 'h';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    ASSERT_STREQ(str.c_str(), "hello");
}

