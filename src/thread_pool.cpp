/*
 * 文件名称：thread_pool.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月10日 首次编写
 */

#include "thread_pool.h"

ThreadPool::ThreadPool() {
	running_ = false;
	maxQueueSize = 1024;
	initNum = 0;
	pmutex_();
	notEmpty_(pmutex_);
	notFull_(pmutex_);
}

ThreadPool::~ThreadPool() {
	stop();
	clear();
}

void ThreadPool::init(int num) {
	stop();
	clear();
	initNum = num;
	for(int i = 0; i < num; i++) {
		threads_.push_back(new WorkerThread(this));
	}
}

void ThreadPool::start() {
	vector<WorkerThread*>::iterator it = threads_.begin();

	while(it != threads_.end()) {
		(*it) -> start();
		++it;
	}
	running_ = true;
}

void ThreadPool::stop() {
	running_ = false;
	notFull_.broadcast();

	vector<WorkerThread*>::iterator it = threads_.begin();

	while(it != threads_.end()) {
		if((*it)->isAlive()) {
			(*it)->terminate();
			(*it)->join();
		}
		++it;
	}
}

void ThreadPool::clear() {
	vector<WorkerThread*>::iterator it = threads_.begin();

	while(it != threads_.end()) {
		delete(it);
		++it;
	}
	threads_.clear();
	queue_.clear();
}

Task* ThreadPool::get() {
	while(queue_.empty() && running_)
		notEmpty_.wait();

	Task* task;
	if(!queue_.empty()) {
		task = &queue_.front();
		queue_.pop_front();
		if(maxQueueSize > 0)
			notFull_.signal();
	}

	return task;
}

Task* ThreadPool::get(WorkerThread* thread) {
	Task* task;
	return task;
}

void ThreadPool::idle(WorkerThread* thread) {

}

void ThreadPool::add(Task& task) {
	if(threads_.empty())
		task();
	else {
		while(isFull())
			notFull_.wait();
		queue_.push_back(&task);
		notEmpty_.signal();
	}
}

bool ThreadPool::finished() const {
	return queue_.empty() && threads_.empty();
}

bool ThreadPool::isFull() const {
	return (maxQueueSize > 0 && queue_.size() >= maxQueueSize);
}

