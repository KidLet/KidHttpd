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


const int n = 1000000;
Task testTask[n];

void Test(int num) {
	cout<<num<<endl;
}

void test(int size) {
	ThreadPool pool;
	pool.init(size);
    pool.start();


    for(int i=0; i<n; i++)
    {
        testTask[i] = std::bind(Test, i);
        pool.add(&testTask[i]);
    }

    while(1) sleep(1);

    //pool.stop();
}

int main() {
    //test(0);
    test(1);
    //test(2);
    //test(10);
    //test(50);
	return 0;
}


