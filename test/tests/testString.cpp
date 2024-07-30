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
    ASSERT_STREQ(str.c_str(), "horld");
}

TEST(String, assign_from_new_c_string)
{
    StaticString str("world");
    str = "hello";
    ASSERT_STREQ(str.c_str(), "hello");
}

TEST(String, assign_from_new_static_string)
{
    StaticString<16> str("world");
    StaticString newStr("hello World");
    str = newStr;
    ASSERT_STREQ(newStr.c_str(), "hello World");
}


TEST(String, create_from_copy)
{
    StaticString str("Hello");
    StaticString copy = str;
    ASSERT_EQ(copy.length(), 5);
    ASSERT_STREQ(copy.c_str(), "Hello");
}

TEST(String, create_from_move)
{
    StaticString str("Hello");
    StaticString copy = std::move(str);
    // Ensure that the copy is correct
    ASSERT_EQ(copy.length(), 5);
    ASSERT_STREQ(copy.c_str(), "Hello");
    // Ensure that the original string is empty
    ASSERT_EQ(str.length(), 0);
    ASSERT_STREQ(str.c_str(), "");
}

TEST(String, to_upper)
{
    StaticString str("hello");
    str.toUpper();
    ASSERT_STREQ(str.c_str(), "HELLO");
}

TEST(String, to_upper_on_empty_string)
{
    StaticString str("");
    str.toUpper();
    ASSERT_STREQ(str.c_str(), "");
}

TEST(String, to_lower)
{
    StaticString str("HELLO");
    str.toLower();
    ASSERT_STREQ(str.c_str(), "hello");
}

TEST(String, to_lower_on_empty_string)
{
    StaticString str("");
    str.toLower();
    ASSERT_STREQ(str.c_str(), "");
}

TEST(String, append_char)
{
    StaticString<7> str("Hello");
    str.append('t');
    ASSERT_STREQ(str.c_str(), "Hellot");
}
TEST(String, append_null_char)
{
    StaticString<7> str("Hello");
    str.append('\0');
    ASSERT_STREQ(str.c_str(), "Hello");
}


TEST(String, append_c_string)
{
    StaticString<16> str("Hello");
    str.append(" World");
    ASSERT_STREQ(str.c_str(), "Hello World");
}

TEST(String, append_empty_c_string)
{
    StaticString<16> str("Hello");
    str.append("");
    ASSERT_STREQ(str.c_str(), "Hello");
}