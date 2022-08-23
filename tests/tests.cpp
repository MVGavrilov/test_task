#include "SomeHash.h"

#include <gtest/gtest.h>

TEST(some_hash_test, sum_1_1)
{
    EXPECT_EQ(SomeHash::sum(1, 2), 3);
}