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
#include "server.h"
#include "util.h"

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

    Configure* conf = Server::getInstance()->getConf();

    iRet = listenSock_.bind(conf->getValue("address"),
                            toint<string>(conf->getValue("port")));
    assert(iRet == 0);
    
    listenSock_.listen(10240);
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
    Server::getInstance()->gLock.lock();
    int clientFd;
    int iRet = 0;

    while(iRet == 0)
    {
        shared_ptr<Connection> clientConnPtr(new Connection());
        iRet = listenSock_.accept( *(clientConnPtr->sock.get()), 0);
        if(iRet)
            break;

        clientFd = clientConnPtr->sock->getFd();


        clientConnPtr->setReactor( reactorsPtr[ clientFd %(reactorNum-1)+1] );

        clientConnPtr->getReactor()->connMap[clientFd] = clientConnPtr;
        clientConnPtr->getReactor()->poller->add( clientFd, EventType::R );
    }

    Server::getInstance()->gLock.unlock();
    
}
