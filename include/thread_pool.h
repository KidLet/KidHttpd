/*
 * 文件名称：thread_pool.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月5日 首次编写
 *  2014年4月9日 增加线程池动态优化
 */
#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include "worker_thread.h"
#include "thread_lock.h"
#include "task.h"
#include "cond.h"
#include "mutex.h"
#include "singleton.h"

#include <pthread.h>
#include <vector>
#include <deque>

using namespace std;

class ThreadPool{
public:
	ThreadPool();
	//ThreadPool(int min, int max, int queueSize):
	//	initNum(min), minAvailNum(min), maxAvailNum(max), maxQueueSize(queueSize),running_(false) {}
	~ThreadPool();

	void init(int num);
	void start();
	void stop(); //参考taf的pool的stop
	void clear();

	Task* get(); 	//获取启动任务
	Task* get(WorkerThread* thread); 	//thread工作线程获取任务
	void idle(WorkerThread* thread);	//将指定线程置为空闲线程
	void add(Task& task);
	bool finished() const; //判断任务队列中的任务是否都已经完成
	bool isFull() const;
	//void adjust(); 	//动态调整线程池大小

private:
/*
	int minAvailNum;
	int maxAvailNum;
	int liveNum;
	int busyNum;
	int queueSize; 	//当前任务队列大小

	WorkerThread* monitor_; //监控线程池并进行动态优化
	Mutex counter_; //线程计数器
*/
	bool running_; 	//thread pool的运行状态
	int initNum;	//线程池初始化大小
	int maxQueueSize; // 最大任务队列大小

	Cond notEmpty_;//任务队列主控
	Cond notFull_;
	Mutex pmutex_; //thread pool的互斥锁

	deque<Task*> queue_;
	vector<WorkerThread*> threads_;


};



#endif /* THREAD_POOL_H_ */
