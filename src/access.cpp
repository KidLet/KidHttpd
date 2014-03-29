/*
 * 文件名称：access.cpp
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月2日
 *
 */
#include "access.h"
#include "connection.h"
#include <sys/epoll.h>

static int epollFd = 0;

Access::Access()
        :listenFd_(SOCK_STREAM, AF_INET)
{
    epollFd = epoll_create(0);
    status_ = STOP;
}

int Access::bind()
{
    cout << listenFd_.bind("0.0.0.0", 8080) << endl;
    listenFd_.listen(1024);
    return 0;
}

void Access::run()
{
    Access::bind();
    Access::listen();
}

int Access::listen()
{
    if(listenFd_.getFd() < 0)
        return -1;

    if(status_ == START)
        return 0;

    struct epoll_event stEv;
    struct epoll_event stEv_Array[MAX_EVENTS];
    struct Connection* pConn;
    
    int iNumFds = 0;

    stEv.events = EPOLLIN;
    stEv.data.fd = listenFd_.getFd();

    epoll_ctl(epollFd, EPOLL_CTL_ADD, listenFd_.getFd(), &stEv);
    
    while(status_ == START)
    {
        iNumFds = epoll_wait(epollFd, stEv_Array, MAX_EVENTS, -1);

        for(int i=0; i<iNumFds; i++)
        {
            if(stEv_Array[i].data.fd == listenFd_.getFd()) //为接入连接Fd，有新连接到来
            {
                pConn = new Connection;
                
                listenFd_.accept(pConn->sock);

                stEv.events = EPOLLIN | EPOLLET;
                stEv.data.fd = pConn->sock.getFd();
                epoll_ctl(epollFd, EPOLL_CTL_ADD, listenFd_.getFd(), &stEv);
                
            }
            else
            {
               
            }
                
        }
    }

    return 0;
}
