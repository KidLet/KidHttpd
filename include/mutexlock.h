/*
 * 文件名称：mutexlock.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月13日 首次编写
 */
#ifndef MUTEXLOCK_H_
#define MUTEXLOCK_H_

#include "mutex.h"

class MutexLock {
public:
	MutexLock(const Mutex& mutex): mutex_(mutex) {
		mutex_.lock();
	}
	~MutexLock() {
		mutex_.unlock();
	}
private:
	Mutex& mutex_;
};



#endif /* MUTEXLOCK_H_ */
