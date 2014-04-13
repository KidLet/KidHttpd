/*
 * 文件名称：task.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月5日 首次编写
 *  2014年4月10日 refactor task
 */
#ifndef TASK_H_
#define TASK_H_

#include "common.h"

using namespace std::placeholders;

class Thread;
class ThreadWorker;
class ThreadMonitor;

class Task {
public:
	Task(Thread* thread) : thread_(thread) {};
	~Task() {};
	void operator() ();
protected:
	friend class Thread;
	friend class ThreadWorker;
	friend class ThreadMonitor;

	Thread* thread_;
};



#endif /* TASK_H_ */
