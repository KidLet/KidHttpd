/*
 * 文件名称：thread.cpp
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月27日
 *
 */
#include "thread.h"

Thread::Thread()
{
    pid_ = 0;
    isRun_ = false;
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
