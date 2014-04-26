/*
 * 文件名称：threadworker.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月5日 首次编写
 */
#ifndef THREADWORKER_H_
#define THREADWORKER_H_

#include "thread.h"

class ThreadPool;

class ThreadWorker: public Thread {
public:
	ThreadWorker(ThreadPool* pool);
	~ThreadWorker();

	void run();
	void terminate();
	bool isAlive() const { return running_; }

protected:
	ThreadPool* pool_;
};

#endif /* THREADWORKER_H_ */
