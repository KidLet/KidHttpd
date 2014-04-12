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

#include "thread.h"

class Task {
public:
	Task(Thread* thread) : thread_(thread) {};
	~Task() {};
	void operator() ();

private:
	Thread* thread_;
};



#endif /* TASK_H_ */
