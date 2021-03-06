/*
 * 文件名称：threadworker.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月12日 首次编写
 */

#include "threadworker.h"
#include "threadpool.h"

ThreadWorker::ThreadWorker(ThreadPool* pool) {
	pool_ = pool;
	running_ = true;
}

ThreadWorker::~ThreadWorker() {

}

void ThreadWorker::run() {

    Debug << "worker start id:" << id() << endl;
/*
	Task* task = pool_->get();
	if(task) {
		(*task)();
		//delete task;
		task = NULL;
	}
*/
	Task* task;
	while(running_) {
		task = pool_->get(this);
		if(task) {
			(*task)();
            //delete task;
			pool_->idle(this);
		}
	}
	pool_->clearQueue();
}

void ThreadWorker::terminate() {
	running_ = false;
	join();
	pool_->notifyAll();
}


