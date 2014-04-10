/*
 * 文件名称：worker_thread.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月10日 首次编写
 */

#include "worker_thread.h"

void WorkerThread::run() {
	/*Task * task = pool_->get();
	if(task) {
		task();
		delete task;
		task = NULL;
	}
	while(!isRun_) {
		task = pool_->get(this);
		if(task) {
			task();
			pool_->idle(this);
		}
	}*/
	Task* task;
	while(!isRun_) {
		task = pool_->get();
		if(task) {
			task();
			pool_->idle(this);
		}
	}
}

void WorkerThread::terminate() {
	isRun_ = false;
}
