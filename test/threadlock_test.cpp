/*
 * 文件名称：threadlock_test.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月28日 首次编写
 */
#include "threadlock.h"
#include "lock.h"

class TestLock: public ThreadLock {
public:
	TestLock() {
		i = 0;
	}
	~TestLock(){}
	void setI(int a) {
		i = a;
	}
	void out() {
		Lock lock(*this);
		++i;
		cout << pthread_self() << ": " << i << endl;
		sleep(1);
		cout << pthread_self() << ": " << i << endl;
	}

protected:
	int i;
};

TestLock tl;

void ThreadEntry1(void *) {
	while(1)
		tl.out();
}

void ThreadEntry2(void *) {
	while(1)
		tl.out();
}

int main() {
	pthread_t id1;
	pthread_t id2;

	pthread_create(&id1, NULL, (void*(*)(void*))&ThreadEntry1, NULL);
	pthread_create(&id2, NULL, (void*(*)(void*))&ThreadEntry2, NULL);

	pthread_join(id1, NULL);
	pthread_join(id2, NULL);

	return 0;
}
