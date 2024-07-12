#include "gtest/gtest.h"
#include "ShamsRingBuffer.hpp"

TEST(RingBufferTests, CanCreateBuffer)
{
    auto buffer = SHAMS::RingBuffer<int>(10);
    EXPECT_EQ(buffer.capacity(), 10);
}