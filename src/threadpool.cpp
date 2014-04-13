/*
 * 文件名称：threadpool.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月12日 首次编写
 */
#include "threadpool.h"

ThreadPool::ThreadPool() {
	running_ = false;
	tNum = 0;
	minAvailNum = 0;
	maxAvailNum = 0;
	liveNum = 0;
	busyNum = 0;
	//monitor_ = NULL;
}

ThreadPool::~ThreadPool() {
	if(running_) {
		stop();
		clear();
	}
}

void ThreadPool::init(int min, int max) {
	stop();
	clear();
	tNum = min;
	minAvailNum = min;
	maxAvailNum = max;

	for(size_t i = 0; i < tNum; i++)
		jobThread.push_back(new ThreadWorker(this));
}

void ThreadPool::start() {
	vector<ThreadWorker*>::iterator it = jobThread.begin();
	while(it != jobThread.end()) {
		//(*it) -> start();
		it++;
	}
	monitor_->start();
	running_ = true;
}

void ThreadPool::stop() {
	vector<ThreadWorker*>::iterator it = jobThread.begin();
	while(it != jobThread.end()) {
		//if((*it)->isAlive())
			//(*it)->terminate();
		it++;
	}
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
	busyThread.insert(thread);
	return task;
}

void ThreadPool::idle(ThreadWorker* thread) {
	busyThread.erase(thread);
	if(busyThread.empty())
		pmutex_.notifyAll();
}

void ThreadPool::add(Task* task) {
	jobQueue.push_back(task);
}

void ThreadPool::clearQueue() {
	jobQueue.clear();
}

bool ThreadPool::finished() const {
	return startQueue.empty() && jobQueue.empty() && busyThread.empty();
}

void ThreadPool::notifyAll() {
	jobQueue.notifyT();
}

void ThreadPool::adjust() {

}
