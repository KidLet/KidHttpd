#include "common.h"
#include "threadpool.h"

ThreadPool pool;

void Test(int num)
{
    cout << num << endl;
}


int main()
{
    pool.init(500);
    pool.start();

    Task testTask[2000];
    for(int i=0; i<2000; i++)
    {
        testTask[i] = std::bind(Test, i);
        pool.add(&testTask[i]);
        
    }


    
    //while(1);

    pool.stop();
    
    return 0;
}


