/*
 * 文件名称：threadtester.cpp

 * 摘要：
 * 作者：Zoey
 *
 * 历史：
 *  2014年5月3日 首次编写
 */
#include "threadtester.h"

ThreadTester::ThreadTester(Task* task) {
	this->task = task;
}

ThreadTester::~ThreadTester() {

}

void ThreadTester::run() {
	(*task)();
}

