#include <SomeHash.h>

#include <gtest/gtest.h>

TEST(some_hash_test, add_1_1)
{
    EXPECT_EQ(SomeHash::sum(1, 2), 3);
}