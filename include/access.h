/*
 * 文件名称：access.h
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月2日

 * 历史:
 *	2014-3-2 首次编写
 *	2014-3-30 采用 shared_ptr 管理
 */
#ifndef __ACCESS_H__
#define __ACCESS_H__

#include "common.h"
#include "socket.h"
#include "thread.h"

enum Status
{
    START,
    STOP
};

const int MAX_EVENTS = 1024;

class Access : public Thread
{
public:
    Access();
    int listen();
    void run();

private:
    Socket listenFd_;
    int status_;
};



#endif
