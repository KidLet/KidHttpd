/*
 * 文件名称：worker_thread.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月5日 首次编写
 */
#ifndef WORKER_THREAD_H_
#define WORKER_THREAD_H_

#include "thread.h"

class WorkerThread: public Thread {
public:
	WorkerThread();
	WorkerThread(ThreadPool* pool): pool_(pool), isRun_(false) {};

	virtual ~WorkerThread();
	void run();
	void terminate();
	bool isAlive() const { return isRun_; }

private:
	ThreadPool* pool_;
};



#endif /* WORKER_THREAD_H_ */
