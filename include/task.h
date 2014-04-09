/*
 * 文件名称：task.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月5日 首次编写
 */
#ifndef TASK_H_
#define TASK_H_

#include "thread.h"

class Task {
public:
	Task(Thread& thread);
	~Task();
	void run(void*);
	void setTaskData(void*);

private:
	void* taskdata_;
	Thread* thread_;
};



#endif /* TASK_H_ */
