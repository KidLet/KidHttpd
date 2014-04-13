/*
 * 文件名称：threadlock.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月5日 首次编写
 *  2014年4月13日 修改为ThreadLockT模板，定义ThreadLock和Lock
 */
#ifndef THREADLOCK_H_
#define THREADLOCK_H_

#include "mutex.h"
#include "cond.h"
#include "lock.h"
#include <pthread.h>

template <class M, class C>
class ThreadLockT {
public:
	ThreadLockT() {}
	~ThreadLockT() {}

	void lock() {
		mutex_.lock();
	}
	void unlock() {
		mutex_.unlock();
	}
	bool trylock() {
		return mutex_.trylock();
	}
	void wait() {
		cond_.wait(mutex_);
	}
	bool timedwait(int millsecond) {
		return cond_.timedwait(mutex_, millsecond);
	}
	void notify() {
		cond_.signal();
	}
	void notifyAll() {
		cond_.broadcast();
	}
protected:
	M mutex_;
	C cond_;
};

typedef LockT<ThreadLockT<Mutex, Cond>> Lock;
typedef ThreadLockT<Mutex, Cond> ThreadLock;

#endif /* THREADLOCK_H_ */
