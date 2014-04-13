/*
 * 文件名称：threadpool.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月5日 首次编写
 *  2014年4月9日 增加线程池动态优化
 */
#ifndef THREADPOOL_H_
#define THREADPOOL_H_


#include "task.h"
#include "cond.h"
#include "mutex.h"
#include "queue.h"
#include "threadworker.h"
#include "threadlock.h"
#include "threadmonitor.h"

#include <pthread.h>
#include <vector>
#include <set>

using namespace std;

class ThreadPool{
public:
	ThreadPool();
	~ThreadPool();

	void init(int min, int max);
	void start();
	void stop(); //参考tax的pool的stop
	void clear();

	Task* get(); 	//获取启动任务
	Task* get(ThreadWorker* thread); 	//thread工作线程获取任务
	void idle(ThreadWorker* thread);	//将指定线程置为空闲线程
	void add(Task* task);
	void clearQueue();
	bool finished() const; //判断任务队列中的任务是否都已经完成
	void notifyAll();

	void adjust(); 	//动态调整线程池大小

private:
	size_t tNum;	//线程池初始化大小
	size_t minAvailNum;
	size_t maxAvailNum;
	size_t liveNum;
	size_t busyNum;

	bool running_; 	//thread pool的运行状态

	ThreadLock<Mutex, Cond> pmutex_; //thread pool的互斥锁
	//ThreadLock<Mutex, Cond> counter_; //线程计数器

	Queue<Task*> jobQueue;
	Queue<Task*> startQueue;

	vector<ThreadWorker*> jobThread;
	set<ThreadWorker*> busyThread;

	ThreadMonitor* monitor_; //监控线程池并进行动态优化

};

#endif /* THREADPOOL_H_ */
