/*
 * 文件名称：access.h
 * 摘要：
 *
 * 当前版本：1.0
 * 作者：KidLet
 * 日期：2014年3月2日
 *
 */
#ifndef __ACCESS_H__
#define __ACCESS_H__

#include "common.h"
#include "socket.h"
#include "thread.h"

enum
{
    START,
    STOP
};

const int MAX_EVENTS = 1024;

class Access : public Thread
{
public:
    Access();
    int listen();
    int bind();
    void run(){while(1)sleep(1); cout << "i am run" << endl;}

private:
    Socket listenFd_;
    int status_;
};

struct Conn
{
    Socket sock;
    unsigned long long activeTimeStamp;
    // to be add
};


#endif
