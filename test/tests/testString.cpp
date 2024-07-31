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

TEST(String, create_from_std_string)
{
    std::string stdStr = "Hello";
    StaticString str(stdStr);
    ASSERT_EQ(str.length(), 5);
    ASSERT_STREQ(str.c_str(), "Hello");
}

TEST(String, create_from_empty_std_string)
{
    std::string stdStr = "";
    StaticString str(stdStr);
    ASSERT_EQ(str.length(), 0);
    ASSERT_STREQ(str.c_str(), "");
}

TEST(String, create_from_null_terminated_string)
{
    const char* cStr = "Hello";
    StaticString str(cStr);
    ASSERT_EQ(str.length(), 5);
    ASSERT_STREQ(str.c_str(), "Hello");
}

TEST(String, create_from_empty_null_terminated_string)
{
    const char* cStr = "";
    StaticString str(cStr);
    ASSERT_EQ(str.length(), 0);
    ASSERT_STREQ(str.c_str(), "");
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
    ASSERT_EQ(str.length(), 6);
}
TEST(String, append_null_char)
{
    StaticString<7> str("Hello");
    str.append('\0');
    ASSERT_STREQ(str.c_str(), "Hello");
    ASSERT_EQ(str.length(), 5);
}


TEST(String, append_c_string)
{
    StaticString<16> str("Hello");
    str.append(" World");
    ASSERT_STREQ(str.c_str(), "Hello World");
    ASSERT_EQ(str.length(), 11);
}

TEST(String, append_empty_c_string)
{
    StaticString<16> str("Hello");
    str.append("");
    ASSERT_STREQ(str.c_str(), "Hello");
    ASSERT_EQ(str.length(), 5);
}

TEST(String, append_static_string)
{
    StaticString<16> str("Hello");
    StaticString newStr(" World");
    str.append(newStr);
    ASSERT_STREQ(str.c_str(), "Hello World");
    ASSERT_EQ(str.length(), 11);
}

TEST(String, append_empty_static_string)
{
    StaticString<16> str("Hello");
    StaticString newStr("");
    str.append(newStr);
    ASSERT_STREQ(str.c_str(), "Hello");
    ASSERT_EQ(str.length(), 5);
}

TEST(String, append_static_string_with_max_length)
{
    StaticString<16> str("Hello");
    StaticString<16> newStr(" World");
    str.append(newStr);
    ASSERT_STREQ(str.c_str(), "Hello World");
    ASSERT_EQ(str.length(), 11);
}


TEST(String, append_std_string)
{
    StaticString<16> str("Hello");
    std::string newStr(" World");
    str.append(newStr);
    ASSERT_STREQ(str.c_str(), "Hello World");
    ASSERT_EQ(str.length(), 11);
}

TEST(String, append_empty_std_string)
{
    StaticString<16> str("Hello");
    std::string newStr("");
    str.append(newStr);
    ASSERT_STREQ(str.c_str(), "Hello");
    ASSERT_EQ(str.length(), 5);
}

TEST(String, append_null_terminated_string)
{
    StaticString<16> str("Hello");
    const char* newStr = " World";
    str.append(newStr);
    ASSERT_STREQ(str.c_str(), "Hello World");
    ASSERT_EQ(str.length(), 11);
}

TEST(String, append_empty_null_terminated_string)
{
    StaticString<16> str("Hello");
    const char* newStr = "";
    str.append(newStr);
    ASSERT_STREQ(str.c_str(), "Hello");
    ASSERT_EQ(str.length(), 5);
}

TEST(String, compare_static_strings)
{
    StaticString str("Hello");
    StaticString copy = "Hello";
    ASSERT_TRUE(str == copy);
    ASSERT_FALSE(str != copy);
}

TEST(String, compare_static_strings_with_different_lengths)
{
    StaticString str1 = "Hello";
    StaticString<10> str2 = "Hello";
    StaticString<20> str3 = "Hello World";
    ASSERT_TRUE(str1 == str2);
    ASSERT_FALSE(str1 == str3);
}

TEST(String, compare_with_c_string)
{
    StaticString str("Hello");
    ASSERT_TRUE(str == "Hello");
}

TEST(String, compare_with_empty_c_string)
{
    StaticString str("Hello");
    ASSERT_FALSE(str == "");
}

TEST(String, compare_with_std_string)
{
    StaticString str("Hello");
    ASSERT_TRUE(str == std::string("Hello"));
}

TEST(String, compare_with_empty_std_string)
{
    StaticString str("Hello");
    ASSERT_FALSE(str == std::string(""));
}

TEST(String, compare_with_null_terminated_string)
{
    StaticString str("Hello");
    ASSERT_TRUE(str == "Hello");
}

TEST(String, compare_with_empty_null_terminated_string)
{
    StaticString str("Hello");
    ASSERT_FALSE(str == "");
}


TEST(String, contains_substring)
{
    StaticString str("Hello World");
    StaticString str2("World");
    std::string str3("World");
    char str4[] = "World";
    ASSERT_TRUE(str.contains("World"));
    ASSERT_FALSE(str.contains("world"));
    ASSERT_TRUE(str.contains('W'));
    ASSERT_FALSE(str.contains('w'));
    // ASSERT_TRUE(str.contains(str2));
    // ASSERT_TRUE(str.contains(str3));
    ASSERT_TRUE(str.contains(str4));
}