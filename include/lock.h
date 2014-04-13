/*
 * 文件名称：lock.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014-3-31 首次编写
 */
#ifndef LOCK_H_
#define LOCK_H_

#include "common.h"

template <class T>
class LockT {
public:
	LockT(const T& mutex) : mutex_(mutex) { mutex_.lock(); }
	~LockT() { mutex_.unlock(); }
private:
	T mutex_;
};

#endif /* LOCK_H_ */
