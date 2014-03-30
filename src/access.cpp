/*
 * 文件名称：access.cpp
 * 摘要：
 *
 *
 */
#include "access.h"
#include "connection.h"
#include <sys/epoll.h>
#include <unistd.h>

#include <vector>


static int epollFd = 0;

Access::Access()
        :listenFd_(SOCK_STREAM, AF_INET)
{
    epollFd = epoll_create(10);
    assert(epollFd >= 0);

    status_ = STOP;
}


void Access::run()
{
    Access::listen();
}

int Access::listen()
{
    int iRet = 0;

    if(listenFd_.getFd() < 0)
        return -1;

    if(status_ == START)
        return 0;

    listenFd_.setReUse();
    iRet = listenFd_.bind("0.0.0.0", 8080);
    assert(iRet == 0);
    
    listenFd_.listen(1024);

    struct epoll_event stEv;
    struct epoll_event stEv_Array[MAX_EVENTS];
    //struct Connection* pConn;
    shared_ptr<Connection> pConn;
    vector< shared_ptr<Connection> > v;
    
    int iNumFds = 0;

    stEv.events = EPOLLIN;
    stEv.data.fd = listenFd_.getFd();

    iRet = epoll_ctl(epollFd, EPOLL_CTL_ADD, listenFd_.getFd(), &stEv);
    assert(iRet == 0);

    status_ = START;
    
    while(status_ == START)
    {
        iNumFds = epoll_wait(epollFd, stEv_Array, MAX_EVENTS, -1);

        for(int i=0; i<iNumFds; i++)
        {
            if(stEv_Array[i].data.fd == listenFd_.getFd()) //为接入连接Fd，有新连接到来
            {
                pConn.reset(new Connection());
                //shared_ptr<Connection> pConn(new Connection);
                
                iRet = listenFd_.accept(pConn->sock);
                assert(iRet >= 0);

                stEv.events = EPOLLIN | EPOLLET;
                stEv.data.fd = pConn->sock.getFd();
                Debug << "have new Connect:" << stEv.data.fd << endl;
                epoll_ctl(epollFd, EPOLL_CTL_ADD, stEv.data.fd, &stEv);
                v.push_back(pConn);
                
            }
            else
            {
                Debug << "have read" << endl;
                char buf[1024];
                int len = read(stEv.data.fd, buf, 1024);
                write(stEv.data.fd, buf, len);

                //v.clear();
               
            }
                
        }
    }

    return 0;
}
