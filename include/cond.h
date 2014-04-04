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

#include "common.h"
#include "mutex.h"
#include <pthread.h>

class Cond {

public:
	Cond();
	virtual ~Cond();

	void wait(const Mutex& thread_mutex);
	bool timedwait(const Mutex& thread_mutex, int millsecond);
	void signal();
	void broadcast();
private:
	timespec abstime( int millsecond);
private:
	pthread_cond_t cond_;
};


#endif /* COND_H_ */