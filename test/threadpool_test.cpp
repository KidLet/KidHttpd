/*
 * 文件名称：threadpool_test.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月26日 首次编写
 */
#include "threadpool.h"
#include "util.h"
using namespace std;

const int n = 30000000;
Task testTask[n];

void run(int num) {
	int j;
	for(int i=1; i<1000; i++)
	{
		j = (i+j)%7;
		j = j*i;
	}
}

void test(int size) {
	ThreadPool pool;
	pool.init(size);
	//Task* task;

    for(int i=0; i<n; i++)
    {
        testTask[i] = std::bind(run, i);
        //task = new Task();
        //*task = std::bind(run, i);
        pool.add(&testTask[i]);
        //pool.add(task);
    }
    pool.start();
    while(1) sleep(1);

}

int main() {
    //test(1);
    test(2);
    //test(10);
    //test(50);
	return 0;
}


