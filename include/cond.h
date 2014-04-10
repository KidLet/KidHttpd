/*
 * 文件名称：cond.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月1日 首次编写
 */
#ifndef COND_H_
#define COND_H_

#include "mutex.h"
#include <pthread.h>

class Cond {

public:
	Cond(const Mutex* thread_mutex);
	virtual ~Cond();

	void wait();
	bool timedwait(int millsecond);
	void signal();
	void broadcast();
private:
	timespec abstime( int millsecond);
private:
	pthread_cond_t cond_;
	Mutex* cmutex_;
};


#endif /* COND_H_ */
