#include <gtest/gtest.h>
#include <ShamsDictionary.hpp>

TEST(Dictionary, Insert)
{
    SHAMS::Dictionary<int, int> dict(10);

    dict.insert(1, 10);

    ASSERT_EQ(dict.size(), 1);
}

TEST(Dictionary, Retrieve)
{
    SHAMS::Dictionary<int, int> dict(10);

    dict.insert(1, 10);

    ASSERT_EQ(dict[1], 10);
}

TEST(Dictionary, Remove)
{
    SHAMS::Dictionary<int, int> dict(10);

    dict.insert(1, 10);
    dict.remove(1);

    ASSERT_EQ(dict.size(), 0);
}

TEST(Dictionary, Contains)
{
    SHAMS::Dictionary<int, int> dict(10);

    dict.insert(1, 10);

    ASSERT_TRUE(dict.contains(1));
}

TEST(Dictionary, ContainsWithStringKey)
{
    SHAMS::Dictionary<std::string, int> dict(10);

    dict.insert("one", 1);

    ASSERT_TRUE(dict.contains("one"));
}

TEST(Dictionary, RetrieveWithStringKey)
{
    SHAMS::Dictionary<std::string, int> dict(10);

    dict.insert("one", 1);

    ASSERT_EQ(dict["one"], 1);
}

TEST(Dictionary, RemoveWithStringKey)
{
    SHAMS::Dictionary<std::string, int> dict(10);

    dict.insert("one", 1);
    dict.remove("one");

    ASSERT_EQ(dict.size(), 0);
}

TEST(Dictionary, InsertWithMaxCapacity)
{
    SHAMS::Dictionary<int, int> dict(2);

    dict.insert(1, 10);
    dict.insert(2, 20);
    ASSERT_FALSE(dict.insert(3, 30));
    ASSERT_EQ(dict.size(), 2);
}