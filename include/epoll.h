/*
 * 文件名称：epoll.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史:
 *	2014-4-3 首次编写
 */

#ifndef __EPOLL_H__
#define __EPOLL_H__

#include "common.h"
#include "poll.h"

class EPoll : public Poll
{
public:
    EPoll();
    virtual ~EPoll();
    int add(int fd, int type);
    int ctl(int fd, int type);
    int del(int fd);
    int poll(int timeOut, vector<Event>& vecEventList);
private:
    int epollFd;
    
};

#endif
