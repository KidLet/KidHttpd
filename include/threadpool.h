/*
 * 文件名称：threadpool.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月5日 首次编写
 *  2014年4月9日 增加线程池动态优化参数
 */
#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include "queue.h"
#include "threadworker.h"
#include "threadlock.h"

#include <pthread.h>
#include <vector>
#include <set>

using namespace std;

class ThreadPool : public ThreadLock {
public:
	ThreadPool();
	~ThreadPool();

	void init(int num);
	void start();
	void stop(); //参考tax的pool的stop
	void clear();

	Task* get(); 	//获取启动任务
	Task* get(ThreadWorker* thread); 	//thread工作线程获取任务
	void idle(ThreadWorker* thread);	//将指定线程置为空闲线程
	void add(Task* task);
	void clearQueue();
	bool finished(); //判断任务队列中的任务是否都已经完成
	void notifyAll();

	void setTNum(size_t num) { tNum = num; }
	size_t getSize() { return tNum; }

	friend class ThreadWorker;
private:
	size_t tNum;	//线程池初始化大小

	bool running_; 	//thread pool的运行状态

	ThreadLock pmutex_; //thread pool的互斥锁

	Queue<Task*> jobQueue;
	Queue<Task*> startQueue;

	vector<ThreadWorker*> jobThread;
	set<ThreadWorker*> busyThread;
};

#endif /* THREADPOOL_H_ */
