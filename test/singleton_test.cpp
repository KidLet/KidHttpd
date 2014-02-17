#include "gtest/gtest.h"
#include "singleton.h"

class A : public Singleton<A>{};

//检查 单例的唯一性
TEST(singleton, unique)
{
    ASSERT_EQ(A::getInstance(), new A);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
