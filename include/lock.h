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

class Lock {
public:
	Lock(){}
	virtual ~Lock(){};

	virtual void lock() = 0;
	virtual bool trylock() = 0;
	virtual void unlock() = 0;
};


#endif /* LOCK_H_ */
