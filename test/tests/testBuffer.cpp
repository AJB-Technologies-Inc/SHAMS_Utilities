#include <gtest/gtest.h>

#include "ShamsBuffer.hpp"

TEST(Buffer, Insert)
{
    SHAMS::Buffer<int> buffer;
    buffer.insert(1);
    buffer.insert(2);
    buffer.insert(3);

    ASSERT_EQ(buffer.size(), 3);
}

TEST(Buffer, SubscriptOperator)
{
    SHAMS::Buffer<int> buffer;
    buffer.insert(1);
    buffer.insert(2);
    buffer.insert(3);

    ASSERT_EQ(buffer[0], 1);
    ASSERT_EQ(buffer[1], 2);
    ASSERT_EQ(buffer[2], 3);
}