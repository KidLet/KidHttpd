/*
 * 文件名称：access.cpp
 * 摘要：
 * 作者：Kidlet
 *
 * 历史：
 *  2014-3-2 首次编写
 *
 */
#include "access.h"
#include "connection.h"
#include "epoll.h"
#include <unistd.h>

#include <memory>
#include <vector>

using namespace std::placeholders;

Access::Access()
        :listenSock_(SOCK_STREAM, AF_INET)
{
    status_ = STOP;
    reactorsPtr = new Reactor(shared_ptr<Poll>(new EPoll()));
    reactorNum = 1;
    connId = 1;
}


void Access::run()
{
    Access::listen();
    Access::eventLoop();
}

int Access::listen()
{
    int iRet = 0;

    if(listenSock_.getFd() < 0)
        return -1;

    if(status_ == START)
        return 0;

    listenSock_.setReUse();
    iRet = listenSock_.bind("0.0.0.0", 8080);
    assert(iRet == 0);
    
    listenSock_.listen(1024);
    return 0;
}

int Access::eventLoop()
{
    reactorsPtr->poller->add(listenSock_.getFd(), EventType::R);
    reactorsPtr->setOnRead(bind(&Access::onConnection, this, _1));
    reactorsPtr->start();
    return 0;
}

void Access::onConnection(int fd)
{
    shared_ptr<Socket> clientSockPtr(new Socket());
    listenSock_.accept( *clientSockPtr.get() );
    Debug << "FD:" << clientSockPtr->getFd() << endl;
    
    connMap[connId] = clientSockPtr;
    connId++;
}
