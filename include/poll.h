/*
 * 文件名称：poll.h
 * 摘要：
 * 作者：KidLet
 *
 * 历史:
 *	2014-4-3 首次编写
 */

#ifndef __POLL_H__
#define __POLL_H__

#include "common.h"
#include <vector>

enum EventType
{
    R = 1,
    W = 2,
    RW = 3
};

struct Event
{
    int fd;
    int type;
};


class Poll
{
public:
    virtual int add(int fd, int type) = 0;
    virtual int del(int fd) = 0;
    virtual int ctl(int fd, int type) = 0;
    virtual int poll(int timeOut, vector<Event>& vecEventList) = 0;
    
};

#endif
