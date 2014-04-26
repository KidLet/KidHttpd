#include "epoll.h"
#include <sys/epoll.h>

EPoll::EPoll()
{
    epollFd = epoll_create(1024);
    assert(epollFd != -1);
}

int EPoll::add(int fd, int type)
{
    struct epoll_event ev;
    int iRet;
    if(type == EventType::RW)
        ev.events = EPOLLIN | EPOLLOUT;
    else if(type == EventType::W)
        ev.events = EPOLLOUT;
    else
        ev.events = EPOLLIN;

    ev.data.fd = fd;
        
    iRet = epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &ev);
    assert(iRet != -1);
    return 0;
}

int EPoll::ctl(int fd, int type)
{
    struct epoll_event ev;
    int iRet;
    if(type == EventType::RW)
        ev.events = EPOLLIN | EPOLLOUT;
    else if(type == EventType::W)
        ev.events = EPOLLOUT;
    else
        ev.events = EPOLLIN;

    ev.data.fd = fd;
        
    iRet = epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &ev);
    assert(iRet != -1);
    return 0;
}


int EPoll::del(int fd)
{
    int iRet = epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, NULL);
    assert(iRet != -1);
    return 0;
}

int EPoll::poll(int timeOut, vector<Event>& vecEventList)
{
    int num = 0;
    const int MAX = 1024;
    struct epoll_event events[MAX];
    struct Event ev;
    
    num = epoll_wait(epollFd, events, MAX, timeOut);
    assert(num != -1);

    vecEventList.clear();

    for(int i=0; i<num; i++)
    {
        ev.fd = events[i].data.fd;
        if(events[i].events == (EPOLLIN | EPOLLOUT) )
            ev.type = EventType::RW;
        else if(events[i].events == EPOLLOUT)
            ev.type = EventType::W;
        else
            ev.type = EventType::R;

        vecEventList.push_back(ev);
    }
    return num;
}

EPoll::~EPoll()
{
    close(epollFd);
}
