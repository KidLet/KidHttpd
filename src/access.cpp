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
#include "epoll.h"

#include <memory>
#include <vector>

using namespace std::placeholders;

Access::Access(int num)
        :listenSock_(SOCK_STREAM, AF_INET)
{
    for(int i=0; i<num; i++)
    {
        reactorsPtr[i] = new Reactor(shared_ptr<Poll>(new EPoll()));
    }

    status = STOP;
    reactorNum = num;
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

    if(status == START)
        return 0;

    listenSock_.setReUse();
    listenSock_.setBlock(0);
    iRet = listenSock_.bind("0.0.0.0", 8080);
    assert(iRet == 0);
    
    listenSock_.listen(1024);
    return 0;
}

int Access::eventLoop()
{
    reactorsPtr[0]->poller->add(listenSock_.getFd(), EventType::R);
    reactorsPtr[0]->setOnRead(bind(&Access::onConnection, this, _1));
    for(int i=0; i<reactorNum; i++)
    {
        reactorsPtr[i]->start();
    }


    return 0;
}

void Access::onConnection(int fd)
{
    int clientFd;

    shared_ptr<Connection> clientConnPtr(new Connection());
    Debug << "accept:" << listenSock_.accept( *(clientConnPtr->sock.get()), 0) << endl;
    Debug << "FD:" << clientConnPtr->sock->getFd() << endl;

    clientFd = clientConnPtr->sock->getFd();
    

    clientConnPtr->setReactor( reactorsPtr[ clientFd %(reactorNum-1)+1] );

    clientConnPtr->getReactor()->connMap[clientFd] = clientConnPtr;
    clientConnPtr->getReactor()->poller->add( clientFd, EventType::R );
    
}
