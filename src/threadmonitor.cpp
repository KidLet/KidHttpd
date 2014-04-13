/*
 * 文件名称：threadmonitor.cpp
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月13日 首次编写
 */
#include "threadmonitor.h"
#include "threadpool.h"

ThreadMonitor::ThreadMonitor(ThreadPool* pool) {
	running_ = true;
	pool_ = pool;
}

ThreadMonitor::~ThreadMonitor() {
	running_ = false;
}

void ThreadMonitor::run() {
	pool_->adjust();
}

