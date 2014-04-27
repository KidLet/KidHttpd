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


void printString() {
	//cout<<str<<endl;
	int sum = 1+1;
	cout<<sum<<endl;
	//usleep(100);
}

void test(int size) {
	ThreadPool pool;
	pool.init(size);
	pool.start();

/*	for(int i = 0; i < 10; i++) {
		string buf = "Task: " + tostr<int>(i);
		cout<<buf<<endl;
		Task t = std::bind(printString);
		pool.add(&t);
	}
	cout<<"exit"<<endl;*/
	pool.stop();
}

int main() {
    //test(0);
    //test(1);
    test(5);
    //test(10);
    //test(50);
	return 0;
}


