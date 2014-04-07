/*
 * 文件名称：access.h
 * 摘要：
 * 作者：KidLet

 * 历史:
 *	2014-3-2 首次编写
 *	2014-3-30 采用 shared_ptr 管理
 *  2014-4-6 功能调整为一个Acceptor
 */
#ifndef __ACCESS_H__
#define __ACCESS_H__

#include "common.h"
#include "socket.h"
#include "thread.h"
#include "poll.h"
#include "epoll.h"
#include "reactor.h"
#include "connection.h"
#include <map>

enum Status
{
    START,
    STOP
};

const int MAX_EVENTS = 1024;

class Access : public Thread
{
public:
    Access(int num);
    void run();

private:
    int listen();
    int eventLoop();
    void onConnection(int fd);
private:
    Socket listenSock_;
    int status;

    Reactor* reactorsPtr[1024]; 
    int reactorNum;
};



#endif
