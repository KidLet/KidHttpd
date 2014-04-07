/*
 * 文件名称：reactor.h
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月30日
 *
 * 历史:
 *	2014-3-30 首次编写
 *	2014-4-6  进一步完善
 */
#ifndef __REACTOR_H__
#define __REACTOR_H__

#include "common.h"
#include "thread.h"
#include "poll.h"
#include "socket.h"
#include "connection.h"
#include <map>

class Reactor : public Thread
{
public:
    typedef function<void (int)> callBackFunc;
    
    Reactor(shared_ptr<Poll> poll);
    
    void setOnRead( callBackFunc cb );
    void setOnWrite( callBackFunc cb );
    void run();
    void stop();
    shared_ptr<Poll> poller;
    map<int, shared_ptr<Connection> > connMap;

private:
    void onRead(int fd);
    void onWrite(int fd);
    
    int loop(int timeOut);
    int status_;
    callBackFunc readCB_;
    callBackFunc writeCB_;
    
};

#endif
