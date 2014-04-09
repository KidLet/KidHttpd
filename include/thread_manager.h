/*
 * 文件名称：thread_manager.h
 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年4月5日 首次编写
 */
#ifndef THREAD_MANAGER_H_
#define THREAD_MANAGER_H_

#include "thread_pool.h"

class ThreadManager {
public:
	ThreadManager();
	~ThreadManager();
private:
	ThreadPool pool_;
};




#endif /* THREAD_MANAGER_H_ */
