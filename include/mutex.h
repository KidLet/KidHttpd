/*
 * 文件名称：mutex.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年3月31日 首次编写
 */
#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

class Cond;

class Mutex {

public:
	Mutex();
	virtual ~Mutex();

	void lock();
	bool trylock();
	void unlock();

protected:
	friend class Cond;
	pthread_mutex_t mutex_;
};

#endif /* MUTEX_H_ */
