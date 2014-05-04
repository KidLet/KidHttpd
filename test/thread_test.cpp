/*
 * 文件名称：thread_test.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年5月3日 首次编写
 */

#include "util.h"
#include "threadtester.h"
using namespace std;

const int n = 1000000;
Task testTask[n];
ThreadTester* tester[n];

void run(int num) {
	int j;

	for(int i=1; i<1000; i++)
	{
		j = (i+j)%7;
		j = j*i;
	}
}

void test() {
	time_t startTime;
	startTime = time(NULL);

    for(int i=0; i<n; i++)
    {
        testTask[i] = std::bind(run, i);
        tester[i] = new ThreadTester(&testTask[i]);
        if(tester[i]->start() != 0)
        {
        	 tester[i] = NULL;
        }
    }

    for(int i=0; i<n; i++)
    {
    	if(tester[i] != NULL)
    	{
    		tester[i]->join();
        	//delete tester[i];
        	//tester[i] = NULL;
    	}

    }

    cout << "cost:" << (time(NULL) - startTime) <<"s"<< endl;

}

int main() {
    test();
    return 0;
}



