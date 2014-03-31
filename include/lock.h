/*
 * 文件名称：lock.h
 * 摘要：
 *
 * 当前版本：1.0
 * 作者："Zoey"
 * 日期：2014年3月31日
 */
#ifndef LOCK_H_
#define LOCK_H_

#include "common.h"

class Lock {
public:
	Lock(){}
	virtual ~Lock();

	virtual int lock() = 0;
	virtual bool trylock() = 0;
	virtual int unlock() = 0;
};


#endif /* LOCK_H_ */
