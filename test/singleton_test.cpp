#include "gtest/gtest.h"
#include "singleton.h"
#include <pthread.h>
#include <unistd.h>
#include <vector>

using namespace std;

class A : public Singleton<A>{};
void* thread_fun(void*);

//检查 单例的唯一性
TEST(Singleton, Unique)
{
    for(int i=0; i<10000; i++)
    {
	ASSERT_EQ(A::getInstance(), A::getInstance()) << "单线程下重复获取实例不一致";	
    }
}



TEST(Singleton, Unique_MulitiThread)
{
    pthread_t aTids [20000];
    for(int i=0; i<20000; i++)
    {
	pthread_create(aTids + i, NULL, thread_fun, NULL);
    }


    A* last = NULL;
    
    for(int i=0; i<20000; i++)
    {
	void** ptr;
	pthread_join(aTids[i], ptr);
	if(i == 0)
	{
	    last = (A*)*(ptr);
	    continue;
	}
	
	ASSERT_EQ(last, (A*)*(ptr));
    }

    

}

void* thread_fun(void* argv)
{
    return (void*)A::getInstance();
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
