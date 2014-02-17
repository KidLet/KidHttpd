#include "gtest/gtest.h"

TEST(singleton, singleton_unique)
{
    ASSERT_EQ(0, 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
