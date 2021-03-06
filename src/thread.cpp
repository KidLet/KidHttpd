/*
 * 文件名称：thread.cpp
 * 摘要：
 * 作者：KidLet
 *
 * 历史：
 *  2013-3-27 首次编写
 *  2014-4-9 添加join和detach的封装
 */
#include "thread.h"

Thread::Thread()
{
    pid_ = 0;
    running_ = false;
}

Thread::~Thread()
{
}

int Thread::start()
{
    int iRet = pthread_create(&this->pid_, NULL, (void*(*)(void*))&Thread::entry, (void *)this);

    return iRet;
}

void Thread::entry(Thread* self)
{
    self->run();
}

pthread_t Thread::id()
{
    return pid_;
}

void Thread::join() {
	int rc = pthread_join(this->pid_, NULL);
	assert(rc == 0);
}

void Thread::detach() {
	int rc = pthread_detach(this->pid_);
	assert(rc == 0);
}
