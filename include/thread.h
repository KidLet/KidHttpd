/*
 * 文件名称：thread.h
 * 摘要：对系统线程函数的简单封装
 * 作者：KidLet
 *
 * 历史：
 *  2014-3-27 首次编写
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include "common.h"

class Thread
{
public:
    Thread();
    virtual ~Thread();
    
    int start();
    pthread_t id();

protected:
    static void entry(Thread* self);
    virtual void run() = 0; //纯虚函数

    pthread_t pid_;
    bool isRun_;
    
};

#endif
