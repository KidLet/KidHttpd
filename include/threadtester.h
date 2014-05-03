/*
 * 文件名称：threadtester.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年5月3日 首次编写
 */
#ifndef THREADTESTER_H_
#define THREADTESTER_H_

#include "thread.h"

class ThreadTester : public Thread {
public:
	ThreadTester(Task* task);
	~ThreadTester();
	void run();
private:
	Task* task;
};




#endif /* THREADTESTER_H_ */
