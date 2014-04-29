#include "common.h"
#include "threadpool.h"

ThreadPool pool;

void Test(int num)
{
    cout << num << endl;
}


int main()
{
    pool.init(100);
    pool.start();

    Task testTask[1000];
    for(int i=0; i<1000; i++)
    {
        testTask[i] = std::bind(Test, i);
        pool.add(&testTask[i]);
        //testTask[i]();
        
    }

    

    
    while(1);

    //pool.stop();
    
    return 0;
}


