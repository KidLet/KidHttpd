/*
 * 文件名称：threadmonitor.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月13日 首次编写
 */
#ifndef THREADMONITOR_H_
#define THREADMONITOR_H_

#include "thread.h"

class ThreadPool;

class ThreadMonitor: public Thread {
public:
	ThreadMonitor(ThreadPool* pool);
	~ThreadMonitor();
	void run();

protected:
	ThreadPool* pool_;
};




#endif /* THREADMONITOR_H_ */
