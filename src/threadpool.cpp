/*
 * 文件名称：threadpool.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月12日 首次编写
 *  2014年4月12日 完善内部实现，对线程池加锁
 *  2014年4月13日 完成线程池动态优化的实现
 */
#include "threadpool.h"

ThreadPool::ThreadPool() {
	running_ = false;
	tNum = 0;
/*	minAvailNum = 0;
	maxAvailNum = 0;
	liveNum = 0;
	busyNum = 0;
	monitor_ = new ThreadMonitor(this);*/
	jobQueue.clear();
	startQueue.clear();
}

ThreadPool::~ThreadPool() {
	if(running_) {
		stop();
		clear();
	}
}

void ThreadPool::init(int num) {
	stop();
	Lock lock(*this);
	clear();
	tNum = num;
/*	minAvailNum = min;
	maxAvailNum = max;
	busyNum = 0;
	liveNum = min;*/

	for(size_t i = 0; i < tNum; i++)
		jobThread.push_back(new ThreadWorker(this));
}

void ThreadPool::start() {
	Lock lock(*this);
	vector<ThreadWorker*>::iterator it = jobThread.begin();
	while(it != jobThread.end()) {
		(*it)->start();
		it++;
	}
	//monitor_->start();
	running_ = true;
}

void ThreadPool::stop() {
	Lock lock(*this);
	vector<ThreadWorker*>::iterator it = jobThread.begin();
	while(it != jobThread.end()) {
		if((*it)->isAlive()) {
			(*it)->terminate();
			cout<<"terminate"<<endl;
		}
		it++;
	}
	cout<<"terminate all"<<endl;
	running_ = false;
}

void ThreadPool::clear() {
	vector<ThreadWorker*>::iterator it = jobThread.begin();
	while(it != jobThread.end()) {
		delete (*it);
		it++;
	}
	jobThread.clear();
	busyThread.clear();
}

Task* ThreadPool::get() {
	Task* task = NULL;
	if(!startQueue.pop_front(task))
		return NULL;
	return task;
}

Task* ThreadPool::get(ThreadWorker* thread) {
	Task* task = NULL;
	if(!jobQueue.pop_front(task, 1000))
		return NULL;
	Lock lock(pmutex_);
	busyThread.insert(thread);
	return task;
}

void ThreadPool::idle(ThreadWorker* thread) {
	Lock lock(pmutex_);
	busyThread.erase(thread);
	if(busyThread.empty())
		pmutex_.notifyAll();
}

void ThreadPool::add(Task* task) {
	if(running_)
		jobQueue.push_back(task);
}

void ThreadPool::clearQueue() {
	jobQueue.clear();
}

bool ThreadPool::finished() {
	return startQueue.empty() && jobQueue.empty() && busyThread.empty();
}

void ThreadPool::notifyAll() {
	jobQueue.notifyT();
}

void ThreadPool::adjust() {

}
