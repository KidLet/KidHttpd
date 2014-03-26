/*
 * 文件名称：thread.h
 * 摘要：对系统线程函数的简单封装
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月27日
 *
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include "common.h"

class Thread
{
public:
    Thread();
    ~Thread();
    
    int start();
    pthread_t id();

protected:
    static void entry(Thread* self);
    virtual void run() = 0; //纯虚函数

    pthread_t pid_;
    bool isRun_;
    
};

#endif
